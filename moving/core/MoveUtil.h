#include <cstdlib>
#include "ev3.h"
#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Clock.h"
#include "Port.h"
#include <ColorSensor.h>

using namespace ev3api;

class MoveUtil{
private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;
  Clock clock;
  int speed;
  int pwm;
  uint32_t E_time;
public:
  MoveUtil();
  void turn(int degree);
  void straight(int distance);
  void stop();
  void to_color(int color);
};
