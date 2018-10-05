#ifndef POINTERS_
#define POINTERS_
#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"

using namespace ev3api;

class Pointers {
  public:
    Pointers(Pointers* ptrs_p);
    Pointers(
      Motor* c_Arm, 
      Motor* l_Wheel, 
      Motor* r_Wheel, 
      ColorSensor* c_Sensor,
      TouchSensor* t_Sensor
    );
    Motor* getCenterArm();
    Motor* getLeftWheel();
    Motor* getRightWheel();
    ColorSensor* getColorSensor();
    TouchSensor* getTouchSensor();

  private:
    Motor* centerArm;
    Motor* leftWheel;
    Motor* rightWheel;
    ColorSensor* colorSensor;
    TouchSensor* touchSensor;
};


#endif  // POINTERS_H_
