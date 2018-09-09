#include "Tracer.h"



Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2),touchSensor(PORT_1),clock()
{
    target_val = 11;
}

void Tracer::setParam(int pid_pattern, int distance) {
    dist = distance;

    switch(pid_pattern) {
      case 0:  // slow
        speed = (Motor::PWM_MAX) / 3;
        KP = 0.66;
        KI = 0.02;
        KD = 0.54;
        DELTA_T = 0.004;
        break;
      case 1:  // fast
        speed = (Motor::PWM_MAX) / 2;
        KP = 0.66;
        KI = 0.02;
        KD = 0.54;
        DELTA_T = 0.004;
        break;
    }

}

float Tracer::pid_sample(int sensor_val) {
    diff[0] = diff[1];
    diff[1] = sensor_val - target_val;
    intergral += (diff[1] + diff[0]) / 2.0*DELTA_T;

    p = KP * diff[1];
    i = KI * intergral;
    d = KD * (diff[1] - diff[0]) / DELTA_T;

    return p+d;
}

void Tracer::run() {
    DistMeasure distMeasure(&leftWheel, &rightWheel);
    distMeasure.resetDig();
    int8_t sensor_val;
    int dist_tmp=0;
    //msg_f("run()", 2);
    while( 1 ){
        msg_f("run()", 1);
        sensor_val = colorSensor.getBrightness();
        float seigyo = pid_sample(sensor_val); // <5>
        int left_speed = speed - seigyo;      // <6>
        int right_speed = speed + seigyo;      // <6>
        /*char log[100];
        //sprintf(log,"speed:%d",speed);
        //msg_f(log,1);
        clock.sleep(1000);
        */
        leftWheel.setPWM(left_speed);
        rightWheel.setPWM(right_speed);
        //if(ev3_button_is_pressed(LEFT_BUTTON)){break;}
        //clock.wait(4);

        dist_tmp = distMeasure.getNowDist(Enums::LR_AVG);
        msg_f(dist_tmp, 2);
        //clock.wait(1000);
        if( dist_tmp >= dist ) {
            msg_f("overed dist.", 2);
            break;
        }
        //if(touchSensor.isPressed()){break;}
    }
}



void Tracer::init() {
    init_f("Tracer");
}

void Tracer::terminate() {
    msg_f("Stopped.", 3);
    leftWheel.stop();
    rightWheel.stop();
}


