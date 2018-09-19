    // インスタンスを作成。
#include "Run_RL.hpp"

void Run_RL::run_L(
    Motor* l_Wheel,
    Motor* r_Wheel,
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {
    Pointers pt_s(l_Wheel, r_Wheel, c_Sensor, t_Sensor);
    Tracer tracer(pt_s);

    // tracer のテスト
/*    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2500);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1500);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 1800);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 2000);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2300);
*/    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1000);
    //tracer.stop();
}


void Run_RL::run_R(
    Motor* l_Wheel,
    Motor* r_Wheel,
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {
    
}
