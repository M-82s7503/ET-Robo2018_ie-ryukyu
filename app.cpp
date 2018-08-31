#include "app.h"
#include "AI_answer.h"
#include "Block_answer.h"

using namespace ev3api;


AI_answer ai_ans;
Block_answer block_ans;

void ext_cyc(intptr_t exinf) {
    act_tsk(EXT_TASK);
}

void ext_task(intptr_t exinf) {
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      wup_tsk(MAIN_TASK);  // 左ボタン押下でメインを起こす
    }
    ext_tsk();
}

void main_task(intptr_t unused) {
    // 【1】 ライントレース
    
    // 【2】 ブロック並べ


    // 【3】 ライントレース

    // 【4】 AIアンサー
    ai_ans.init();
    ai_ans.readImg_degital();  // ;走行
    ai_ans.terminate();
    ext_tsk();
}
