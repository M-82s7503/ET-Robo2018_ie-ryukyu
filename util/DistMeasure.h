#include <cstdlib>

#include "Motor.h"

#include "util.h"
#include "Enums.h"

using namespace ev3api;

class DistMeasure {
  public:
    DistMeasure(Motor* l_Wheel, Motor* r_Wheel);
    void init();
    void resetDig();
    float getNowDist(Enums::Directs whichWheel);

  private:
    Motor* leftWheel;
    Motor* rightWheel;
    int32_t startDig_L;
    int32_t startDig_R;
};
