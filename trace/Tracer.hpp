#ifndef TRACER_H_
#define TRACER_H_

#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"

#include "Moving.h"
#include "To_Vector_IF.hpp"
#include "To_Color_IF.hpp"
#include "DistMeasure.h"

#include <list>

using namespace ev3api;

class Tracer : public Moving, public To_Vector_IF, public To_Color_IF {
  public:
    Tracer(Pointers pt_s);
    //void init();
    //パラメーターを選ぶ & 長さを指定
    void setParam(Enums::PID pid_pattern);
    // 走行
    void run(Enums::Directs direct, int distance);
    // LorR：線の右側と左側、どちらを走るかを指定。
    void setVector(Enums::Directs LorR, int distance);
    // to color
    void run(Enums::Directs direct, Enums::Colors color);
    void setToColor(Enums::Directs LorR, Enums::Colors color);
    // キャリブレーション
    void calibration(int8_t white_val, int8_t black_val);
    static constexpr float coefficient = 0.4;
    // ローパスフィルタの初期化
    void setLowpassValue();
    
  protected:
    float decide_pwm_l();
    float decide_pwm_r();
    bool break_condition();

  private:
    Enums::Directs line_side;
    int dist;
    DistMeasure distMeasure;
    bool isToColor_mode = false;
    Enums::Colors till_color;

    float calc_pid(int sensor_val);
    int8_t calc_lowpass(int8_t brightness);
    // 定数変数
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

#endif  // TRACER_H_

