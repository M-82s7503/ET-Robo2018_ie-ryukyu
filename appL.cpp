#include "app.h"
#include "util.h"
#include "Run_RL.hpp"
#include "AI_answer.hpp"
#include "Parking.h"

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


Motor centerArm(PORT_A);
Motor leftWheel(PORT_C);
Motor rightWheel(PORT_B);
TouchSensor touchSensor(PORT_1);
ColorSensor colorSensor(PORT_2);

void main_task(intptr_t unused) {
    Pointers ptrs(&centerArm, &leftWheel, &rightWheel, &colorSensor, &touchSensor);
    //###  アームの角度を初期化 → 調整  ###//
    //###  タッチ スタート  ###//
    Run_RL running_L;
    running_L.calibration(&ptrs);

    //###  【3】 ライントレース  ###//
//    msg_f("start running !", 0);
//    running_L.run_L(&ptrs);
//    msg_f("line trace finished!", 0);

    //###  【4】 AIアンサー  ###//
    AI_answer ai_ans;
    ai_ans.init();
    ai_ans.readImg_digital(&ptrs);  // ;走行
//    ai_ans.readImg_analog(&leftWheel, &rightWheel, &colorSensor, &touchSensor);  // ;走行
    // ブロックを動かす
    ai_ans.answer_forBlock();
    ai_ans.terminate();

    // 駐車
//    Parking parking;
//    parking.after_AI();

    ext_tsk();
}
