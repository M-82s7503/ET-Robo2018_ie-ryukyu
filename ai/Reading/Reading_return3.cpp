#include "Reading_return3.h"

/* 
* 数字の読み取り
* ：アナログ数字

    １列一気に読むスタイルで！
    〜分割 を変えやすいように設計。
*/


Reading_return3::Reading_return3(Pointers pt_s, int base_pwm, float* arr_analog, int distance):
    Moving(pt_s)
    , distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
    , speed(base_pwm), num_img_arr(arr_analog)       // 引数の値でメンバ変数を初期化
{
    color_tmp = Enums::WHITE;
    //arr_idx = 0;
    break_dist = distance / divide;
}


// オーバーライド：Moving
/*
float Reading_return3::decide_pwm_r(){
    return speed;
}
float Reading_return3::decide_pwm_l(){
    return speed;
}
*/
bool Reading_return3::break_condition() {
    // 1マス分の処理
    ++while_c;
    // 処理オーバーにならないように調整。
    if ( while_c % accuracy == 2 ) {
        // 現在地の色を取得。
        if ((int)(colorSensor->getColorNumber()) == Enums::BLACK) {
            ++color_tmp;
        }
    }
    // 現在の距離を取得。
    now_dist = distMeasure.getNowDist(Enums::Directs::LR_AVG);
    // １マス終わり位置まできたら、抜ける。
    if (now_dist >= break_dist) {
        num_img_arr[start_idx+c_idx] = color_tmp / (while_c / accuracy);
        return true;
    } else return false;
}




void Reading_return3::f_write() {
    FILE *file = fopen("read_3return.txt", "a");   

    char arr[7];

    // 配列で書き出し
    fprintf(file, "{");
    for(int i=0; i<3*divide; i++){
        sprintf(arr, "%.2f, ", num_img_arr[i]);
        //clock.sleep(1000);  //画面表示を見やすくするためらしい。
        fprintf(file, "%s", arr);
    }
    fprintf(file, "}\n\n\n");

    // 一旦初期化
    for (int i=0; i<6; i++){
        arr[i] = ' ';
    }
    // わかりやすく書き出し
    for(int i=0; i<3*divide; i++){
        switch (i%3) {
            case 0:
                // 3列目
                arr[3] = convBlacknessChar(num_img_arr[i]);
                break;
            case 1:
                // 2列目
                arr[2] = convBlacknessChar(num_img_arr[i]);
                break;
            case 2:
                // 1列目
                arr[1] = convBlacknessChar(num_img_arr[i]);
                // 3列分揃ったので書き出し。
                fprintf(file,"%s", arr);
                break;
        }
    }
    fprintf(file,"\n\n");
    fclose(file);
}

char Reading_return3::convBlacknessChar(float blackness) {
    if (blackness < 0.3) {
        return ' ';
    } else if (blackness < 0.5) {
        return '~';
    } else if (blackness < 0.7) {
        return '#';
    } else if (blackness < 1.0) {
        return '@';
    } else {
        return ' ';
    }   
}



//--  original  --//
void Reading_return3::run(int return_th) {
    start_idx = (return_th-1) * divide;
    // divide回 繰り返す。
    for (c_idx=0; c_idx<divide; c_idx++) {
        while_c = 0;
        color_tmp = 0;
        distMeasure.init();
        Moving::run();
    }
}


