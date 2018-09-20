/*

2018/09/20
[ver1.3]

*/

#ifndef MOVEUTIL_H_
#define MOVEUTIL_H_

#include "ev3.h"
#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Port.h"
#include "ColorSensor.h"
#include "Clock.h"

using namespace ev3api;

class MoveUtil{
protected:
  Motor leftWheel;
  Motor rightWheel;
  Motor centerArm;
  ColorSensor colorSensor;
  Clock clock;

  bool rightSearch;
  int speed;
  int32_t startLeftDig;//開始時左タイヤ角位置
  int32_t startRightDig;//開始時の右タイヤ角位置
  int32_t endLeftDig;//終了左タイヤ角位置
  int32_t endRightDig;//終了右タイヤ角位置

public:
  MoveUtil();
  void turn(int degree);
  void turn(int degree,int side);
  void straight(int distance);
  void stop();
  void to_color(int color);
  int to_color_turn(int color, int L_dig, int R_dig, int nagasi_dig);
  void resetArm();
  void raiseArm(int degree, int pwm);
  void setSpeed(int a);
};
#endif  // MOVEUTIL_H_

