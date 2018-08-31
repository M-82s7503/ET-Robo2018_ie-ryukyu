#pragma once
#include "Motor.h"
#include "ColorSensor.h"
#include "Clock.h"
#include "TouchSensor.h"

using namespace ev3api;

class Parts {
  public:
    Parts();
    Clock getClock();
    Motor getLeftWheel();
    Motor getRightWheel();
    ColorSensor getColorSensor();
    TouchSensor getTouchSensor();

  private:
    Clock clock;
    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
    TouchSensor touchSensor;
    const int8_t mThreshold = 20;
    const int8_t base_pwm = (Motor::PWM_MAX) / 4;
};
