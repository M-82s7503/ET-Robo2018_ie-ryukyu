#include "ev3.h"
#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Clock.h"
#include "Port.h"
#include "SonarSensor.h"
#include "ColorSensor.h"

#include <cstdlib>
#include <cmath>
using namespace ev3api;

/* 色に関する宣言 */
#define NONE 0    // 無し
#define BLACK 1   // 黒 
#define BLUE 2    // 青
#define GREEN 3   // 緑
#define YELLOW 4  // 黄
#define RED 5     // 赤
#define WHITE 6   // 白

/* mapに関する宣言 */
#define N 4
#define NO_EXIST 0
#define BEFORE_MOVE_BLOCK 1
#define AFTER_MOVE_BLOCK 2

/* 動きに関する宣言 */
#define DELTA_T 0.004
#define KP 1.34
#define KI 4.46
#define KD 0.167

/* Map関するクラス */
class Map_Move{
public:
  int block[N][N]; //block exist                                                                                    
  int map_color[N][N]; //map color                                                                                  
  int car_x,car_y;
  int move_x,move_y;
  int car_degree;
public:
  Map_Move();
  void block_jud(int solove_num[5]);  // 暗号よりブロックの初期配置の計算                                           
  void priority_move(int* move_x,int* move_y,int block[N][N]); // 運ぶブロックの優先順位を決める
  void move_point(int block_color,int* move_x,int* move_y,int block[N][N]); // ブロックを移動させる座標を決定する                                           
};


/* 初期化 */
Map_Move::Map_Move()
{
  car_x = 0;
  car_y = 2;
  car_degree = 0;

  int i,j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      block[i][j] = NO_EXIST;
    }
  }

  map_color[0][0] = RED;
  map_color[0][1] = YELLOW;
  map_color[0][2] = BLUE;
  map_color[0][3] = GREEN;

  map_color[1][0] = BLUE;
  map_color[1][1] = GREEN;
  map_color[1][2] = RED;
  map_color[1][3] = YELLOW;

  map_color[2][0] = RED;
  map_color[2][1] = YELLOW;
  map_color[2][2] = BLUE;
  map_color[2][3] = GREEN;

  map_color[3][0] = BLUE;
  map_color[3][1] = GREEN;
  map_color[3][2] = RED;
  map_color[3][3] = YELLOW;


}

/* 暗号よりブロックの初期配置の計算 */
void Map_Move::block_jud(int code_solve[5])
{
  int count;
  int x,y;

  for(count = 0; count < N; count++){
    y = code_solve[count]/4;
    x = code_solve[count] - y * 4;
    block[y][x] = BEFORE_MOVE_BLOCK;
  }

}

/* 運ぶブロックの優先順位を決める */
void Map_Move::priority_move(int* move_x,int* move_y,int block[N][N])
{
  int i,j;
  int box,distance;

  distance = 100;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){

      if(block[i][j] == BEFORE_MOVE_BLOCK){
        box = abs(i - car_y)+ abs(j - car_x);
        if(distance > box){
          *move_y = i;
          *move_x = j;
          distance = box;
        }
      }

    }
  }


}

/* ブロックを移動させる座標を決定する */
void Map_Move::move_point(int block_color,int* move_x,int* move_y,int block[N][N])
{
  int i,j;
  int box,distance;

  distance = 100;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){

      if(map_color[i][j] == block_color){
        box = abs(i - car_y)+ abs(j - car_x);
        if(distance > box){
          *move_y = i;
          *move_x = j;
          distance = box;
        }
      }

    }
  }
}

/* 暗号を解くクラス */
class Code_Solve{
private:
  int num;
  int count;
public:
  Code_Solve();
  void Solve(int solve_num[5],int firstvalue);
};

Code_Solve::Code_Solve(){
  num = 0;
  count = 0;
}

void Code_Solve::Solve(int solve_num[5],int firstvalue){

  while(count < 5){
    if(firstvalue < num * pow(16,4-count)){
      solve_num[count] = num-1;
      firstvalue -= (num-1)*pow(16,4-count);
      num = 0;
      count++;
    }else{
      num++;
    }
  }

}



