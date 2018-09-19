#include "Moving.h"


/**
 *  全ての「動き」の基本となるクラス。 
 *  （抽象クラスなので）継承して使う。
 */



Moving::Moving(Pointers pt_s):
  clock()
{
    leftWheel = pt_s.getLeftWheel();
    rightWheel = pt_s.getRightWheel();
    colorSensor = pt_s.getColorSensor();
    touchSensor = pt_s.getTouchSensor();
}


void Moving::run() {
    while(1){
        //clock.wait(3);
        // break_condition() の T/F が入れ替わったので注意。
        if (break_condition()) {
            break;
        }
        
        int pwm_l = decide_pwm_l();      // <6>
        int pwm_r = decide_pwm_r();      // <6>
        leftWheel->setPWM(pwm_l);
        rightWheel->setPWM(pwm_r);
    }
    // break で抜けるだけなので、回転し続けることに注意。
    // 止めたい場合は、 .stop() を呼ぶこと。
}



void Moving::stop() {
    //leftWheel.stop();
    //rightWheel.stop();
    leftWheel->stop();
    rightWheel->stop();
}

