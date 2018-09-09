/*
#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"
*/
#include "util.h"
#include "MoveUtil.h"
#include "Reading_seg8.h"
#include "Turn_oneSide.h"

using namespace ev3api;

class AI_answer {
  public:
    AI_answer();
    void init();
    void terminate();
    void readImg_degital(
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

    // デジタルの数字。７本あれば表現可能。
    int num_img_digital[7];
    // アナログの数字。3*4=12 マスまで落とし込むのが目標。
    int num_img_analog[12];

  private:
    Clock clock;

    //static const Parts parts = new Parts();
    MoveUtil moveUtil;

    const int8_t pwm = (Motor::PWM_MAX) / 4;

    void init_arr_all0(int* arr);
    const int img_size_tate = 435;//mm ?
    const int img_size_yoko = 310;

    // 灰色の終点から緑まで
    int until_greenMat = 400; // 27+13(<3)
    int tate_4 = img_size_tate / 4;
    int yoko_2 = img_size_yoko /2;
};
