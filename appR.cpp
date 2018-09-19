#include "app.h"
#include "Run_RL.hpp"
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
        /*  スタート処理  */
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
    msg_f("breaked!",0);


    // 【1】 ライントレース
    Run_RL running_R;
    running_R.run_R(&leftWheel, &rightWheel, &colorSensor, &touchSensor);

    // 【2】 ブロック並べ
    Block_answer block_ans;
    block_ans.run();

    ext_tsk();
}
