#include "Reading_seg8.h"

/* 
* 数字の読み取り
*/


//--  Moving  --//
Reading_seg8::Reading_seg8(float pwm, int* arr_digital)
    : //Moving(parts) 
    base_pwm(pwm), num_img_arr(arr_digital)       // 引数の値でメンバ変数を初期化
{
    color_tmp = WHITE;
    arr_idx = 0;
}

float Reading_seg8::decide_pwm_r() {
    return base_pwm;
}
float Reading_seg8::decide_pwm_l() {
    return base_pwm;
}


//--  original  --//
bool Reading_seg8::break_condition() {
    // 一定距離進んで、黒があれば 1、無ければ 0 を、num_img_digital に入れる。
    // 現在の距離を取得。
    now_dist = dMeasure.getNowDist(DistMeasure::LEFT);
    // 現在地の色を取得。
    color_tmp = colorSensor.getColorNumber();
    // 現在地の位置によって、処理を変える。
    switch ( posi_type(now_dist) ) {
        case 0:
            // 何もしない。
            // 緑が黒で認識される問題の解決のため。という意味もある。
            return true;
        case 1:
            if (color_tmp == BLACK) {
                num_img_arr[arr_idx] = 1;
            }
            return true;
        case 2:
            // 何もしない。
            // 半分を超えたところを想定。
            return color_tmp != BLACK;
        default:
            return false;
    }
}



int Reading_seg8::posi_type(float dist) {
    for (int i=0; i<cond_len; i++) {
        if (dist < cond_dists[i]) {
            return i;
        }
    }
    return 2;
}


// 何番目かを指定。
void Reading_seg8::setArr_idx(int idx) {
    arr_idx = idx;
}

void Reading_seg8::f_write() {
    FILE *file = fopen("read_7seg_8nozi.txt", "a");   

    char arr[5]; // 3x5 = 90
    /*

     -     - 
    | |     |
     -      
    | |     |
     -    

    */

    // 配列で書き出し
    fprintf(file, "[");
    for(int i=0; i<7; i++){
        sprintf(arr, "%d, ", num_img_arr[i]);
        //clock.sleep(1000);  //画面表示を見やすくするためらしい。
        fprintf(file, "%s", arr);
    }
    fprintf(file, "]\n\n\n");

    // わかりやすく書き出し
    for(int i=0; i<7; i++){
        if (num_img_arr[mapArr[i]] == 1) {
            switch (i%3) {
                case 0:
                    // 3の倍数番目の場合：「 - 」
                    fprintf(file," - \n");
                    break;
                case 1:
                    // 奇数の場合：「| |」
                    fprintf(file,"| ");
                    break;
                case 2:
                    // 奇数の場合：「| |」
                    fprintf(file,"| \n");
                    break;
            }
        } else {
            fprintf(file, "  ");
        }
    }

    fprintf(file,"\n\n");

    fclose(file);
}



/*
Moving* mover = new Straight(30);
mover->run();

Straight mover = new Straight(30);
mover.run();

mover.setDist(20);
mover.run();


mover = new Turn();
*/