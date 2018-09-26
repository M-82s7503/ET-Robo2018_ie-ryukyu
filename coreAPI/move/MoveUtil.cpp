/*

2018/09/20
[ver1.5]

*/

#include "MoveUtil.h"

//初期化
MoveUtil::MoveUtil():
    leftWheel(PORT_C),rightWheel(PORT_B),centerArm(PORT_A),colorSensor(PORT_2)
{
  speed = 20;
}

//指定の角度分曲がる(-180~180)
void MoveUtil::turn(int degree) {
  startLeftDig = leftWheel.getCount();
  startRightDig = rightWheel.getCount();
  endLeftDig = startLeftDig + (degree * 3 / 2);  //計算上は、3/2
  endRightDig = startRightDig - (degree * 3 / 2);

  while (1) {
    //msg_f("turn... 3 / 2", 1);

    if (degree>=0){
      leftWheel.setPWM(speed);
      rightWheel.setPWM(-speed);
      if (endLeftDig <= leftWheel.getCount()){leftWheel.stop();}
      if (endRightDig >= rightWheel.getCount()){rightWheel.stop();}
      if (endLeftDig <= leftWheel.getCount() && endRightDig >= rightWheel.getCount()){break;}
    }else{
      leftWheel.setPWM(-speed);
      rightWheel.setPWM(speed);
      if (endLeftDig >= leftWheel.getCount()){leftWheel.stop();}
      if (endRightDig <= rightWheel.getCount()){rightWheel.stop();}
      if (endLeftDig >= leftWheel.getCount() && endRightDig <= rightWheel.getCount()){break;}
    }


    /*
    if (endLeftDig < leftWheel.getCount()){
      leftWheel.setPWM(speed);
    }else if(endLeftDig > leftWheel.getCount()){
      leftWheel.setPWM(-speed);
    }else{
      leftWheel.stop();
    }

    if (endRightDig < rightWheel.getCount()){
      rightWheel.setPWM(speed);
    }else if(endRightDig > rightWheel.getCount()){
      rightWheel.setPWM(-speed);
    }else{
      rightWheel.stop();
    }

    if (endLeftDig == leftWheel.getCount() && endRightDig == rightWheel.getCount()){
      break;
    }
    */
  }
}


//sideを指定することで大回り。sideが1なら左タイヤ、-1なら右タイヤ。
void MoveUtil::turn(int degree,int side) {

  while (1) {
    if (side >= 0){
      //msg_f("leftLongTurn...", 1);
      startLeftDig = leftWheel.getCount();
      endLeftDig = startLeftDig + (degree * 3);
      leftWheel.setPWM(speed);
      if (leftWheel.getCount() >= endLeftDig){
        leftWheel.stop();
        rightWheel.stop();
        break;
        }
    }else{
      //msg_f("rightLongTurn...", 1);
      startRightDig = rightWheel.getCount();
      endRightDig = startRightDig + (degree * 3);
      rightWheel.setPWM(speed);
      if (rightWheel.getCount() >= endRightDig){
        leftWheel.stop();
        rightWheel.stop();
        break;
        }
    }
  }
}


//指定の距離進む
// 9/26 "-"" でバックするように改良。
void MoveUtil::straight(int distance){
  startLeftDig = leftWheel.getCount();
  endLeftDig = startLeftDig + (distance * 9 / 8);
  speed = speed * (distance / abs(distance));

  while (1) {
    //msg_f("straight...", 1);
    leftWheel.setPWM(speed);
    rightWheel.setPWM(speed);

    //終了判定。前進しているか後進しているかで分岐
    if(distance >=0){
      if (leftWheel.getCount() >= endLeftDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
      }else{
        if (leftWheel.getCount() <= endLeftDig){
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
// 修正 → 左側に L_dig度、右側に R_dig度、色（color）を 探しに行く。
int MoveUtil::to_color_turn(int color, int L_dig, int R_dig, int nagasi_dig){
  // 前に進む方のタイヤでやりたい。
  endLeftDig = leftWheel.getCount() + (R_dig * 3 / 2);
  rightSearch = true;

  if (colorSensor.getColorNumber() == color) {
    //leftWheel.stop();
    //rightWheel.stop();
    return 1;
  }


  while(1) {

    if (colorSensor.getColorNumber() == color) {
      //leftWheel.stop();
      //rightWheel.stop();
      break;
    }

    if(rightSearch){
      leftWheel.setPWM(speed);
      rightWheel.setPWM(-speed);
      if(leftWheel.getCount() >= endLeftDig){
        turn(-R_dig);
        endRightDig = rightWheel.getCount() + (L_dig * 3 / 2);
        rightSearch = false;
      }
    }else{
      leftWheel.setPWM(-speed);
      rightWheel.setPWM(speed);
      if(rightWheel.getCount() >= endRightDig){
        turn(L_dig);
        return 0;
      }
    }
  }
  
  if (rightSearch) {
    turn(nagasi_dig);
  } else {
    turn(-nagasi_dig);
  }
  return 1;
}


void MoveUtil::resetArm() {
  uint32_t b_time = clock.now();//msec
  // 限界までアームを下げる。
  while( (clock.now()-b_time) < 800 ) {
    centerArm.setPWM(-20);
  }
  centerArm.reset();
}


// degree：絶対角度を指定する。0〜90度
void MoveUtil::raiseArm(int degree, int pwm) {
    if (degree < 0) {
        degree = 0;
    } else if (90 < degree) {
        degree = 90;
    }
    if (pwm < 0) { pwm = 0; }

    // 上げる
    if (centerArm.getCount() < degree) {
        centerArm.setPWM(pwm);
        while (centerArm.getCount() < degree) {}
    }
    // 下げる
    if (degree < centerArm.getCount()) {
        centerArm.setPWM(-pwm);
        while (degree < centerArm.getCount()) {}
    }

    centerArm.stop();
    return;
}


void MoveUtil::setSpeed(int a){
  this->speed = a;
}



void MoveUtil::back(int distance){
  startLeftDig = leftWheel.getCount();
  endLeftDig = startLeftDig - (distance * 9 / 8);

  while (1) {
    //msg_f("straight...", 1);
    leftWheel.setPWM(-speed);
    rightWheel.setPWM(-speed);

    //終了判定。前進しているか後進しているかで分岐
    if(distance >=0){
        if (leftWheel.getCount() >= endLeftDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
    }else{
        if (leftWheel.getCount() <= endLeftDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
    }
  }
}


