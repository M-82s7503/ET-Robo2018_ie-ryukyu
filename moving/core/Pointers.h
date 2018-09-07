#ifndef POINTERS_
#define POINTERS_
#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
//#include "Clock.h"

using namespace ev3api;

class Pointers {
  public:
    Pointers(
      Motor* l_Wheel, 
      Motor* r_Wheel, 
      ColorSensor* c_Sensor,
      TouchSensor* t_Sensor
    );
    //Clock getClock();
    Motor* getLeftWheel();
    Motor* getRightWheel();
    ColorSensor* getColorSensor();
    TouchSensor* getTouchSensor();

  private:
    Motor* leftWheel;
    Motor* rightWheel;
    ColorSensor* colorSensor;
    TouchSensor* touchSensor;
    //const int8_t mThreshold = 20;
    //const int8_t base_pwm = (Motor::PWM_MAX) / 4;
};


#endif  // POINTERS_H_
