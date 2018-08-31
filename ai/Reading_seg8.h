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

#include "Moving_Measure.h"

using namespace ev3api;

class Reading_seg8 : public Moving_Measure {
  public:
    Reading_seg8(float pwm, int* arr_digital);
    void setArr_idx(int arr_idx);
    void f_write();

  protected:
    // 継承したら、必ず全部実装する。
    float decide_pwm_r();   
    float decide_pwm_l();
    bool break_condition();
    //void run_after();
  
  private:
    enum {
        // colorSensor.getColorNumber() の戻り値
        GREY = 0,    // 無し
        BLACK = 1,   // 黒
        BLUE = 2 ,   // 青
        GREEN = 3,   // 緑
        YELLOW = 4,  // 黄
        RED = 5,     // 赤
        WHITE = 6,   // 白
   };

    float base_pwm;
    // 白黒情報を保存する配列
    int* num_img_arr;
    int arr_idx;  // 今回読み取る位置。
    // 配列を描画する用のマップ配列
    int mapArr[7] = {7,2,1,6,3,4,5};


    float now_dist;
    int color_tmp;

    // 動作変更位置。
    static const int cond_len = 2;
    float cond_dists[cond_len] = {150,160};
    int posi_type(float dist);
};
