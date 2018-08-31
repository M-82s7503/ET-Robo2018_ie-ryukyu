#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"
#include "TouchSensor.h"

using namespace ev3api;

class Moving {
  public:
    Moving();
    void run();

  protected:
    // 継承したら、必ず全部実装する。
    virtual float decide_pwm_r() = 0;
    virtual float decide_pwm_l() = 0;
    virtual bool break_condition() = 0;

    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
    TouchSensor touchSensor;
    Clock clock;
};
