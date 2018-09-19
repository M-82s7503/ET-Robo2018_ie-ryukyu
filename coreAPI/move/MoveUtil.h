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
  ColorSensor colorSensor;
  Clock clock;

  bool rightSearch;
  int speed;
  int pwm;
  int32_t startDig;//開始時の角位置
  int32_t endDig;//終了角位置

public:
  MoveUtil();
  void turn(int degree);
  void turn(int degree,int side);
  void straight(int distance);
  void stop();
  void to_color(int color);
  int to_color_turn(int color);

};
#endif  // MOVEUTIL_H_
