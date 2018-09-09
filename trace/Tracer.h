#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"

#include "DistMeasure.h"
#include "Moving_ex.h"

using namespace ev3api;

class Tracer : public Moving_ex {
  public:
    Tracer(Pointers pt_s);
    //void init();
    //パラメーターを選ぶ & 長さを指定
    void setParam(int pid_pattern);
    // 走行
    //void run();
    //void terminate();
  
  protected:
    float decide_pwm_l();
    float decide_pwm_r();
    bool break_condition();
    
    // LorR：線の右側と左側、どちらを走るかを指定。
    void setVector(Enums::Directs LorR, int distance);
    Enums::Directs line_side;
    int dist;

  private:
    DistMeasure distMeasure;
    float calc_pid(int sensor_val);

    // 定数系
    float KP, KI, KD, DELTA_T;
    int target_val;
    int8_t speed;

    // よく使う変数系
    float p, i, d;
    float intergral;
    int diff[2];

    float seigyo;
};
