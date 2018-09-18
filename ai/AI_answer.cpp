#include "AI_answer.hpp"


AI_answer::AI_answer():
    clock()
{
    // アナログ数字の読み取り結果を保存する配列を初期化
    init_arr_all0(num_img_digital, 7);
    init_arr_all0(num_img_analog, 15);
}

void AI_answer::init_arr_all0(int* arr, int arr_size) {
    // sizeofで要素数を調べる
    if (arr_size <= 0) return;
    for(int i=0; i < arr_size; ++i){
      // 0で初期化
      arr[i] = 0;
    }
}
void AI_answer::init_arr_all0(float* arr, int arr_size) {
    // sizeofで要素数を調べる
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



// 【動き】 デジタル数字カード
void AI_answer::readImg_digital(
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
    reading_digital.run(0, yoko_2 - sensor_dist);
    reading_digital.run(1, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。

    //--  <2> 横・下側  --//
    // 開始位置に移動
    moveUtil.to_color(Enums::BLACK);  // 一旦マットに出る。
    turn_oneSide.run(Enums::RIGHT, 90);
    straight.run(Enums::FRONT, tate_4/2);  // ［確認］いらないかも？
    turn_oneSide.run(Enums::RIGHT, Enums::WHITE);  // 白が見えるまで回転。
    // 読み取り
    // 読み取り実行
    reading_digital.run(2, yoko_2 - sensor_dist);
    reading_digital.run(3, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。


    //--  <3> 縦  --//
    // 開始位置に移動
    // 1回転
    moveUtil.to_color(Enums::BLACK);  // 一旦マットに出る。
    turn_oneSide.run(Enums::LEFT, 90);
    // 2回転
    straight.run(Enums::FRONT, tate_4*1.5);
    turn_oneSide.run(Enums::LEFT, 90);
    // 3回転
    straight.run(Enums::FRONT, img_size_yoko/2);
    turn_oneSide.run(Enums::LEFT, 90);
    //moveUtil.to_color(Enums::WHITE);  // 多分、ここまでは行かない。

    // 読み取り実行
    reading_digital.run(4, img_size_tate/3 - sensor_dist);
    reading_digital.run(5, img_size_tate/3);
    reading_digital.run(6, img_size_tate/3);
    //straight.run(Enums::FRONT, img_size_tate);

    moveUtil.to_color(Enums::BLACK);
    straight.stop();

    // log 出力
    reading_digital.f_write();

}




// 【動き】 アナログ数字カード
void AI_answer::readImg_analog(
    Motor* l_Wheel,
    Motor* r_Wheel,
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {
    Pointers pt_s(l_Wheel, r_Wheel, c_Sensor, t_Sensor);

    Straight straight(pt_s);
    Turn_oneSide turn_oneSide(pt_s);

    float read_speed = 20;
    Reading_return3 reading_analog(pt_s, read_speed, num_img_analog, analog_size_tate);
    

    // 数字画像まで移動
    // 一旦マットに出る。
    moveUtil.to_color(Enums::BLACK);
    //  ↘︎
    turn_oneSide.run(Enums::LEFT, -90);
    //  ← (アナログ画像のとこまで)
    moveUtil.to_color(Enums::BLACK);  // デジタル画像 -> マット
    moveUtil.to_color(Enums::WHITE);  // マット -> アナログ画像


    /**  3return 走行  **/
    //--  1 return  --//
    // 開始位置に移動
    straight.run(Enums::FRONT, sensor_dist);
    moveUtil.turn(90);
    moveUtil.to_color(Enums::BLACK);
    straight.run(Enums::FRONT, sensor_dist);
    moveUtil.turn(-90);
    moveUtil.to_color_turn(Enums::WHITE);  // ズレを修正。回る向きは指定したい。
    straight.run(Enums::FRONT, img_yohaku_yoko);  // 余白 上側
    moveUtil.turn(-90);
    // 読み取り実行
    straight.run(Enums::FRONT, img_yohaku_tate - sensor_dist);  // 余白 上側
    reading_analog.run(1);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。

// 未
    //--  <2> 横・下側  --//
    // 開始位置に移動
    moveUtil.to_color(Enums::BLACK);  // 一旦マットに出る。
    turn_oneSide.run(Enums::RIGHT, 90);
    straight.run(Enums::FRONT, tate_4/2);  // ［確認］いらないかも？
    turn_oneSide.run(Enums::RIGHT, Enums::WHITE);  // 白が見えるまで回転。
    // 読み取り
    // 読み取り実行
    reading_analog.run(2);
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
    reading_analog.run(3);
    straight.run(Enums::FRONT, img_size_tate);

    straight.stop();


    reading_analog.f_write();

}
