#include "Run_RL.hpp"


void Run_RL::calibration(Pointers* ptrs_p) {
    Clock clock;

    //###  アームの角度を初期化 → 調整  ###//
    Pointers ptrs(ptrs_p);
    Move_Basic mv_basic(ptrs);
    mv_basic.resetArm();
    mv_basic.raiseArm(42, 30);
  
    //###  タッチ スタート  ###//
    msg_f("boot completed !",0);
    //ボタンを押したらスタート
    TouchSensor* touchSensor = ptrs.getTouchSensor();
    clock.wait(500);  //入れると安定した。
    msg_f("waiting...",0);
    while(1){
        if (touchSensor->isPressed()) {
            break;
        }
        clock.wait(10);
    }
    clock.wait(500);
    //msg_f("breaked!",0);
}

void Run_RL::run_L(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Tracer tracer(ptrs);
    Move_Basic mv_basic(ptrs);
    // キャリブレーション
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
    mv_basic.stop();
}


void Run_RL::run_R(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Tracer tracer(ptrs);
    Move_Basic mv_basic(ptrs);
    // キャリブレーション
    tracer.calibration();
    // tracer のテスト
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2150);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 5550);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2300);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1550);
    mv_basic.stop();

}
