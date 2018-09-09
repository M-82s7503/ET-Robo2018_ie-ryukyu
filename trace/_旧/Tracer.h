#include "Motor.h"
#include "ColorSensor.h"
#include "clock.h"
#include "TouchSensor.h"

#include "DistMeasure.h"

using namespace ev3api;

class Tracer {
  public:
    Tracer();
    void init();
    //パラメーターを選ぶ、長さを指定
    void setParam(int pid_pattern, int dist);
    // 走行
    void run();
    void terminate();

  private:
    float pid_sample(int sensor_val);

    Clock clock;
    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
    TouchSensor touchSensor;
    //int8_t mThreshold = 20;

    float KP, KI, KD, DELTA_T;
    int target_val;
    int8_t speed;

    float p, i, d;
    int dist;
    int diff[2];
    float intergral;
};
