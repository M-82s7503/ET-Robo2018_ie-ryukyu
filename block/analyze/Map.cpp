#include "Map.hpp"


Map::Map()
{
    // マップの初期化
    int i,j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
        blocks[i][j] = NO_EXIST;
        }
    }
}


/* (暗号の解読結果から)ブロックの初期配置を計算する */
void Map::block_jud(int code_solve[5])
{
    int count;
    int x,y;

    for(count = 0; count < N; count++){
        y = code_solve[count]/4;
        x = code_solve[count] - y * 4;
        blocks[y][x] = BEFORE_MOVE_BLOCK;
    }

}
