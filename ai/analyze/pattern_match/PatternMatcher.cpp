#include "PatternMatcher.hpp"


PatternMatcher::PatternMatcher():
    is100per(false), ans_D(0), ans_A(0)
{

}

void PatternMatcher::solve_D(const int* readImg) {
    /**
     * 答えの配列との差を一つずつ計算し、
     * 差が最も少なかったものを採用する。
     */
    float count_tmp;
    for (int8_t i=0; i<8; i++) {
        count_tmp = 0;
        // 一つずつ検証
        for (int8_t px=0; px<7; px++) {
            count_tmp += abs(ansImg_D[i][px] - readImg[px]);
        }
        // 類似度（％） に変換
        result_A_probs[i] = 1 - (count_tmp / 7.0);
        if (result_A_probs[ans_D] < result_A_probs[i]) {
            ans_D = i;
        }
        // 100% が出たら、その時点で終了。（それ以上やっても意味ないので。）
        if (result_A_probs[i] >= 0.98) {  //誤差を考慮し、1にしない。
            is100per = true;
            break;
        }
    }
}


void PatternMatcher::solve_A(const float* readImg) {
    /**
     * 答えの配列との差を一つずつ計算し、
     * 差が最も少なかったものを採用する。
     */
    float count_tmp;
    for (int8_t i=0; i<8; i++) {
        count_tmp = 0;
        // 一つずつ検証
        for (int8_t px=0; px<7; px++) {
            count_tmp += abs(ansImg_A[i][px] - readImg[px]);
        }
        // 類似度（％） に変換
        result_A_probs[i] = 1 - (count_tmp / 15.0);
        if (result_A_probs[ans_A] < result_A_probs[i]) {
            ans_A = i;
        }
        // 100% が出たら、その時点で終了。（それ以上やっても意味ないので。）
        if (result_A_probs[i] >= 0.95) {  //誤差を考慮し、1にしない。
            is100per = true;
            break;
        }
    }
}

