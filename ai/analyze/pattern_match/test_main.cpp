#include <stdio.h>
#include "answer_arrays.h"
#include "PatternMatcher.hpp"


int main(int argc, char const *argv[]) {
    PatternMatcher ptMatch;
/*    for (int a_id=0; a_id<8; a_id++) {
        printf("[");
        for (int i=0; i<7; i++) {
            printf("%d,", ansImg_D[a_id][i]);
        }
        printf("]\n");
    }*/


    printf("\n< digital >\n");
    for (int ans=0; ans<8; ans++) {
        printf("ans = %d\n", ans);
        ptMatch.solve_D(ansImg_D[ans]);
        printf("予想：%d ,  100%%：%s\n", ptMatch.getAns_D(), ptMatch.is100per ? "true" : "false");
        printf("[");
        for (int a_id=0; a_id<8; a_id++) {
            printf("%f, ", ptMatch.result_D_probs[a_id]);
        }
        printf("]\n\n");
    }

    return 0;
}


