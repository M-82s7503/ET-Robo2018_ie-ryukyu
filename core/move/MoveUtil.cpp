/*

2018/09/19
[ver1.1]

*/

#include "MoveUtil.h"

//初期化
MoveUtil::MoveUtil():
    leftWheel(PORT_C),rightWheel(PORT_B), 
    colorSensor(PORT_2)
{
  speed = 20;
}

//指定の角度分曲がる(-180~180)
void MoveUtil::turn(int degree) {
  startDig = leftWheel.getCount();
  endDig = startDig + (degree * 13 / 9);  //計算上は、3/2

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
        leftWheel.setPWM(speed);
        rightWheel.setPWM(speed);
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

void MoveUtil::setSpeed(int a){
  this->speed = a;
}