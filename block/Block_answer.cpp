#include "Block_answer.hpp"


Block_answer::Block_answer():
  colorSensor(PORT_2) // センサのポート指定
  , tai()
{}

void Block_answer::run() {
  int count = 0; 
  int a[3] = {5,3,4};
  int k = 0;

  // マップを作成し、初期化する。
  Map map;
  code.Solve(solve_num, code_num);  //暗号を解読し、solve_num[5] に保存する
  map.block_jud(solve_num); // 暗号よりブロックの初期配置の計算
  
  // 【要確認】仮想ロボを起動！
  Map_Move mapMV(&map);

  tai.to_color(5);

  
  /*  <<<  1こだけ動かして離脱パターン  >>>
    */
  // ブロックまで移動       
  mapMV.priority_move(); // 優先順位決定               
  mapMV.purpose_move(90); // 目的まで移動                                    
  map.blocks[mapMV.car_y][mapMV.car_x] = NO_EXIST; // マップの更新
                           
  // ブロックを指定の位置まで移動させる       
  tai.straight(50);
  mapMV.move_point(BLUE); // ブロックの色により向かう場所の決定
  mapMV.purpose_move(0,3, 30); // 目的まで移動                                  
  // 次のブロックを探すために一個前に戻る      
  map.blocks[0][3] = AFTER_MOVE_BLOCK; // マップの更新     
  mapMV.back_move(); // 一個前の座標に移動      



  /*  <<<  完全版  >>>
   */
  // ブロックまで移動       
  mapMV.priority_move(); // 優先順位決定               
  mapMV.purpose_move(90); // 目的まで移動                                    
  map.blocks[mapMV.car_y][mapMV.car_x] = NO_EXIST; // マップの更新
                           
  // ブロックを指定の位置まで移動させる       
  tai.straight(50);
  mapMV.move_point(BLUE); // ブロックの色により向かう場所の決定
  mapMV.purpose_move(30); // 目的まで移動                                  
  // 次のブロックを探すために一個前に戻る      
  map.blocks[mapMV.move_y][mapMV.move_x] = AFTER_MOVE_BLOCK; // マップの更新     
  mapMV.back_move(); // 一個前の座標に移動      

  int8_t color = -1;
  while(1) { 
    // ブロックまで移動     
    mapMV.priority_move(); // 優先順位決定 
    mapMV.purpose_move(90); // 目的まで移動                   
    map.blocks[mapMV.car_y][mapMV.car_x] = NO_EXIST; // マップの更新                         
    // ブロックを指定の位置まで移動させる 
    color = colorSensor.getColorNumber();
    if(color != 0 && color != 1 && color != 6){       
      mapMV.move_point(color); // ブロックの色により向かう場所の決定                         
    }else{
      mapMV.move_point(a[k]); // ブロックの色により向かう場所の決定                         
    }
    mapMV.purpose_move(30); // 目的まで移動                                  
    // 次のブロックを探すために一個前に戻る                                   
    map.blocks[mapMV.move_y][mapMV.move_x] = AFTER_MOVE_BLOCK; // マップの更新   
    mapMV.back_move(); // 一個前の座標に移動
  
    // 終了条件
    int i,j;
    for(i = 0; i < 4; i++){              
      for(j = 0; j < 4; j++){            
        if(map.blocks[i][j] == AFTER_MOVE_BLOCK){                                
          count++;    
        }             
      }               
    }   
            
    k++;

    if(count == N){
      break;
    }else{
      count = 0;
    }

  }

  mapMV.purpose_move(3,2, 90); // 目的まで移動

  switch(mapMV.car_degree){
  case 90:
    tai.turn(90);
    break;
  case 180:
    tai.turn(-180);
    break;
  case 270:
    tai.turn(-90);
    break;
  }
  msg_f("Stopped.", 1);


}

