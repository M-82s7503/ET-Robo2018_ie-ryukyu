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
#include "MoveTemps.h"

using namespace ev3api;

class AI_answer {
  public:
    AI_answer();
    void init();
    void readImg_digital(
        Motor* l_Wheel,
        Motor* r_Wheel,
        ColorSensor* c_Sensor,
        TouchSensor* t_Sensor
    );
    void readImg_analog(
        Motor* l_Wheel,
        Motor* r_Wheel,
        ColorSensor* c_Sensor,
        TouchSensor* t_Sensor
    );
    void terminate();

    // 解析結果を２進数として保存
    int analyze_result[2][3];

  private:
    Clock clock;
    MoveUtil moveUtil;

    const int8_t pwm = (Motor::PWM_MAX) / 4;

    // デジタルの数字。７本あれば表現可能。
    int num_img_digital[7];
    // アナログの数字。3*5=15 マス。
    float num_img_analog[15];
    // 配列の初期化
    void init_arr_all0(int* arr, int arr_size);
    void init_arr_all0(float* arr, int arr_size);

    /*  コース の計測データ  */
    // 灰色の終点から緑まで
    const int until_greenMat = 400; // 27+13
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
    const int sensor_dist = 30;  // (未) タイヤの中心線から、カラーセンサーまでの距離
    const int tire_dist = 75;
};
