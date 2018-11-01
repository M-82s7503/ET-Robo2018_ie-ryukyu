#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"

#include "Moving.h"
#include "To_Vector_IF.hpp"
#include "DistMeasure.h"

#include <list>

using namespace ev3api;

class Tracer : public Moving, public To_Vector_IF {
  public:
    Tracer(Pointers pt_s);
    //void init();
    //パラメーターを選ぶ & 長さを指定
    void setParam(int pid_pattern);
    // 走行
    void run(Enums::Directs direct, int distance);
    // LorR：線の右側と左側、どちらを走るかを指定。
    void setVector(Enums::Directs LorR, int distance);
    //void terminate();
    // キャリブレーション
    void calibration(int8_t white_val, int8_t black_val);

  protected:
    float decide_pwm_l();
    float decide_pwm_r();
    bool break_condition();
    

  private:
    Enums::Directs line_side;
    int dist;
    DistMeasure distMeasure;

    float calc_pid(int sensor_val);
    int8_t calc_lowpass(int8_t brightness);
    // 定数
    float KP, KI, KD, DELTA_T;
    int target_val;
    int8_t speed;

    // よく使う変数
    float p, i, d;
    float intergral;
    int diff[2];

    float seigyo;
    std::list<int> lowpass_list;
    int8_t all_avarage;
};
