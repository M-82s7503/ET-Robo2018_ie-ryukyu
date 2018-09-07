#ifndef Moving_ex_H_
#define Moving_ex_H_

#include "Motor.h"

#include "Moving.h"
#include "Enums.h"
#include "util.h"


using namespace ev3api;

class Moving_ex : public Moving {
  public:
    //Moving_ex();
    //Moving_ex(Motor* l_Wheel, Motor* r_Wheel);
    Moving_ex(Pointers pt_s);
    void run(Enums::Directs direct, int param);

  protected:
    // 継承したら、必ず全部実装する。
    virtual void setVector(Enums::Directs ForB, int distance) = 0; 
};


#endif  // Moving_ex_H_