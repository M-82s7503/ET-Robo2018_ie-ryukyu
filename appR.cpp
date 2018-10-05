#include "app.h"
#include "Run_RL.hpp"
#include "Block_answer.hpp"
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
Clock clock;

void main_task(intptr_t unused) {
    Pointers ptrs(&centerArm, &leftWheel, &rightWheel, &colorSensor, &touchSensor);
    //###  アームの角度を初期化 → 調整  ###//
    //###  タッチ スタート  ###//
    Run_RL running_L;
    running_L.calibration(&ptrs);

    //###  【1】 ライントレース  ###//
    Run_RL running_R;
    running_R.run_R(&ptrs);

    //###  【2】 ブロック並べ  ###//
    Block_answer block_ans;
    block_ans.run();
    // 駐車
    Parking parking;
    parking.after_Block();

    ext_tsk();
}
