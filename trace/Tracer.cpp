#include "Tracer.hpp"



Tracer::Tracer(Pointers pt_s):
    Moving(pt_s), To_Vector_IF(),
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


// オーバーライド
// run(Enums::Directs LorR, int distance) でも呼び出される。
void Tracer::setVector(Enums::Directs LorR, int distance) {
    distMeasure.init();
    // 「向き」を指定
    line_side = LorR;
    dist = distance;
}
// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Tracer::run(Enums::Directs direct, int distance) {
    setVector(direct, distance);
    Moving::run();
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


// +,- を逆にするなら、 decide_pwm_~ のl,r を入れ替えるのが一番楽かも。
float Tracer::decide_pwm_l() {
    switch (line_side) {
//        case Enums::LEFT:
        case Enums::RIGHT:
            return speed - seigyo;
//        case Enums::RIGHT:
        case Enums::LEFT:
            return speed + seigyo;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("Tracer line_side Error", 2);
            return 20;
    }
}
float Tracer::decide_pwm_r() {
    switch (line_side) {
//        case Enums::LEFT:
        case Enums::RIGHT:
            return speed + seigyo;
//        case Enums::RIGHT:
        case Enums::LEFT:
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
//    msg_f(sensor_val, 4);

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


