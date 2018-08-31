#include "Moving_Measure.h"


/**
 *  全ての「動き」の基本となるクラス。 
 *  （抽象クラスなので）継承して使う。
 */

// Moving *mover = new Chilid_Moving();
// mover->run();
// で使う。


Moving_Measure::Moving_Measure()
  : dMeasure()
{}


void Moving_Measure::run() {
  //static int run = 0;
  while(break_condition()){
    int pwm_l = decide_pwm_l();      // <6>
    int pwm_r = decide_pwm_r();      // <6>
    leftWheel.setPWM(pwm_l);
    rightWheel.setPWM(pwm_r);

    // ボタンを押したら、動作を中断
    if(touchSensor.isPressed()){break;}
    clock.wait(1);
  }
}



