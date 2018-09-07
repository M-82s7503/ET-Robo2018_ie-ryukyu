#include "MoveUtil.h"


//初期化
MoveUtil::MoveUtil():
  leftWheel(PORT_C),rightWheel(PORT_B),colorSensor(PORT_2)
{
  speed = 20;
  pwm = (Motor::PWM_MAX)/6;
}

//指定の角度分曲がる(-180~180)
void MoveUtil::turn(int degree) {
  E_time = abs(degree) * 7.5;
  clock.reset();//クロックをリセット

  while (1) {
    msg_f("turn...", 1);
    //degreeが0以上で右回転、未満で左回転
    if (degree >= 0){
      leftWheel.setPWM(speed);
      rightWheel.setPWM(-speed);
    }else{
      leftWheel.setPWM(-speed);
      rightWheel.setPWM(speed);
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
  msg_f("straight...", 1);
  leftWheel.setPWM(speed);
  rightWheel.setPWM(speed);

  if (clock.now() >= E_time){
    leftWheel.stop();
    rightWheel.stop();
    break;
    }
  }
}
void MoveUtil::stop(){
  leftWheel.stop();
  rightWheel.stop();
}

void MoveUtil::to_color(int color)
{
    while(1) {
        leftWheel.setPWM(pwm);
        rightWheel.setPWM(pwm);
        if (colorSensor.getColorNumber() == color) {
                break;
        }
    }
}
