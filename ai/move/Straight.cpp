#include "Straight.h"

/*
Straight::Straight(Motor* l_Wheel, Motor* r_Wheel):
  Moving_ex(l_Wheel, r_Wheel),
  distMeasure(l_Wheel, r_Wheel)
{}*/
Straight::Straight(Pointers pt_s):
  Moving_ex(pt_s),
  distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{}
Straight::Straight(Pointers pt_s, int base_pwm):
  Moving_ex(pt_s),
  distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{
  setBase_PWM(base_pwm);
}

void Straight::setBase_PWM(int base_pwm) {
  speed = base_pwm;
}

void Straight::setVector(Enums::Directs ForB, int distance) {
  distMeasure.init();
  // 「向き」を指定
  direct = ForB;
  dist = distance;
}

float Straight::decide_pwm_r(){
  switch (direct) {
    case Enums::FRONT:
      return speed;
    case Enums::BACK:
      return -speed;
    default:
      // 明らかにおかしいので、エラー処理
      msg_f("", 2);
      msg_f("Straight direct Error", 2);
      return 20;
  }
}

float Straight::decide_pwm_l(){
  switch (direct) {
    case Enums::FRONT:
      return speed;
    case Enums::BACK:
      return -speed;
    default:
      // 明らかにおかしいので、エラー処理
      msg_f("", 2);
      msg_f("Straight direct Error", 2);
      return 20;
  }
}

bool Straight::break_condition(){
  // true の間、走り続ける。
  msg_f(leftWheel->getCount(), 2);
  // break condition なので。
  return distMeasure.getNowDist(Enums::LR_AVG) >= dist;
}