/* 走行に関するクラス */
class MoveUtil{
private:
  Motor leftWheel;
  Motor rightWheel;
  Motor handWheel;
  ColorSensor colorsensor;
  Clock clock;
  int speed;
  uint32_t E_time;
  
  int diff[2];
  float intergral;
  int8_t target_val;
  int8_t sensor_val;
  int8_t control_speed;
public:
  MoveUtil();
  void turn(int degree);
  void straight(int distance); // mm進むプログラム
  void back(int distance); // mm戻るプログラム
  void purpose_move(int* car_x,int* car_y,int move_x,int move_y,int* car_degree,int block[4][4],int handdegree);
  void back_move(int car_degree,int* car_x,int* car_y);
  float block_pid(int8_t sensor_val,int8_t target_val);
  void pid_straight(int distance);
  void to_color(int color);
  void hand_move(int jud);
};

//初期化
MoveUtil::MoveUtil():
  leftWheel(PORT_C),rightWheel(PORT_B),handWheel(PORT_A),colorsensor(PORT_2)
{
  speed = (Motor::PWM_MAX) / 6;
  sensor_val = colorsensor.getBrightness();
  target_val = 11;
}

//指定の角度分曲がる(-180~180)
void MoveUtil::turn(int degree) {
  E_time = abs(degree) * 7.5;
  clock.reset();//クロックをリセット

  while (1) {
    //degreeが0以上で右回転、未満で左回転
    if (degree >= 0){
      leftWheel.setPWM(-speed);
      rightWheel.setPWM(speed);
    }else{
      leftWheel.setPWM(speed);
      rightWheel.setPWM(-speed);
    }
    //リセットした時間から一定経過でタイヤストップ
    if (clock.now() >= E_time){
      leftWheel.stop();
      rightWheel.stop();
      break;
    }
  }
}

//指定の距離進む
void MoveUtil::straight(int distance){
  E_time = distance * 4.5;
  clock.reset();

  while (1) {

    leftWheel.setPWM(speed);
    rightWheel.setPWM(speed);

    if (clock.now() >= E_time){
      leftWheel.stop();
      rightWheel.stop();
      break;
    }
  }
}

//指定の距離進む                                                                                                                                                  
void MoveUtil::back(int distance){
  E_time = distance * 4.5;
  clock.reset();
  while(1){
    leftWheel.setPWM(-speed/2);
    rightWheel.setPWM(-speed/2);
    
    if (clock.now() >= E_time){
      leftWheel.stop();
      rightWheel.stop();
      break;
    }
  }

}

/* ブロック並べの際のpid制御 */
float MoveUtil::block_pid(int8_t sensor_val,int8_t target_val){
  float p, i, d;

  diff[0] = diff[1];
  diff[1] = sensor_val - target_val;
  intergral += (diff[1] + diff[0]) / 2.0*DELTA_T;

  p = KP * diff[1];
  i = KI * intergral;
  d = KD * (diff[1] - diff[0]) / DELTA_T;

  return p+d;
}

//指定の距離進む                                                                                                                                                                             
void MoveUtil::pid_straight(int distance){
  E_time = distance * 4.7;
  clock.reset();

  while (1) {
    sensor_val = colorsensor.getBrightness();
    control_speed = block_pid(sensor_val,target_val);
    leftWheel.setPWM(speed+control_speed);
    rightWheel.setPWM(speed-control_speed);

    if (clock.now() >= E_time){
      leftWheel.stop();
      rightWheel.stop();
      break;
    }
  }
}

void MoveUtil::to_color(int color){
  while(1) {
    leftWheel.setPWM(speed);
    rightWheel.setPWM(speed);
    if (colorsensor.getColorNumber() == color) {
      leftWheel.stop();
      rightWheel.stop();
      break;
    }
  }
}

