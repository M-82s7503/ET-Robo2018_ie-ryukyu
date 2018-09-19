#include "app.h"
#include "AI_answer.hpp"
#include "Block_answer.hpp"

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
    // 【3】 ライントレース
    Run_RL runner_L;
    running_L.run_L(&leftWheel, &rightWheel, &colorSensor, &touchSensor);

    // 【4】 AIアンサー
    AI_answer ai_ans;
    ai_ans.init();
    ai_ans.readImg_digital(&leftWheel, &rightWheel, &colorSensor, &touchSensor);  // ;走行
    ai_ans.readImg_analog(&leftWheel, &rightWheel, &colorSensor, &touchSensor);  // ;走行
    ai_ans.terminate();
    
    ext_tsk();
}
