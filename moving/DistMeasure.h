#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"
#include "TouchSensor.h"

using namespace ev3api;

class DistMeasure {
  public:
    DistMeasure();
    enum LR {
      // DistMeasure::LEFT
      // みたいな感じで使う
      // Enums に統合する可能性あり。
      LEFT = -1,
      RIGHT = 1
    };
    void init();
    void resetDig();
    float getNowDist(LR whichWheel);

  private:
    Motor leftWheel;
    Motor rightWheel;
    int32_t startDig_L;
    int32_t startDig_R;
};
