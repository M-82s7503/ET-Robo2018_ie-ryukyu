#include "app.h"
#include "Run_RL.hpp"
#include "Block_answer.hpp"
#include "Parking.h"

using namespace ev3api;


void ext_cyc(intptr_t exinf) {
    act_tsk(EXT_TASK);
}

void ext_task(intptr_t exinf) {
    if (ev3_button_is_pressed(UP_BUTTON)) {
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
    //###  キャリブレーション  ###//
    // Mac を ロボと Bluetooth で接続後、
    //      $ screen /dev/tty.MindstormsEV3-SerialPor 115200
    // を実行する。

    bool isRemoteStart = true;
    int block_code = 15432;
    Run_RL running_R;
    if (isRemoteStart) {
        block_code = running_R.calibration_R(&ptrs);
        msg_f(block_code, 0);
    } else {
        // タッチスタート の初期設定
        running_R.calibration_touch(&ptrs, true);
    }

    //###  【1】 ライントレース  ###//
    running_R.run_R(&ptrs, isRemoteStart);

    //###  【2】 ブロック並べ  ###//
    Block_answer block_ans;
    block_ans.run();
    //###   駐車   ###//
    Parking parking;
    parking.after_Block();

    ext_tsk();
}
