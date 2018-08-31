#include "AI_answer.h"


AI_answer::AI_answer()
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

void AI_answer::readImg_degital() {
  float read_speed = 20;
  Reading_seg8 reading_digital(read_speed, num_img_digital);

  // 数字画像まで移動
  moveUtil.straight(leng_to_greenMat);
  moveUtil.to_color(WHITE);

  /** 8の字走行  */
  //--  横・上側  --//
  // 開始位置に移動
  moveUtil.turn(-90);
  moveUtil.straight(img_size_tate_3);  // 数字の3分の1の長さ
  moveUtil.turn(90);

  // 読み取り
  /*
  int color_tmp;
  do {
    color_tmp = WHITE;

    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);

    color_tmp = getColorNumber();
  } while (color_tmp != GREEN)
  */

  reading_digital.run();
  //moveUtil.straight(img_size_yoko);

  //--  横・下側  --//
  // 開始位置に移動
  moveUtil.turn(-90);
  moveUtil.to_color(WHITE);
  moveUtil.straight(img_size_tate_3);  // 数字の3分の1の長さ
  moveUtil.turn(-90);
  // 読み取り
  moveUtil.straight(img_size_yoko);


  //--  縦  --//
  // 開始位置に移動
  moveUtil.turn(90);
  moveUtil.straight(img_size_tate_3);  // 数字の3分の1の長さ
  moveUtil.turn(90);
  moveUtil.straight(img_size_yoko/1.8);
  moveUtil.turn(90);
  moveUtil.to_color(WHITE);
  // 読み取り
  moveUtil.straight(img_size_tate);

  moveUtil.stop();


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
