#include "Block_answer.hpp"


void Block_answer::run() {
  int count = 0; 

  code.Solve(solve_num,code_num);
  map.block_jud(solve_num); // 暗号よりブロックの初期配置の計算
                                                                                                     
  while(1) { 
    // ブロックまで移動                                                                                                                                                                
    map.priority_move(&map.move_x,&map.move_y,map.block); // 優先順位決定                                                                                                                     
    tai.purpose_move(&map.car_x,&map.car_y,map.move_x,map.move_y,&map.car_degree,map.block,1); // 目的まで移動                                                                             
    map.block[map.car_y][map.car_x] = Map_Move::NO_EXIST; // マップの更新                                                                                                                                             
    // ブロックを指定の位置まで移動させる                                                                                                                            
    map.move_point(color.Output(),&map.move_x,&map.move_y,map.block); // ブロックの色により向かう場所の決定                         
    tai.purpose_move(&map.car_x,&map.car_y,map.move_x,map.move_y,&map.car_degree,map.block,-1); // 目的まで移動                                                                                            
    // 次のブロックを探すために一個前に戻る                                                                                                                                                       
    map.block[map.move_y][map.move_x] = Map_Move::AFTER_MOVE_BLOCK; // マップの更新                                                                                                                       
    tai.back_move(map.car_degree,&map.car_x,&map.car_y); // 一個前の座標に移動
  
    // 終了条件
    int i,j;
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
    
   

  }
    

  msg_f("Stopped.", 1);


}

