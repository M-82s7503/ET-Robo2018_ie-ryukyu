#include "AI_answer.hpp"


AI_answer::AI_answer():
    clock()
{
    // アナログ数字の読み取り結果を保存する配列を初期化
    init_arr_all0(num_img_digital, 7);
    init_arr_all0(num_img_analog, 12);
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
    msg_f("AI_answer compleated.", 1);
}



// 【動き】 デジタル数字カード
void AI_answer::readImg_digital(Pointers* ptrs_p) {
    pts = ptrs_p;
    Pointers ptrs(ptrs_p);

    Move_Basic mv_basic(ptrs);
    Straight straight(ptrs);
    straight.setBase_PWM(12);
    Turn_oneSide turn_oneSide(ptrs);
    Turn turn(ptrs);
    MoveTemps moveTemps(ptrs);
    Tracer tracer(ptrs);

    moveUtil.setSpeed(12);
    float read_speed = 8;
    Reading_seg8 reading_digital(ptrs, read_speed, num_img_digital);

//    int whites[2] = {Enums::WHITE, Enums::GREY};

    // 数字画像まで移動
    mv_basic.stop();
    clock.wait(600);

//    turn.run(Enums::Directs::RIGHT, 3);
//    turn.to_color_turn(Enums::Colors::BLACK, Enums::Directs::RIGHT, 30);
/*
    // ライントレースで収束させたい...。
    straight.run(Enums::BACK, 120);
    mv_basic.stop();
    clock.wait(700);

    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 120);
    mv_basic.stop();
    clock.wait(700);

    straight.run(Enums::BACK, 80);
    mv_basic.stop();
    clock.wait(700);

    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 80);
    mv_basic.stop();
    clock.wait(700);
*/
    mv_basic.raiseArm(30, 30);
    mv_basic.stop();
    clock.wait(500);

    straight.run(Enums::FRONT, until_greenMat);
    moveUtil.to_color( static_cast<int>(Enums::WHITE) );
//    straight.run(Enums::Colors::BLACK, Enums::Directs::FRONT, 500);

    //###  8の字走行  ###//
    //--  <1> 横・上側  --//
    // 開始位置に移動
    moveUtil.turn(-90);
    turn_oneSide.run(Enums::LEFT, 90);
    straight.run(Enums::Directs::BACK, 80);
    straight.run(Enums::Colors::BLACK, Enums::Directs::BACK, 20);
    mv_basic.stop();
    moveUtil.to_color( static_cast<int>(Enums::Colors::WHITE) );
    mv_basic.stop();

    // 読み取り実行
    reading_digital.run(0, yoko_2);
    reading_digital.run(1, yoko_2);

    //--  <2> 横・下側  --//
    // 開始位置に移動
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 一旦マットに出る。
    mv_basic.stop();
    straight.run(Enums::FRONT, sensor_dist);
    mv_basic.stop();
    turn_oneSide.run(Enums::RIGHT, 180);  // 白が見えるまで回転。
    mv_basic.stop();
    // (未テスト) ズレ調整
    straight.run(Enums::Directs::BACK, 30);
    straight.run(Enums::Colors::BLACK, Enums::Directs::BACK, 20);
    mv_basic.stop();
    //moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::LEFT);
    mv_basic.stop();

    // 読み取り実行
    reading_digital.run(2, yoko_2);
    reading_digital.run(3, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。


    //--  <3> 縦  --//
    // 開始位置に移動
    // 1回転
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 一旦マットに出る。
    mv_basic.stop();
//    moveUtil.turn(90+8);     // [確認] ズレように値を調整した。
    turn.run(Enums::Directs::RIGHT, 85);
    // 2回転
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    turn_oneSide.run(Enums::LEFT, 180);
    mv_basic.stop();
    straight.run(Enums::BACK, sensor_dist*1.5);
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 多分、ここまでは行かない。
    //moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::RIGHT);

    // 読み取り実行
    reading_digital.run(4, img_size_tate*2/5);
    reading_digital.run(5, img_size_tate*1/5);
    reading_digital.run(6, img_size_tate*2/5);
    //straight.run(Enums::FRONT, img_size_tate);

/*
    //--  <+α> digital で終わる場合  --//
    // カード上側
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  //一旦マットに出る
    straight.run(Enums::Directs::FRONT, sensor_dist-12);
    // カード上側 → カード左側
    turn.to_color_turn(Enums::Colors::WHITE, Enums::Directs::LEFT, 120);
    turn.run(Enums::LEFT, 5);  // 確実に、白の枠内に入る。
    mv_basic.stop();
    // カード左側（アナログもやる場合は、こっちもやる）
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  //一旦マットに出る
    straight.run(Enums::Directs::FRONT, sensor_dist-12);
    // カード左側 → カード下側
    turn.to_color_turn(Enums::Colors::WHITE, Enums::Directs::LEFT, 120);
    turn.run(Enums::LEFT, 5);  // 確実に、白の枠内に入る。
    mv_basic.stop();
    moveUtil.to_color(Enums::Colors::BLACK);

    // 右に黒を探しに行く。そこでズレ修正。
    turn.run(Enums::Directs::RIGHT, 80);
    moveUtil.to_color(Enums::Colors::BLACK);
    straight.run(Enums::Directs::FRONT, sensor_dist/2);
    moveTemps.ride_onLine_vertical(Enums::Colors::WHITE, Enums::LEFT);
    straight.run(Enums::Directs::BACK, sensor_dist/3);
    turn.run(Enums::Directs::LEFT, 90);
    // マットに出て終了。
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    straight.run(Enums::Directs::FRONT, sensor_dist/2);
    mv_basic.stop();
*/
    //--  log 出力  --//
    reading_digital.f_write();

    //--  パターンマッチで、カードの数字を予想  --//
    PatternMatcher ptMatch;
    ptMatch.solve_D(num_img_digital);
    msg_f("analog answer", 2);
    msg_f( ptMatch.getAns_D(), 3 );

    // 回答を 2進数に変換した上で、analyze_result に書き込む。
    conv_Binary_num(ptMatch.getAns_D(), analyze_result[0]);
/*
*/
    //--  <4> アナログ読み取りへ  --//

}






// 【動き】 アナログ数字カード
void AI_answer::readImg_analog(Pointers* ptrs_p) {
    pts = ptrs_p;
    Pointers ptrs(ptrs_p);
    
    Move_Basic mv_basic(ptrs);
    Straight straight(ptrs, 12);
    Turn_oneSide turn_oneSide(ptrs, 8);
    Turn turn(ptrs, 8);
    MoveTemps moveTemps(ptrs, 8);

    moveUtil.setSpeed(12);
    float read_speed = 12;
    Reading_return3 reading_analog(ptrs, read_speed, num_img_analog, analog_size_tate);
    
    mv_basic.raiseArm(30, 30);
    mv_basic.stop();
    clock.wait(500);

    // 数字画像まで移動
    // 一旦マットに出る。
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    straight.run(Enums::Directs::FRONT, sensor_dist);
    //  ↘︎
    turn_oneSide.run(Enums::LEFT, -90);
    mv_basic.stop();
    straight.run(Enums::Directs::FRONT, img_size_yoko*2/3);
    mv_basic.stop();

    //  ← (アナログ画像のとこまで)
    straight.run(Enums::Colors::BLACK, Enums::FRONT, 30);  // 〜マット
    straight.run(Enums::FRONT, sensor_dist*1.5);
    straight.run(Enums::Colors::WHITE, Enums::FRONT, 30);  // 〜アナログカード

    //###  3return 走行  ###//
    // 初期位置に移動
    straight.run(Enums::FRONT, sensor_dist/2);
    mv_basic.stop();
    moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::LEFT);
    straight.run( Enums::FRONT,  sensor_dist *moveTemps.getRCos() +15 );
    mv_basic.stop();

    turn.run(Enums::Directs::RIGHT, 90);
    mv_basic.stop();
    if (ptrs.getColorSensor()->getColorNumber() == static_cast<int>(Enums::Colors::BLACK)) {
        turn.run(Enums::Directs::LEFT, Enums::Colors::WHITE);
        turn.run(Enums::Directs::LEFT, 8);
        mv_basic.stop();
    }
    straight.run(Enums::Colors::BLACK, Enums::Directs::FRONT, 30);  // 余白 上側
    straight.run(Enums::FRONT, sensor_dist);

    //--  <1> return 目  --//
    // 開始位置に移動
    moveUtil.turn(-90);
    turn_oneSide.run(Enums::RIGHT, 90);
    mv_basic.stop();
    // 読み取り実行：1
    analog_read_pattern(reading_analog, 1, straight, moveTemps, mv_basic);

    //--  <2>  return 目  --//
    // 開始位置に移動
    turn.run(Enums::RIGHT, 90);
    turn_oneSide.run(Enums::LEFT, 90);
    mv_basic.stop();
    // 読み取り実行：2
    reading_analog.setSpeed(8);
    analog_read_pattern(reading_analog, 2, straight, moveTemps, mv_basic);


    //--  <3> return 目  --//
    // 開始位置に移動
    turn.run(Enums::LEFT, 90);
    turn_oneSide.run(Enums::RIGHT, 90);  // 白が見えるまで回転。
/*
*/
    // 読み取り実行：3
    reading_analog.setSpeed(12);
    analog_read_pattern(reading_analog, 3, straight, moveTemps, mv_basic);

    // log 書き出し。
    reading_analog.f_write();

    //--  パターンマッチで、カードの数字を予想  --//
    PatternMatcher ptMatch;
    ptMatch.solve_A(num_img_analog);
    msg_f("analog answer", 4);
    msg_f(ptMatch.getAns_A(), 5);
    // 2進数に変換
    conv_Binary_num(ptMatch.getAns_A(), analyze_result[1]);
}

