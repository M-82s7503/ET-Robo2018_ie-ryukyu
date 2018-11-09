/*
#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"
*/
#include "util.h"
#include "MoveUtil.h"

#include "Reading_seg8.h"
#include "Reading_return3.h"

//#include "Turn_oneSide.h"
//#include "Turn.h"
//#include "Straight.h"
#include "MoveTemps.hpp"
#include "Tracer.hpp"

#include "PatternMatcher.hpp"
#include "Move_block.h"

using namespace ev3api;

class AI_answer {
  public:
    AI_answer();
    void init();
    void readImg_digital(Pointers* ptrs_p);
    void readImg_analog(Pointers* ptrs_p);

    void answer_forBlock();
    void terminate();

    // 解析結果を２進数として保存
    // 0:digital,  1:analog
    int8_t analyze_result[2][3];

  private:
    Clock clock;
    MoveUtil moveUtil;
    Pointers* pts;

    const int8_t pwm = (Motor::PWM_MAX) / 4;

    // デジタルの数字。７本あれば表現可能。
    int num_img_digital[7];
    // アナログの数字。3*5=15 マス。
    float num_img_analog[15];
    // 配列の初期化
    void init_arr_all0(int* arr, int arr_size);
    void init_arr_all0(float* arr, int arr_size);

    // その他
    void analog_read_pattern(Reading_return3 reading_analog, int8_t return_th, Straight straight, MoveTemps moveTemps, Move_Basic mv_basic);
    void conv_Binary_num(int8_t ans_num, int8_t arr[3]);

    /*  コース の計測データ  */
    // 灰色の終点から緑まで
    const int until_greenMat = 200; // 27+13
    Enums::Colors greenMat_c = Enums::Colors::BLACK;
    /*  数字カード の計測データ  */
    const int img_size_tate = 435;//mm
    const int img_size_yoko = 310;//mm
    const int img_yohaku_tate = 60;
    const int img_yohaku_yoko = 40;
    // よく使う値
    int tate_4 = img_size_tate / 4;
    int yoko_2 = img_size_yoko / 2;
    float analog_size_tate = img_size_tate - img_yohaku_tate*2;
    float analog_size_yoko = img_size_yoko - img_yohaku_yoko*2;

    /*  機体 の計測データ  */
    const int sensor_dist = 35;  // (未) タイヤの中心線から、カラーセンサーまでの距離
    const int tire_dist = 75;
};
