#include "Tracer.hpp"
//#include "MoveUtil.h"
#include "Move_Basic.hpp"
#include "TouchSensor.h"

using namespace ev3api;

class Run_RL {
  public:
    void calibration(Pointers* ptrs_p);
    // Rコースの走行
    void run_R(Pointers* ptrs_p);
    // Lコースの走行
    void run_L(Pointers* ptrs_p);

};
