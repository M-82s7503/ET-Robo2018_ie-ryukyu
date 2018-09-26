#include "Run_RL.hpp"


void Run_RL::calibration(TouchSensor* touchSensor) {
    Clock clock;

    //###  アームの角度を初期化 → 調整  ###//
    MoveUtil moveUtil;
    moveUtil.resetArm();
    moveUtil.raiseArm(42, 30);
  
    //###  タッチ スタート  ###//
    msg_f("boot completed !",0);
    //ボタンを押したらスタート
    clock.wait(500);  //入れると安定した。
    msg_f("waiting...",0);
    while(1){
        if (touchSensor->isPressed()) {
            break;
        }
        clock.wait(10);
    }
    //msg_f("breaked!",0);
}

void Run_RL::run_L(
    Motor* l_Wheel,
    Motor* r_Wheel,
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {
    Pointers pt_s(l_Wheel, r_Wheel, c_Sensor, t_Sensor);
    Tracer tracer(pt_s);
    tracer.calibration();
    // tracer のテスト
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2500);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1500);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 1800);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 2000);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2300);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1400);
    tracer.stop();

}


void Run_RL::run_R(
    Motor* l_Wheel,
    Motor* r_Wheel,
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {
    Pointers pt_s(l_Wheel, r_Wheel, c_Sensor, t_Sensor);
    Tracer tracer(pt_s);
    tracer.calibration();
    // tracer のテスト
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2150);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 5550);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2300);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1300);
    tracer.stop();

}
