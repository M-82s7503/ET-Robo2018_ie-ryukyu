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
  dist = abs(distance);
}
// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Straight::run(Enums::Directs ForB, int distance) {
    setVector(ForB, distance);
    isToColor_mode = false;
    Moving::run();
}


// オーバーライドする。
void Straight::setToColor(Enums::Directs ForB, Enums::Colors color) {
    till_color = color;

    // param の処理

    // break_condision() でフラグ処理する。
}
// to_color の .run()
void Straight::run(Enums::Colors to_c, Enums::Directs ForB, int distance) {
    setVector(ForB, distance);
    setToColor(ForB, to_c);
    isToColor_mode = true;
    isFoundColor = false;
    Moving::run();
}


float Straight::decide_pwm_r(){
  // 左右の誤差を補正する。
  // 速い方の車輪の反対側に寄ってしまうが、移動後の角度誤差は最小限になるはず。
  if (dist < distMeasure.getNowDist(Enums::Directs::RIGHT)){
      rightWheel->stop();
      return 0;
  }
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
  // 左右の誤差を補正する。
  // 速い方の車輪の反対側に寄ってしまうが、移動後の角度誤差は最小限になるはず。
  if (dist < distMeasure.getNowDist(Enums::Directs::LEFT)){
      leftWheel->stop();
      return 0;
  }
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
  // break condition なので。
  if (isToColor_mode) {
    if (colorSensor->getColorNumber() == static_cast<int>(till_color)) {
        isFoundColor = true;
        // breakする。
        return true;
    }
  }
  // To Color の場合でも、制限距離になったら、終了。
  return distMeasure.getNowDist(Enums::LR_AVG) >= dist;
}

