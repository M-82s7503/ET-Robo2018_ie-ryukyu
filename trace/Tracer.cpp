#include "Tracer.hpp"



Tracer::Tracer(Pointers pt_s):
    Moving(pt_s), To_Vector_IF(),
    distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{
    target_val = 11;
    // 初期値
    setParam(Enums::PID::Midium);
    setVector(Enums::LEFT, 0);
}

void Tracer::setParam(Enums::PID pid_pattern) {
    switch(pid_pattern) {
        /**
         *   ● 速度
         *   ● KP, KI, KD
         *   ● DELTA_T (?)
         * を１セットとする。
         */
        case Enums::PID::Midium:  // 中間
            speed = (Motor::PWM_MAX) / 5;
            KP = 1.20;
            KI = 0;
            KD = 0.20;
            DELTA_T = 0.004;
            break;
        case Enums::PID::Fast:  // 高速
            speed = (Motor::PWM_MAX) / 3;
            KP = 0.35;
            KI = 0;
            KD = 0.50;
            DELTA_T = 0.004;
            break;
        case Enums::PID::Slow:  // 遅い
            speed = (Motor::PWM_MAX) / 6;
            KP = 0.43;
            KI = 0.01;
            KD = 0.2;
            DELTA_T = 0.004;
            break;
    }
}


float Tracer::calc_pid(int sensor_val) {
    diff[0] = diff[1];
    diff[1] = sensor_val - target_val;
    intergral += (diff[1] + diff[0]) / 2.0*DELTA_T;

    p = KP * diff[1];
    i = KI * intergral;
    d = KD * (diff[1] - diff[0]) / DELTA_T;

    return p+i+d;
}


// オーバーライド
// run(Enums::Directs LorR, int distance) でも呼び出される。
void Tracer::setVector(Enums::Directs LorR, int distance) {
    distMeasure.init();
    // 「向き」を指定
    line_side = LorR;
    dist = distance;

    isToColor_mode = false;
}
// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Tracer::run(Enums::Directs direct, int distance) {
    setVector(direct, distance);
    Moving::run();
}
void Tracer::run(Enums::Directs direct, Enums::Colors color) {
    setToColor(direct, color);
    Moving::run();
}
void Tracer::setToColor(Enums::Directs LorR, Enums::Colors color) {
    till_color = color;
    isToColor_mode = true;  // ToVector でフラグを戻すことを忘れない！
    // param の処理

    // break_condision() でフラグ処理する。
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
    int8_t lowpass = calc_lowpass(sensor_val);
    seigyo = calc_pid(lowpass); // <5>
//    msg_f(sensor_val, 4);

    // 【break条件】距離
    if( distMeasure.getNowDist(Enums::LR_AVG) >= dist ) {
        msg_f("overed dist.", 2);
        // break;
        return true;
    }
    // 【break条件】その他
    // to color
    if (isToColor_mode && colorSensor->getColorNumber() == static_cast<int>(till_color)) {
        return true;
    }
    // 続行
    return false;
}


void Tracer::calibration(int8_t white_val, int8_t black_val) {
  float sensor_average = (white_val + black_val) /2;
  target_val = sensor_average * coefficient + target_val * (1- coefficient);
  msg_f(target_val, 6);
}

void Tracer::setLowpassValue(){
  uint8_t list_size = 5;
  while(lowpass_list.size() <= list_size){
    int8_t sensor_val = colorSensor->getBrightness();

    lowpass_list.push_back(sensor_val);
  }
  int8_t average = 0;
  for(auto i = lowpass_list.begin(); i != lowpass_list.end(); ++i){
    average += *i;
  }
  //msg_f("calibration",1);
  //msg_f(average/list_size, 1);
  
  all_avarage = average/list_size;  
}


int8_t Tracer::calc_lowpass(int8_t brightness){
  /*lowpass_list.pop_front();
  lowpass_list.push_back(brightness);
  int8_t avarage = 0;

  for (auto itr = lowpass_list.begin(); itr != lowpass_list.end(); ++itr){
    avarage += *itr;
  }
  */
  //int8_t avarage = 0;
  float coefficient = 0.4;
  all_avarage  = all_avarage *(coefficient) + brightness * (1 - coefficient);
  
 return all_avarage;
}
