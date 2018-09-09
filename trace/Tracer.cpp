#include "Tracer.h"



Tracer::Tracer(Pointers pt_s):
    Moving_ex(pt_s),
    distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{
    target_val = 11;
    // 初期値
    setParam(0);
    setVector(Enums::LEFT, 0);
}

void Tracer::setParam(int pid_pattern) {
    switch(pid_pattern) {
        /**
         *   ● 速度
         *   ● KP, KI, KD
         *   ● DELTA_T (?)
         * を１セットとする。
         */
        case Enums::PID::Slow:  // 遅い
            speed = (Motor::PWM_MAX) / 4;
            KP = 0.66;
            KI = 0.02;
            KD = 0.54;
            DELTA_T = 0.004;
            break;
        case Enums::PID::Midium:  // 中間
            speed = (Motor::PWM_MAX) / 3;
            KP = 0.66;
            KI = 0.02;
            KD = 0.54;
            DELTA_T = 0.004;
            break;
        case Enums::PID::Fast:  // 高速
            speed = (Motor::PWM_MAX) / 1.8;
            KP = 0.66;
            KI = 0.02;
            KD = 0.54;
            DELTA_T = 0.004;
            break;
    }
}

// run(Enums::Directs LorR, int distance) でも呼び出される。
void Tracer::setVector(Enums::Directs LorR, int distance) {
    distMeasure.init();
    // 「向き」を指定
    line_side = LorR;
    dist = distance;
}


float Tracer::calc_pid(int sensor_val) {
    diff[0] = diff[1];
    diff[1] = sensor_val - target_val;
    intergral += (diff[1] + diff[0]) / 2.0*DELTA_T;

    p = KP * diff[1];
    i = KI * intergral;
    d = KD * (diff[1] - diff[0]) / DELTA_T;

    return p+d;
}

/*
// ライントレース は基本、線の左側を走るらしいので、それを基準に考える。
void Tracer::run() {
    while( 1 ){
        // line_side で切り替え
        int left_speed = speed - seigyo;      // <6>
        int right_speed = speed + seigyo;      // <6>
    }
}
*/

// i がうまくいかなかったのは、 seigyo の +,- が逆だったからでは？
// 普通、左側にいるなら、左側のタイヤを加速させるものでは？

// +,- を逆にするなら、 decide_pwm_~ のl,r を入れ替えるのが一番楽かも。
float Tracer::decide_pwm_l() {
    switch (line_side) {
        case Enums::LEFT:
            return speed - seigyo;
        case Enums::RIGHT:
            return speed + seigyo;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("Tracer line_side Error", 2);
            return 20;
    }
}
float Tracer::decide_pwm_r() {
    switch (line_side) {
        case Enums::LEFT:
            return speed + seigyo;
        case Enums::RIGHT:
            return speed - seigyo;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("Tracer line_side Error", 2);
            return 20;
    }
}


bool Tracer::break_condition() {
    int8_t sensor_val = colorSensor->getBrightness();
    seigyo = calc_pid(sensor_val); // <5>

    // 【break条件】距離
    if( distMeasure.getNowDist(Enums::LR_AVG) >= dist ) {
        msg_f("overed dist.", 2);
        // break;
        return true;
    }
    // 【break条件】その他

    // 続行
    return false;
}


/*
void Tracer::init() {
    init_f("Tracer");
}

void Tracer::terminate() {
    msg_f("Stopped.", 3);
    leftWheel.stop();
    rightWheel.stop();
}
*/