//目標の座標まで移動する
void MoveUtil::purpose_move(int* car_x,int* car_y,int move_x,int move_y,int* car_degree,int block[4][4],int jud){
  
  hand_move(jud);
  bool flag1,flag2;

  flag1 = flag2 = false;

  do{
    /* 機体の角度の調整 */
    if(*car_x != move_x){
      if(*car_x < move_x){
	switch(*car_degree){
	case 90:
	  turn(-90);
	  *car_degree = 0;
	  break;
	case 180:
	  turn(180);
	  *car_degree = 0;
	  break;
	case 270:
	  turn(90);
	  *car_degree = 0;
	  break;
	}
      }else{
	switch(*car_degree){
	case 0:
	  turn(180);
	  *car_degree = 180;
	  break;
	case 90:
	  turn(90);
	  *car_degree = 180;
	  break;
	case 270:
	  turn(-90);
	  *car_degree = 180;
	  break;
	}
      }

      /* 目標のx座標まで移動する */
      while(*car_x != move_x){
	if(*car_x > move_x){
	  if(block[*car_y][*car_x-1] != AFTER_MOVE_BLOCK){
	    (*car_x)--;
	    straight(40);
	    //to_color(RED);
	  }else{
	    break;
	  }
	}else{ 
	  if(block[*car_y][*car_x+1] != AFTER_MOVE_BLOCK){
	    (*car_x)++;
	    straight(40);
	    //to_color(RED);
	  }else{ 
	    break;
	  }
	}
      }
    }

    if(*car_y != move_y){
      /* 機体の角度の調整 */
      if(*car_y > move_y){
	switch(*car_degree){
	case 0:
	  turn(90);
	  *car_degree = 90;
	  break;
	case 180:
	  turn(-90);
	  *car_degree = 90;
	  break;
	case 270:
	  turn(180);
	  *car_degree = 90;
	  break;
	}
      }else if(*car_y < move_y){
	switch(*car_degree){
	case 0:
	  turn(-90);
	  *car_degree = 270;
	  break;
	case 90:
	  turn(180);
	  *car_degree = 270;
	  break;
	case 180:
	  turn(90);
	  *car_degree = 270;
	  break;
	}
      }
    
    /* 目標のy座標まで移動する */
    while(*car_y != move_y){
	if(*car_y > move_y){
	  if(block[*car_y-1][*car_x] != AFTER_MOVE_BLOCK){
	    (*car_y)--;
	    straight(35);
	    //to_color(RED);
	  }else{
	    break;
	  }
	}else{
	  if(block[*car_y+1][*car_x] != AFTER_MOVE_BLOCK){
	    (*car_y)++;
	    straight(35);
	    //to_color(RED);
	  }else{
	    break;
	  }
	}
      }
    }

    if(*car_x == move_x){
      flag1 = true;
    }

    if(*car_y == move_y){
      flag2 = false;
    }
 

  }while(flag1 != true && flag2 != true);
  
}

void MoveUtil::back_move(int car_degree,int* car_x,int* car_y){
  switch(car_degree){
  case 0:
    (*car_x)--;
    back(450);
    break;
  case 90:
    (*car_y)++;
    back(420);
    break;
  case 180:
    (*car_x)++;
    back(450);
    break;
  case 270:
    (*car_y)--;
    back(420);
    break;
  }

}

/* 引数によって機体のハンドを動かす */
void MoveUtil::hand_move(int jud){
  while(1){                                                                                                                                                                                 
    handWheel.setPWM(jud);                                                                                                                                                                            
    msg_f(handWheel.getCount(), 3);                                                                                                                                                                   
    if(handWheel.getCount() > 60){                                                                                                                                                                    
      handWheel.stop();  
      break;                                                                                                                                                                                           
    }                                                                                                                                                                                                  
  }         
}

/* 色に関するクラス */
class Color_recognition{
private:
  colorid_t box; // 色 
  ColorSensor colorSensor; // 色のセンサ
public:
  Color_recognition();
  void GetColor();
  int OutputColor();
};


/* 初期化 */  
Color_recognition::Color_recognition():
  colorSensor(PORT_2) // センサのポート指定
{
  box = colorSensor.getColorNumber(); // 色を取得
}

// 何の色かを判別
void Color_recognition::GetColor()
{
  box = colorSensor.getColorNumber(); // 色を取得
}

