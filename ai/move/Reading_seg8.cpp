#include "Reading_seg8.h"

/* 
* 数字の読み取り
*/


//--  Moving  --//
Reading_seg8::Reading_seg8(Pointers pt_s, int base_pwm, int* arr_digital)
    : Straight(pt_s, base_pwm), num_img_arr(arr_digital)       // 引数の値でメンバ変数を初期化
{
    color_tmp = Enums::WHITE;
    arr_idx = 0;
}



//--  original  --//
bool Reading_seg8::break_condition() {
    // 一定距離進んで、黒があれば 1、無ければ 0 を、num_img_digital に入れる。
    // 現在の距離を取得。
    now_dist = distMeasure.getNowDist(Enums::Directs::LR_AVG);
    // 現在地の色を取得。
    color_tmp = colorSensor->getColorNumber();
    // 現在地の位置によって、処理を変える。
    switch ( posi_type(now_dist) ) {
        case 0:
        case 1:
            // 何もしない。
            // 数字を読み取る前の範囲を移動中に実行される予定。
            // 緑が黒で認識される問題の解決のため。という意味もある。
            return true;
        case 2:
            if (color_tmp == Enums::BLACK) {
                num_img_arr[arr_idx] = 1;
            }
            return true;
        case 3:
            // 何もしない。
            // 数字を読み取った後の範囲を移動中に実行される予定。
            // 黒（マット）に着いたら止まって欲しいので、止まるようにした。（あくまで保険）
            return color_tmp != Enums::BLACK;
        default:
            return false;
    }
}

int Reading_seg8::posi_type(float dist) {
    // cond_len = 4
    for (int i=0; i<cond_len; i++) {
        if (dist < cond_dists[i]) {
            // 0:~0,  1:0~10,  2:10~130,  3:130~155
            return i;
        }
    }
    return -1;
}



void Reading_seg8::f_write() {
    FILE *file = fopen("read_7seg_8nozi.txt", "a");   

    char arr[5];
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


void Reading_seg8::run(int idx, Enums::Directs ForB, int distance) {
    arr_idx = idx;
    cond_dists[0] = 0;
    cond_dists[0] = distance / 6;
    cond_dists[1] = distance * 5 / 6;
    cond_dists[2] = distance;
    // ［？］Straight の break_condition() が呼ばれる可能性が高い...。
    // → その場合は、 Straight からコピペしてくる。Movng_ex を継承するスタイルに変更。
    Moving_ex::run(ForB, distance);
}