// 読み取り実行（黒マットから黒マットまで）
void AI_answer::analog_read_pattern(Reading_return3 reading_analog, int8_t return_th, Straight straight, MoveTemps moveTemps, Move_Basic mv_basic) {
    // 黒マットまでバックする。
    straight.run(Enums::BACK, tire_dist+img_yohaku_tate/2);
    straight.run(Enums::Colors::BLACK, Enums::BACK, img_yohaku_tate/2+8);
    mv_basic.stop();
    // 位置合わせ？
    straight.run(Enums::FRONT, img_yohaku_tate);
    mv_basic.stop();
    clock.wait(800);  // 段差を越えることになるので。
    //moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::LEFT);
    // 読み取り
    reading_analog.run(return_th);
    // 黒マットまで進む。
    straight.run(Enums::FRONT, img_yohaku_tate/1.5);
    straight.run(Enums::Colors::BLACK, Enums::FRONT, img_yohaku_tate);
    mv_basic.stop();
}

void AI_answer::conv_Binary_num(int8_t ans_num, int8_t arr[3]) {
    // 回答を 2進数に変換した上で、analyze_result に書き込む。
    int8_t divd_tmp = ans_num;
    for (int8_t idx=2; idx>=0; idx--) {
        // 2^0 の位は、一番奥（最後）なので、
        // 最初の余りは、配列の一番最後に入る。
        arr[idx] = divd_tmp % 2;
        divd_tmp /= 2;
    }
}


void AI_answer::answer_forBlock() {
    Move_block mv_block(analyze_result);
//    mv_block.through();
    mv_block.by_turn(pts);
}