// 判別した色をLCDに表示
int Color_recognition::OutputColor()
{

  switch(box){
  case NONE:
    msg_f("None...", 1); // LCDに出力
    break;
  case BLACK:
    msg_f("Black!!", 1); // LCDに出力
    break;
  case BLUE:
    msg_f("Blue!!", 1); // LCDに出力
    break;
  case GREEN:
    msg_f("Greeeeeen!!", 1); // LCDに出力
    break;
  case YELLOW:
    msg_f("Yello!!", 1); // LCDに出力
    break;
  case RED:
    msg_f("Red!!", 1); // LCDに出力
    break;
  case WHITE:
    msg_f("White!!", 1); // LCDに出力
    break;
  default:
    break;
  }

  return box;

}

/* メインタスク */
void main_task(intptr_t unused) {
  
  Map_Move map;
  MoveUtil tai;
  Color_recognition color;
  Code_Solve code;
  int code_num = 84722;
  int solve_num[5];
  int count;
  int i,j;
  Motor handWheel(PORT_A);
  Motor leftWheel(PORT_C);
  Motor rightWheel(PORT_B);
  count = 0; 

  //tai.to_color(RED);
  

  /*
  while(1){
    handWheel.setPWM(1);
    msg_f(handWheel.getCount(), 3);  
    if(handWheel.getCount() > 60){
    handWheel.stop();
      break;
    }
  }

  while(1){
    handWheel.setPWM(-1);
    msg_f(handWheel.getCount(), 4);
    if(handWheel.getCount() < 0){
      handWheel.stop();
      break;
    }
  }
  */
  
  code.Solve(solve_num,code_num);
  map.block_jud(solve_num); // 暗号よりブロックの初期配置の計算
  
  // ブロックまで移動                                                                                                                                                                                   
  map.priority_move(&map.move_x,&map.move_y,map.block); // 優先順位決定                                                                                                                                 
  tai.purpose_move(&map.car_x,&map.car_y,map.move_x,map.move_y,&map.car_degree,map.block,1); // 目的まで移動                                                                                            
  map.block[map.car_y][map.car_x] = NO_EXIST; // マップの更新                                                                                                                                          \
                                                                                                                                                                                                          
  // ブロックを指定の位置まで移動させる                                                                                                                                                                 
  map.move_point(RED,&map.move_x,&map.move_y,map.block); // ブロックの色により向かう場所の決定                                                                                                          
  tai.purpose_move(&map.car_x,&map.car_y,map.move_x,map.move_y,&map.car_degree,map.block,-1); // 目的まで移動                                                                                          \
                                                                                                                                                                                                          
  // 次のブロックを探すために一個前に戻る                                                                                                                                                               
  map.block[map.move_y][map.move_x] = AFTER_MOVE_BLOCK; // マップの更新                                                                                                                                 
  tai.back_move(map.car_degree,&map.car_x,&map.car_y); // 一個前の座標に移動     


  while(1) { 
    /*    
    // ブロックまで移動                                                                                                                                                                
    map.priority_move(&map.move_x,&map.move_y,map.block); // 優先順位決定                                                                                                                     
    tai.purpose_move(&map.car_x,&map.car_y,map.move_x,map.move_y,&map.car_degree,map.block,1); // 目的まで移動                                                                             
    map.block[map.car_y][map.car_x] = NO_EXIST; // マップの更新                                                                                                                                             
    // ブロックを指定の位置まで移動させる                                                                                                                            
    map.move_point(RED,&map.move_x,&map.move_y,map.block); // ブロックの色により向かう場所の決定                         
    tai.purpose_move(&map.car_x,&map.car_y,map.move_x,map.move_y,&map.car_degree,map.block,-1); // 目的まで移動                                                                                            
    // 次のブロックを探すために一個前に戻る                                                                                                                                                       
    map.block[map.move_y][map.move_x] = AFTER_MOVE_BLOCK; // マップの更新                                                                                                                       
    tai.back_move(map.car_degree,&map.car_x,&map.car_y); // 一個前の座標に移動
  
    // 終了条件
    for(i = 0; i < 4; i++){                                                     
      for(j = 0; j < 4; j++){                                                   
        if(map.block[i][j] == AFTER_MOVE_BLOCK){                                
          count++;                                                              
        }                                                                       
      }                                                                         
    }               
 
    if(count == N){
      break;
    }else{
      count = 0;
    }
    
    */
    // 左ボタンを長押し、それを捕捉する
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      break;
    }
  }

  msg_f("Stopped.", 1);


  ext_tsk(); // tasl end
}

