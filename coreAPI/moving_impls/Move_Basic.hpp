#include "Moving.h"

using namespace ev3api;

class Move_Basic {
  public:
    Move_Basic(Pointers pt_s);
    //###  基本機能系  ###//
    void resetArm();
    void raiseArm(int degree, int pwm);
    void stop();

    int getArmDeg() {
        return centerArm->getCount();
    }

  private:
    Motor* centerArm;
    Motor* leftWheel;
    Motor* rightWheel;
    ColorSensor* colorSensor;
    TouchSensor* touchSensor;

    Clock clock;

};
