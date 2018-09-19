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

class Reading_seg8 : public Moving {
  public:
    Reading_seg8(Pointers pt_s, int base_pwm, int* arr_digital);
    void run(int arr_idx, int distance);
    void f_write();  // ファイルに出力

  protected:
    float decide_pwm_r() { return speed; }
    float decide_pwm_l() { return speed; }
    bool break_condition();
  
  private:
    //##  走行に関するもの  ##//
    DistMeasure distMeasure;
    int speed;
    // 白黒情報を保存する配列
    int* num_img_arr;
    int arr_idx;  // 今回読み取る位置。
    // 配列を描画する用のマップ配列
    const int mapArr[7] = {6,1,0,5,2,3,4};

    // tmp変数
    float now_dist;
    int color_tmp;

    // 動作変更位置。
    // 0:~0,  1:0~10,  2:10~130,  3:130~155
    static const int cond_len = 4;
    float cond_dists[cond_len];
    int posi_type(float dist);
};
