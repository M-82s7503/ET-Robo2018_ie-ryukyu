#include "Moving.h"


/**
 *  全ての「動き」の基本となるクラス。 
 *  （抽象クラスなので）継承して使う。
 */

// Moving *mover = new Chilid_Moving();
// mover->run();
// で使う。


Moving::Moving():
  // ev3_motor_set_power(mPort, mPWM); で呼び出してるだけだから、多分、複数作っても問題ない？
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2),touchSensor(PORT_1),clock()
{}



void Moving::run() {
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
