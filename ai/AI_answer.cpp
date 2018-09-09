#include "AI_answer.h"


AI_answer::AI_answer():
    clock()
{
    // アナログ数字の読み取り結果を保存する配列を初期化
    init_arr_all0(num_img_analog);
    init_arr_all0(num_img_digital);
}

void AI_answer::init_arr_all0(int* arr) {
    // sizeofで要素数を調べる
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    if (arr_size <= 0) return;
    for(int i=0; i < arr_size; ++i){
      // 0で初期化
      arr[i] = 0;
    }
}


void AI_answer::init() {
    init_f("AI_answer");
}

void AI_answer::terminate() {
    msg_f("Stopped.", 1);
    moveUtil.stop();
}

void AI_answer::readImg_degital(
    Motor* l_Wheel,
    Motor* r_Wheel,
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {

    Pointers pt_s(l_Wheel, r_Wheel, c_Sensor, t_Sensor);

    Straight straight(pt_s);
    Turn_oneSide turn_oneSide(pt_s);

    float read_speed = 20;
    Reading_seg8 reading_digital(pt_s, read_speed, num_img_digital);

    // 数字画像まで移動
    straight.run(Enums::FRONT, until_greenMat);
    moveUtil.to_color(Enums::WHITE);

    /**  8の字走行  **/
    //--  <1> 横・上側  --//
    // 開始位置に移動
    turn_oneSide.run(Enums::LEFT, -90);
    straight.run(Enums::FRONT, tate_4);  // 数字の3分の1の長さ
    turn_oneSide.run(Enums::LEFT, 90);
    // 読み取り実行
    reading_digital.run(0, Enums::FRONT, yoko_2);
    reading_digital.run(1, Enums::FRONT, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。

    //--  <2> 横・下側  --//
    // 開始位置に移動
    moveUtil.to_color(Enums::BLACK);  // 一旦マットに出る。
    turn_oneSide.run(Enums::RIGHT, 90);
    straight.run(Enums::FRONT, tate_4/2);  // ［確認］いらないかも？
    turn_oneSide.run(Enums::RIGHT, Enums::WHITE);  // 白が見えるまで回転。
    // 読み取り
    // 読み取り実行
    reading_digital.run(2, Enums::FRONT, yoko_2);
    reading_digital.run(3, Enums::FRONT, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。


    //--  <3> 縦  --//
    // 開始位置に移動
    moveUtil.to_color(Enums::BLACK);  // 一旦マットに出る。
    turn_oneSide.run(Enums::LEFT, 90);
    // ［確認］この辺で ライントレース入れる？
    straight.run(Enums::FRONT, tate_4*1.5);  // 数字の3分の1の長さ

    turn_oneSide.run(Enums::LEFT, 90);
    // ［確認］この辺で ライントレース入れる？
    straight.run(Enums::FRONT, img_size_yoko/2);

    turn_oneSide.run(Enums::LEFT, 90);
    moveUtil.to_color(Enums::WHITE);

    // 読み取り実行
    reading_digital.run(4, Enums::FRONT, img_size_tate);
    reading_digital.run(5, Enums::FRONT, yoko_2);
    reading_digital.run(6, Enums::FRONT, yoko_2);
    straight.run(Enums::FRONT, img_size_tate);

    straight.stop();


    reading_digital.f_write();

    /*
    //static int run = 0;
    while(1){
      //run = (rightWheel.getCount()+leftWheel.getCount())/2;
      float turn = calc_prop_value(); // <5>
      int pwm_l = pwm - turn;      // <6>
      int pwm_r = pwm + turn;      // <6>
      leftWheel.setPWM(pwm_l);
      rightWheel.setPWM(pwm_r);
      //msg_f(pwm_l,2);
      msg_f(turn,2);
      if(touchSensor.isPressed()){break;}
      clock.wait(4);
    }*/
}
