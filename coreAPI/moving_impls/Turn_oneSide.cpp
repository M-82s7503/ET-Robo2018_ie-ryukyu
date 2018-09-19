#include "Turn_oneSide.h"

/*
Turn_oneSide::Turn_oneSide(Motor* l_Wheel, Motor* r_Wheel):
  Moving(l_Wheel, r_Wheel),
  distMeasure(l_Wheel, r_Wheel)
{}*/
Turn_oneSide::Turn_oneSide(Pointers pt_s):
  Moving(pt_s), To_Vector_IF()
{}
Turn_oneSide::Turn_oneSide(Pointers pt_s, int base_pwm):
  Moving(pt_s), To_Vector_IF()
{
  setBase_PWM(base_pwm);
}

void Turn_oneSide::setBase_PWM(int base_pwm) {
  speed = base_pwm;
}


// オーバーライド
void Turn_oneSide::setVector(Enums::Directs LorR, int deg) {
  //distMeasure.init();
  // 「どちらのタイヤを回すか」を指定
  which_Wheel = LorR;
  switch (which_Wheel) {
    case Enums::LEFT:
      startDig = leftWheel->getCount();
      break;
    case Enums::RIGHT:
      startDig = rightWheel->getCount();
      break;
    default:
      // 明らかにおかしいので、エラー処理
      msg_f("", 2);
      msg_f("Turn_oneSide which_Wheel Error", 2);
      startDig =0;
      break;
  }
  endDig = abs(deg) * 3;
  speed = (deg / abs(deg)) * abs(speed);
}
// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Turn_oneSide::run(Enums::Directs ForB, int distance) {
    setVector(ForB, distance);
    Moving::run();
}


float Turn_oneSide::decide_pwm_r(){
  switch (which_Wheel) {
    case Enums::LEFT:
      return 0;
    case Enums::RIGHT:
      return speed;
    default:
      // 明らかにおかしいので、エラー処理
      msg_f("", 2);
      msg_f("Turn_oneSide which_Wheel Error", 2);
      return 20;
  }
}

float Turn_oneSide::decide_pwm_l(){
  switch (which_Wheel) {
    case Enums::LEFT:
      return speed;
    case Enums::RIGHT:
      return 0;
    default:
      // 明らかにおかしいので、エラー処理
      msg_f("", 2);
      msg_f("Turn_oneSide which_Wheel Error", 2);
      return 20;
  }
}

bool Turn_oneSide::break_condition(){
  msg_f(endDig, 4);
  // break condition なので。
  switch (which_Wheel) {
    case Enums::LEFT:
      //msg_f( leftWheel->getCount(), 3);
      return abs(leftWheel->getCount() - startDig) >= endDig;
    case Enums::RIGHT:
      //msg_f( rightWheel->getCount(), 3);
      return abs(rightWheel->getCount() - startDig) >= endDig;
    default:
      // 明らかにおかしいので、エラー処理
      msg_f("", 2);
      msg_f("Turn_oneSide which_Wheel Error", 2);
      return true;
  }

}

