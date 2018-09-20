#include "app.h"
#include "util.h"
#include "Run_RL.hpp"
#include "AI_answer.hpp"

using namespace ev3api;


void ext_cyc(intptr_t exinf) {
    act_tsk(EXT_TASK);
}

void ext_task(intptr_t exinf) {
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      wup_tsk(MAIN_TASK);  // 左ボタン押下でメインを起こす
    }
    ext_tsk();
}



Motor leftWheel(PORT_C);
Motor rightWheel(PORT_B);
TouchSensor touchSensor(PORT_1);
ColorSensor colorSensor(PORT_2);
Clock clock;

void main_task(intptr_t unused) {
    //###  アームの角度を初期化 → 調整  ###//
    /*MoveUtil moveUtil;
    moveUtil.resetArm();
    moveUtil.raiseArm(10, 30);
    */
  
    //###  タッチ スタート  ###//
    msg_f("to start completed !",0);
    //ボタンを押したらスタート
    clock.wait(500);  //入れると安定した。
    msg_f("waiting...",0);
    while(1){
        if (touchSensor.isPressed()) {
            break;
        }
        clock.wait(10);
    }
    //msg_f("breaked!",0);


    // 【3】 ライントレース
    msg_f("start!", 0);
    Run_RL running_L;
    running_L.run_L(&leftWheel, &rightWheel, &colorSensor, &touchSensor);
    msg_f("line trace finished!", 0);

    /*
    // 【4】 AIアンサー
    AI_answer ai_ans;
    ai_ans.init();
    ai_ans.readImg_digital(&leftWheel, &rightWheel, &colorSensor, &touchSensor);  // ;走行
    ai_ans.readImg_analog(&leftWheel, &rightWheel, &colorSensor, &touchSensor);  // ;走行
    ai_ans.terminate();
    */
    ext_tsk();
}
