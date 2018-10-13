#include "Map_Move.hpp"

/* 初期化 */
Map_Move::Map_Move(Map* map_p):
  mvUtil()
{
  car_x = 0;
  car_y = 2;
  car_degree = 0;

  map = map_p;
}


/* 運ぶブロックの優先順位を決める */
void Map_Move::priority_move()
{
  int i,j;
  int box,distance;

  distance = 100;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){

      if(map->blocks[i][j] == BEFORE_MOVE_BLOCK){
        box = abs(i - car_y)+ abs(j - car_x);
        if(distance > box){
          move_y = i;
          move_x = j;
          distance = box;
        }
      }

    }
  }
}

/* ブロックを移動させる座標を決定する */
void Map_Move::move_point(int block_color) {
  int i,j;
  int box,distance;

  distance = 100;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){

      if(map->colors[i][j] == block_color){
        box = abs(i - car_y)+ abs(j - car_x);
        if(distance > box){
          move_y = i;
          move_x = j;
          distance = box;
        }
      }

    }
  }
}



/* 次に向かうべきブロッック置き場まで移動する */
// オーバーロード：座標指定 ver
void Map_Move::purpose_move(int mv_x, int mv_y, int deg){
  move_x = mv_x;
  move_y = mv_y;
  purpose_move(deg);
}

/* 次に向かうべきブロッック置き場まで移動する */
void Map_Move::purpose_move(int deg){
  
  mvUtil.raiseArm(deg, 5);
  bool flag1,flag2;

  flag1 = flag2 = false;

  // ブロックの移動                                                              
  if(deg == -1){
    mvUtil.straight(50);
  }


  do{
    /* 機体の角度の調整 */
    if(car_x != move_x){
      if(car_x < move_x){
	switch(car_degree){
	case 90:
	  mvUtil.turn(90);
	  car_degree = 0;
	  break;
	case 180:
	  mvUtil.turn(-180);
	  car_degree = 0;
	  break;
	case 270:
	  mvUtil.turn(-90);
	  car_degree = 0;
	  break;
	}
      }else{
	switch(car_degree){
	case 0:
	  mvUtil.turn(-180);
	  car_degree = 180;
	  break;
	case 90:
	  mvUtil.turn(-90);
	  car_degree = 180;
	  break;
	case 270:
	  mvUtil.turn(90);
	  car_degree = 180;
	  break;
	}
      }

      /* 目標のx座標まで移動する */
      while(car_x != move_x){
	if(car_x > move_x){
	  if(map->blocks[car_y][car_x-1] != AFTER_MOVE_BLOCK){
	    mvUtil.straight(350);
            if(car_y != move_y && (car_x-1) != move_x){
              mvUtil.straight(100);
            }
            (car_x)--;
	  }else{
	    break;
	  }
	}else{ 
	  if(map->blocks[car_y][car_x+1] != AFTER_MOVE_BLOCK){
	    mvUtil.straight(350);
            if(car_y != move_y && (car_x+1) != move_x){
              mvUtil.straight(100);
            }
	    (car_x)++;
	  }else{ 
	    break;
	  }
	}
      }
    }

    if(car_y != move_y){
      /* 機体の角度の調整 */
      if(car_y > move_y){
	switch(car_degree){
	case 0:
	  mvUtil.turn(-90);
	  car_degree = 90;
	  break;
	case 180:
	  mvUtil.turn(90);
	  car_degree = 90;
	  break;
	case 270:
	  mvUtil.turn(-180);
	  car_degree = 90;
	  break;
	}
      }else if(car_y < move_y){
	switch(car_degree){
	case 0:
	  mvUtil.turn(90);
	  car_degree = 270;
	  break;
	case 90:
	  mvUtil.turn(-180);
	  car_degree = 270;
	  break;
	case 180:
	  mvUtil.turn(-90);
	  car_degree = 270;
	  break;
	}
      }
    
    /* 目標のy座標まで移動する */
    while(car_y != move_y){
	if(car_y > move_y){
	  if(map->blocks[car_y-1][car_x] != AFTER_MOVE_BLOCK){
	    mvUtil.straight(300);
	    if((car_y+1) != move_y && car_x != move_x){
              mvUtil.straight(100);
            }
	    (car_y)--;
	  }else{
	    break;
	  }
	}else{
	  if(map->blocks[car_y+1][car_x] != AFTER_MOVE_BLOCK){
	    mvUtil.straight(300);
	    if((car_y+1) != move_y && car_x != move_x){
              mvUtil.straight(100);
            }
	    (car_y)++;
	  }else{
	    break;
	  }
	}
      }
    }

    if(car_x == move_x){
      flag1 = true;
    }

    if(car_y == move_y){
      flag2 = false;
    }
 

  }while(flag1 != true && flag2 != true);

}


/* １つ前のブロック置き場に戻る */
void Map_Move::back_move(){
  switch(car_degree){
  case 0:
    (car_x)--;
    mvUtil.straight(-420);
    break;
  case 90:
    (car_y)++;
    mvUtil.straight(-360);
    break;
  case 180:
    (car_x)++;
    mvUtil.straight(-420);
    break;
  case 270:
    (car_y)--;
    mvUtil.straight(-360);
    break;
  }

}

