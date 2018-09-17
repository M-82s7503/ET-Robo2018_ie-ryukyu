#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include "answer_arrays.h"


class PatternMatcher {
public:
    PatternMatcher();
    // 引数：読み取った数字カードの情報
    void solve_D(const int* read_img);
    void solve_A(const float* read_img);

    int getAns_D() {
        return ans_D;
    }
    int getAns_A() {
        return ans_A;
    }
    
    // もし読み取りに失敗した場合に、
    // 今あるデータで最良の答えを導き出す関数。
    // 「戻って計測し直す」もあり。
    void select_goodAns() {}

    float result_D_probs[8]; 
    float result_A_probs[8];
    bool is100per;

private:
    int ans_D;
    int ans_A;
};
