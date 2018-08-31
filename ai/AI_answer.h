/*
#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"
*/
#include "util.h"
#include "MoveUtil.h"
#include "Reading_seg8.h"

using namespace ev3api;

class AI_answer {
  public:
    AI_answer();
    void init();
    void terminate();
    void readImg_degital();
    void readImg_analog();

    // デジタルの数字。７本あれば表現可能。
    int num_img_digital[7];
    // アナログの数字。3*4=12 マスまで落とし込むのが目標。
    int num_img_analog[12];

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

    //static const Parts parts = new Parts();
    MoveUtil moveUtil;

    const int8_t mThreshold = 20;
    const int8_t pwm = (Motor::PWM_MAX) / 4;

    void init_arr_all0(int* arr);
    const int img_size_tate = 435;//mm ?
    const int img_size_yoko = 310;

    // 灰色の終点から緑まで
    int leng_to_greenMat = 400; // 27+13(<3)
    int img_size_tate_3 = img_size_tate / 3;

};
