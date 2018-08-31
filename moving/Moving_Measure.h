#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"
#include "TouchSensor.h"

#include "Moving.h"
#include "DistMeasure.h"


using namespace ev3api;

class Moving_Measure : public Moving {
  public:
    Moving_Measure();
    void run();
    DistMeasure dMeasure;
};
