#include "Tracer.hpp"
#include "MoveUtil.h"
#include "TouchSensor.h"

using namespace ev3api;

class Run_RL {
  public:
    void calibration(TouchSensor* touchSensor);
    // Rコースの走行
    void run_R(
        Motor* l_Wheel,
        Motor* r_Wheel,
        ColorSensor* c_Sensor,
        TouchSensor* t_Sensor
    );
    // Lコースの走行
    void run_L(
        Motor* l_Wheel,
        Motor* r_Wheel,
        ColorSensor* c_Sensor,
        TouchSensor* t_Sensor
    );

};
