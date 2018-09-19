#include "MoveUtil_Block.hpp"


//初期化
MoveUtil_Block::MoveUtil_Block():
    MoveUtil(), handWheel(PORT_A)
{
  // ブロック並べ pid 系の変数
  sensor_val = colorSensor.getBrightness();
  target_val = 11;
}


/**
 *  ブロック並べに必要な動き
 */

//指定の距離進む                                                                                                                                                       
void MoveUtil_Block::back(int distance){
  startDig = leftWheel.getCount();
  endDig = startDig - (distance * 9 / 8);

  while (1) {
    msg_f("straight...", 1);
    leftWheel.setPWM(-speed);
    rightWheel.setPWM(-speed);

    //終了判定。前進しているか後進しているかで分岐
    if(distance >=0){
        if (leftWheel.getCount() >= endDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
    }else{
        if (leftWheel.getCount() <= endDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
    }
  }
}

//目標の座標まで移動する
void MoveUtil_Block::purpose_move(int* car_x,int* car_y,int move_x,int move_y,int* car_degree,int block[4][4],int jud){
  
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

void MoveUtil_Block::back_move(int car_degree,int* car_x,int* car_y){
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


/* ブロック並べの際のpid制御 */
float MoveUtil_Block::block_pid(int8_t sensor_val,int8_t target_val){
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
void MoveUtil_Block::pid_straight(int distance){
  E_time = distance * 4.7;
  clock.reset();

  while (1) {
    sensor_val = colorSensor.getBrightness();
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


/* 引数によって機体のハンドを動かす */
void MoveUtil_Block::hand_move(int jud){
  while(1){                                                                                                                                                                                 
    handWheel.setPWM(jud);                                                                                                                                                                            
    msg_f(handWheel.getCount(), 3);                                                                                                                                                                   
    if(handWheel.getCount() > 60){                                                                                                                                                                    
      handWheel.stop();  
      break;                                                                                                                                                                                           
    }                                                                                                                                                                                                  
  }         
}
