#include "MoveTemps.h"

/*
MoveTemps::MoveTemps(Motor* l_Wheel, Motor* r_Wheel):
  Moving(l_Wheel, r_Wheel),
  distMeasure(l_Wheel, r_Wheel)
{}*/
MoveTemps::MoveTemps(Pointers pt_s):
  distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
  , mv_straight(pt_s)
  , mv_turn(pt_s)
{}
MoveTemps::MoveTemps(Pointers pt_s, int base_pwm):
  distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
  , mv_straight(pt_s, base_pwm)
  , mv_turn(pt_s, base_pwm)
{
  setBase_PWM(base_pwm);
}

void MoveTemps::setBase_PWM(int base_pwm) {
  speed = base_pwm;
}


//###  少し複雑な動きを実行  ###//
// 線（指定した色）の真上に、ロボを乗せる
void MoveTemps::ride_onLine(Enums::Directs ForB, int dist, Enums::Colors line_c, Enums::Colors other_c) {
  bool isFoundColor = false;
  int8_t divide = dist/30;

  for (int i=1; i<=divide; ++i) {
    isFoundColor = searchColor(other_c, Enums::LEFT, 90/(i*i));
    isFoundColor = searchColor(line_c, Enums::RIGHT, 90/(i*i));
    if (!isFoundColor) {
      isFoundColor = searchColor(other_c, Enums::LEFT, 90);
      isFoundColor = searchColor(line_c, Enums::RIGHT, 90);
    }
    mv_straight.run(ForB, 30);
    dist -= 30;
  }

}

bool MoveTemps::searchColor(Enums::Colors color, Enums::Directs first_search_d, int deg) {
  bool isFoundColor = false;
  Enums::Directs against_d = (first_search_d == Enums::LEFT) ? Enums::RIGHT : Enums::LEFT;

  isFoundColor = mv_turn.to_color_turn(color, first_search_d, deg);
  if (!isFoundColor) {
    mv_turn.run(Enums::RIGHT, deg);
    isFoundColor = mv_turn.to_color_turn(color, against_d, deg);
    if (!isFoundColor) {
      mv_turn.run(Enums::LEFT, deg);
    }
  }
  return isFoundColor;
}

