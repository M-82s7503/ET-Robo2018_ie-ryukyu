#include "Straight.h"

/*
Straight::Straight(Motor* l_Wheel, Motor* r_Wheel):
  Moving(l_Wheel, r_Wheel),
  distMeasure(l_Wheel, r_Wheel)
{}*/
Straight::Straight(Pointers pt_s):
  Moving(pt_s), To_Vector_IF(),
  distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{}
Straight::Straight(Pointers pt_s, int base_pwm):
  Moving(pt_s), To_Vector_IF(),
  distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{
  setBase_PWM(base_pwm);
}

void Straight::setBase_PWM(int base_pwm) {
  speed = base_pwm;
}

// オーバーライド
void Straight::setVector(Enums::Directs ForB, int distance) {
  distMeasure.init();
  // 「向き」を指定
  direct = ForB;
  dist = distance;
}
// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Straight::run(Enums::Directs ForB, int distance) {
    setVector(ForB, distance);
    Moving::run();
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
  //msg_f( (leftWheel->getCount()+rightWheel->getCount())/2, 3);
  //msg_f(dist, 4);
  //clock.wait(2000);

  // break condition なので。
  return distMeasure.getNowDist(Enums::LR_AVG) >= dist;
}

