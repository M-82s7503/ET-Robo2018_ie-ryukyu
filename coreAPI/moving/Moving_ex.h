#ifndef Moving_ex_H_
#define Moving_ex_H_

#include "Motor.h"

#include "Moving.h"
#include "Enums.h"
#include "util.h"


using namespace ev3api;

class Moving_ex : public Moving {
  public:
    Moving_ex(Pointers pt_s);
    void run(Enums::Directs direct, int param);
    void run(Enums::Directs LorR, Enums::Colors color);

  protected:
    // 継承したら、必ず実装する。
    void setVector(Enums::Directs ForB, int distance);

    // to_color も使いたい場合は、この辺も実装する。
    void setToColor(Enums::Directs LorR, Enums::Colors color);
    /*
    Enums::Colors till_color;
    bool isToColor_mode = false;
    */
};


#endif  // Moving_ex_H_