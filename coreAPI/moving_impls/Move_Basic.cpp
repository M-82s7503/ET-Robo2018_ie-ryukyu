#include "Move_Basic.hpp"



Move_Basic::Move_Basic(Pointers pt_s):
    clock()
{
    centerArm = pt_s.getCenterArm();
    leftWheel = pt_s.getLeftWheel();
    rightWheel = pt_s.getRightWheel();
    colorSensor = pt_s.getColorSensor();
    touchSensor = pt_s.getTouchSensor();
}

//###  基本機能系  ###//
void Move_Basic::resetArm() {
  uint32_t b_time = clock.now();//msec
  // 限界までアームを下げる。
  while( (clock.now()-b_time) < 600 ) {
    centerArm->setPWM(-20);
  }
  centerArm->reset();
}

// degree：絶対角度を指定する。0〜90度
void Move_Basic::raiseArm(int degree, int pwm) {
    if (degree < 0) {
        degree = 0;
    } else if (90 < degree) {
        degree = 90;
    }
    if (pwm < 0) { pwm = 0; }

    // 上げる
    if (centerArm->getCount() < degree) {
        centerArm->setPWM(pwm);
        while (centerArm->getCount() < degree) {}
    }
    // 下げる
    if (degree < centerArm->getCount()) {
        centerArm->setPWM(-pwm);
        while (degree < centerArm->getCount()) {}
    }

    centerArm->stop();
    return;
}


void Move_Basic::stop() {
    //leftWheel.stop();
    //rightWheel.stop();
    leftWheel->stop();
    rightWheel->stop();
}

