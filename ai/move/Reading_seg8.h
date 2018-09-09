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

#include "Straight.h"

using namespace ev3api;

class Reading_seg8 : public Straight {
  public:
    Reading_seg8(Pointers pt_s, int base_pwm, int* arr_digital);
    void run(int arr_idx, Enums::Directs ForB, int distance);
    void f_write();

  protected:
    bool break_condition();
    //void run_after();
  
  private:

    float base_pwm;
    // 白黒情報を保存する配列
    int* num_img_arr;
    int arr_idx;  // 今回読み取る位置。
    // 配列を描画する用のマップ配列
    int mapArr[7] = {7,2,1,6,3,4,5};


    float now_dist;
    int color_tmp;

    // 動作変更位置。
    // 0:~0,  1:0~10,  2:10~130,  3:130~155
    static const int cond_len = 4;
    float cond_dists[cond_len];
    int posi_type(float dist);
};
