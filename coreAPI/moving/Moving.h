#ifndef MOVINGp_H_
#define MOVINGp_H_

#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"

#include "Enums.h"
#include "util.h"
#include "Pointers.h"

using namespace ev3api;

class Moving {
  public:
    Moving(Pointers pt_s);
    void run();

  protected:
    // 継承したら、必ず全部実装する。
    virtual float decide_pwm_r() = 0;
    virtual float decide_pwm_l() = 0;
    virtual bool break_condition() = 0;

    Motor* centerArm;
    Motor* leftWheel;
    Motor* rightWheel;
    ColorSensor* colorSensor;
    TouchSensor* touchSensor;

    Clock clock;
};


#endif  // MOVINGp_H_
