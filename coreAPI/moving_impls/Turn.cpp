#include "Turn.h"

/*
Turn::Turn(Motor* l_Wheel, Motor* r_Wheel):
  Moving(l_Wheel, r_Wheel),
  degMeasure(l_Wheel, r_Wheel)
{}*/
Turn::Turn(Pointers pt_s):
  Moving(pt_s), To_Vector_IF(), To_Color_IF()
{}
Turn::Turn(Pointers pt_s, int base_pwm):
  Moving(pt_s), To_Vector_IF(), To_Color_IF()
{
  setBase_PWM(base_pwm);
}

void Turn::setBase_PWM(int base_pwm) {
  speed = base_pwm;
}

// オーバーライド : To Vector
void Turn::setVector(Enums::Directs LorR, int degree) {
    // 「向き」を指定
    direct = LorR;
    // 終了条件を指定
    deg = degree;
    startLeftDig = leftWheel->getCount();
    startRightDig = rightWheel->getCount();
    endLeftDig = startLeftDig + (degree * 3 / 2);  //計算上は、3/2
    endRightDig = startRightDig - (degree * 3 / 2);
}
// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Turn::run(Enums::Directs LorR, int degree) {
    setVector(LorR, degree);
    // フラグを立てる
    isToColor_mode = false;
    Moving::run();
}

// オーバーライド : To Color
void Turn::setToColor(Enums::Directs LorR, Enums::Colors color) {
    // 「向き」を指定
    direct = LorR;
    // 終了条件を指定
    till_color = color;
}
void Turn::run(Enums::Directs LorR, Enums::Colors color) {
    setToColor(LorR, color);
    // フラグを立てる
    isToColor_mode = true;
    isToColorTurn_mode = false;
    Moving::run();
}

// To color turn
bool Turn::to_color_turn(Enums::Colors color, Enums::Directs LorR, int degree) {
    setToColor(LorR, color);
    setVector(LorR, degree);
    // フラグを立てる
    isToColor_mode = true;
    isToColorTurn_mode = true;
    // 色が見つかれば、true になってるはず。
    isFoundColor = false;
    Moving::run();
    return isFoundColor;
}


float Turn::decide_pwm_r(){
  if (isToColor_mode) {
    switch (direct) {
      case Enums::Directs::LEFT:
        return speed;
      case Enums::Directs::RIGHT:
        return -speed;
      default:
        // 明らかにおかしいので、エラー処理
        return 0;
    }
  } else {
    switch (direct) {
      case Enums::Directs::LEFT:
        // ズレた場合は、とりあえず止める。
        if (endRightDig <= rightWheel->getCount()){
          rightWheel->stop();
          return 0;
        } else return speed;  //右タイヤは、左回転の時＋。
      case Enums::Directs::RIGHT:
        if (endRightDig >= rightWheel->getCount()){
          rightWheel->stop();
          return 0;
        } else return -speed;
      default:
        // 明らかにおかしいので、エラー処理
        return 0;
    }
  }
}

float Turn::decide_pwm_l(){
  if (isToColor_mode) {
    switch (direct) {
      case Enums::Directs::LEFT:
        return -speed;
      case Enums::Directs::RIGHT:
        return speed;
      default:
        // 明らかにおかしいので、エラー処理
        return 0;
    }
  } else {
    switch (direct) {
      case Enums::Directs::LEFT:
        if (endLeftDig >= leftWheel->getCount()){
          leftWheel->stop();
          return 0;
        } else return -speed;
      case Enums::Directs::RIGHT:
        if (endLeftDig <= leftWheel->getCount()){
          leftWheel->stop();
          return 0;
        } else return speed;
      default:
        // 明らかにおかしいので、エラー処理
        return 0;
    }
  }
}

bool Turn::break_condition(){
  if (isToColor_mode) {
    if (colorSensor->getColorNumber() == static_cast<int>(till_color)) {
      isFoundColor = true;
      return true;
    } else return false;
  } 
  if (isToColor_mode || !isToColor_mode) {
    switch (direct) {
      case Enums::Directs::LEFT:
        if (endLeftDig >= leftWheel->getCount() && endRightDig <= rightWheel->getCount()){
          return true;
        } else return false;
      case Enums::Directs::RIGHT:
        if (endLeftDig <= leftWheel->getCount() && endRightDig >= rightWheel->getCount()){
          return true;
        } else return false;
      default:
        // 明らかにおかしいので、エラー処理
        msg_f("", 2);
        msg_f("Turn direct Error", 2);
        return true;
    }
  }
}

