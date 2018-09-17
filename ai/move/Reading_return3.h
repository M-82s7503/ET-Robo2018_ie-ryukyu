/*
#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#include "Moving.h"
#include "DistMeasure.h"

using namespace ev3api;

class Reading_return3 : public Moving {
  public:
    Reading_return3(Pointers pt_s, int base_pwm, float* arr_analog, int distance);
    void run(int return_th);
    void f_write();  // ファイルに出力

  protected:
    float decide_pwm_r() { return speed; }
    float decide_pwm_l() { return speed; }
    bool break_condition();
  
  private:
    //##  走行 に関するもの  ##//
    DistMeasure distMeasure;
    int speed;
  
    //##  読み取り に関するもの  ##//
    float* num_img_arr;  // 白黒情報を保存する配列
    const int divide = 5;  // 分割数
    int break_dist;  // 終了距離
    int start_idx;  // 読み込み始める最初のidx
    const int accuracy = 4;  // データの粒度

    // tmp変数
    float now_dist;
    int color_tmp;
    int c_idx;
    int while_c;

    char convBlacknessChar(float blackness);
};
