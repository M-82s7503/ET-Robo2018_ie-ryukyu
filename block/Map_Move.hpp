
/* Map関するクラス */
class Map_Move{
public:
  int block[N][N]; //block exist                                                                                    
  int map_color[N][N]; //map color                                                                                  
  int car_x,car_y;
  int move_x,move_y;
  int car_degree;
public:
  Map_Move();
  void block_jud(int solove_num[5]);  // 暗号よりブロックの初期配置の計算                                           
  void priority_move(int* move_x,int* move_y,int block[N][N]); // 運ぶブロックの優先順位を決める
  void move_point(int block_color,int* move_x,int* move_y,int block[N][N]); // ブロックを移動させる座標を決定する                                           
};
