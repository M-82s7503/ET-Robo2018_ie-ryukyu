#include "MoveUtil.h"

//初期化
MoveUtil::MoveUtil():
    leftWheel(PORT_C),rightWheel(PORT_B), handWheel(PORT_A), 
    colorSensor(PORT_2)
{
  speed = 20;
  pwm = (Motor::PWM_MAX)/6;
}

//指定の角度分曲がる(-180~180)
void MoveUtil::turn(int degree) {
  startDig = leftWheel.getCount();
  endDig = startDig + (degree * 13 / 9);

  while (1) {
    msg_f("turn... 13 / 9", 1);
    //degreeが0以上で右回転、未満で左回転
    if (degree >= 0){
      leftWheel.setPWM(speed);
      rightWheel.setPWM(-speed);
      if (leftWheel.getCount() >= endDig){
        leftWheel.stop();
        rightWheel.stop();
        break;
        }
    }else{
      leftWheel.setPWM(-speed);
      rightWheel.setPWM(speed);
      if (leftWheel.getCount() <= endDig){
        leftWheel.stop();
        rightWheel.stop();
        break;
        }
    }
  }
}

//sideを指定することで大回り。sideが1なら左タイヤ、-1なら右タイヤ。
void MoveUtil::turn(int degree,int side) {

  while (1) {
    if (side >= 0){
      msg_f("leftLongTurn...", 1);
      startDig = leftWheel.getCount();
      endDig = startDig + (degree * 3);
      leftWheel.setPWM(speed);
      if (leftWheel.getCount() >= endDig){
        leftWheel.stop();
        rightWheel.stop();
        break;
        }
    }else{
      msg_f("rightLongTurn...", 1);
      startDig = rightWheel.getCount();
      endDig = startDig + (degree * 3);
      rightWheel.setPWM(speed);
      if (rightWheel.getCount() >= endDig){
        leftWheel.stop();
        rightWheel.stop();
        break;
        }
    }
  }
}

//指定の距離進む
void MoveUtil::straight(int distance){

  startDig = leftWheel.getCount();
  endDig = startDig + (distance * 9 / 8);

  while (1) {
  msg_f("straight...", 1);
  leftWheel.setPWM(speed);
  rightWheel.setPWM(speed);

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


void MoveUtil::stop(){
  leftWheel.stop();
  rightWheel.stop();
}

void MoveUtil::to_color(int color){
    while(1) {
        leftWheel.setPWM(pwm);
        rightWheel.setPWM(pwm);
        if (colorSensor.getColorNumber() == color) {
                break;
        }
    }
}

//右を90度探してなかったら左を180度探す。成功で1を返す、失敗で0を返す。
int MoveUtil::to_color_turn(int color){
  startDig = leftWheel.getCount();
  endDig = startDig + 130;
  rightSearch = true;

  while(1) {

    if (colorSensor.getColorNumber() == color) {
      leftWheel.stop();
      rightWheel.stop();
      return 1;
      }

    if(rightSearch){
      leftWheel.setPWM(speed);
      rightWheel.setPWM(-speed);
      if(leftWheel.getCount() >= endDig){
        rightSearch = false;
      }
    }else{
      endDig = startDig - 130;
      leftWheel.setPWM(-speed);
      rightWheel.setPWM(speed);
      if(leftWheel.getCount() <= endDig){
        turn(90);
        return 0;
      }

    }
  }
}








/**
 *  ブロック並べに必要な動き
 */

//指定の距離進む                                                                                                                                                       
void MoveUtil::back(int distance){
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
void MoveUtil::purpose_move(int* car_x,int* car_y,int move_x,int move_y,int* car_degree,int block[4][4],int handdegree){
  
  handWheel.setPWM(handdegree);

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
	    straight(450);
	  }else{
	    break;
	  }
	}else{ 
	  if(block[*car_y][*car_x+1] != AFTER_MOVE_BLOCK){
	    (*car_x)++;
	    straight(450);
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
	  turn(90);
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
	    straight(400);
	  }else{
	    break;
	  }
	}else{
	  if(block[*car_y+1][*car_x] != AFTER_MOVE_BLOCK){
	    (*car_y)++;
	    straight(400);
	  }else{
	    break;
	  }
	}
      }
    }
     
  }while(*car_x != move_x && *car_y != move_y);
  
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


