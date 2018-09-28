#include "MoveTemps.hpp"

/*
MoveTemps::MoveTemps(Motor* l_Wheel, Motor* r_Wheel):
  Moving(l_Wheel, r_Wheel),
  distMeasure(l_Wheel, r_Wheel)
{}*/
MoveTemps::MoveTemps(Pointers ptrs):
  distMeasure(ptrs.getLeftWheel(), ptrs.getRightWheel())
  , mv_basic(ptrs)
  , mv_straight(ptrs)
  , mv_turn(ptrs)
  , clock()
{
  colorSensor = ptrs.getColorSensor();
}
MoveTemps::MoveTemps(Pointers ptrs, int base_pwm):
  distMeasure(ptrs.getLeftWheel(), ptrs.getRightWheel())
  , mv_basic(ptrs)
  , mv_straight(ptrs, base_pwm)
  , mv_turn(ptrs, base_pwm)
  , clock()
{
  setBase_PWM(base_pwm);
  colorSensor = ptrs.getColorSensor();
}

void MoveTemps::setBase_PWM(int base_pwm) {
  speed = base_pwm;
}


//###  少し複雑な動きを実行  ###//
// 線（指定した色）の真上に、ロボを乗せる
// 最初は、 line_c を見つけた状態であるとする。（to_color_turn 実行後）
// LorR : 最初の一回はどちら側を探すかを指定できる。
void MoveTemps::ride_onLine(Enums::Directs ForB, Enums::Directs first_LorR, int dist, Enums::Colors line_c, Enums::Colors other_c) {
  int8_t divide = dist / divide_unit;
  // 色のtmp
  Enums::Colors now_c = line_c;
  Enums::Colors against_c = other_c;
  // 方向のtmp
  Enums::Directs end_d = first_LorR;
  Enums::Directs against_d;

  for (int i=1; i<=divide; ++i) {
    now_c = static_cast<Enums::Colors>(colorSensor->getColorNumber());
    against_c = (now_c == line_c) ? other_c : line_c;

    end_d = static_cast<Enums::Directs>( searchColor(against_c, end_d, 30/(i*i), -5) );
    end_d = static_cast<Enums::Directs>( searchColor(now_c, end_d, 30/(i*i), 5) );

    against_d = (end_d == Enums::LEFT) ? Enums::RIGHT : Enums::LEFT;
    // 見つからなかった場合は、探索範囲を広げて探す。
/*    if (!isFound) {
      isFound = searchColor(against_c, Enums::LEFT, 90, 5);
      isFound = searchColor(now_c, Enums::RIGHT, 90, 5);
    }*/
    mv_straight.run(ForB, divide_unit);
    dist -= divide_unit;
  }

}

// 読み取った色が line_c なら other_c を探す。
// other_c なら、line_c を探す。
int8_t MoveTemps::searchColor(Enums::Colors color, Enums::Directs first_search_d, int deg, int nagare) {
  bool isFound = false;
  Enums::Directs end_d = first_search_d;
  Enums::Directs against_d = (end_d == Enums::LEFT) ? Enums::RIGHT : Enums::LEFT;
  Enums::Directs nagare_d = (nagare > 0) ? end_d : against_d;

  isFound = mv_turn.to_color_turn(color, end_d, deg);

  if (!isFound) {
    // 戻す
    mv_turn.run(Enums::RIGHT, deg);
    isFound = mv_turn.to_color_turn(color, against_d, deg);
    if (!isFound) {
      // 戻す
      mv_turn.run(nagare_d, deg);
      return -1;  // 失敗
    } else {
      // nagare度 分流す。
      mv_turn.run(nagare_d, nagare);
    }
    return against_d;

  } else {
    // nagare度 分流す。
    mv_turn.run(nagare_d, nagare);
  }
  return end_d;
}


// in_c : ロボがいる側の色（境界にまたがっている場合）。黒線に対して行う場合は、線の色。
// out_c : ロボがいない側の色（境界にまたがっている場合）。黒線に対して行う場合は、線以外の色。
bool MoveTemps::ride_onLine_vertical(Enums::Colors line_c, Enums::Directs start_d) {
  // アームを少し高めにする。
  int8_t armDeg = mv_basic.getArmDeg();
  mv_basic.raiseArm(35, 20);
  clock.wait(500);

  int halfDeg;
  Enums::Directs against_d = (start_d == Enums::LEFT) ? Enums::RIGHT : Enums::LEFT;

  //##  start_d 方向に、線を探しに行く  ##//
  mv_turn.to_color_turn(line_c, start_d, 180);
  mv_basic.stop();
  //##  start_d の反対方向に、線を探しに行く  ##//
  // 10度戻って、反対方向に探しに行くとき、前の色を読んで止まらないようにする。
  mv_turn.run(against_d, 10);
  mv_turn.to_color_turn(line_c, against_d, 180);
  mv_basic.stop();

  // halfDeg / 2 が、線に対して垂直になるための角度になる。
  halfDeg = ( mv_turn.getTurnedDegree() + 10 ) / 2;  // 10度分修正。
  msg_f(halfDeg, 3);
  // 垂直になるように回転
  mv_turn.run(start_d, halfDeg);
  mv_basic.stop();

  // アームを元の角度にする。
  mv_basic.raiseArm(armDeg, 15);

  return mv_turn.getIsFoundColor();
}



