#ifndef ENUMS_H_
#define ENUMS_H_
class Enums {
  public:
    enum Directs {
        // Enums::Directs::LEFT
        // （または単に、Enums::LR_AVG）
        // みたいな感じで使う
        FRONT = 1,
        BACK = -1,
        RIGHT = 2,
        LEFT = -2,
        LR_AVG = 0
    };
    enum Colors {
        // colorSensor.getColorNumber() の戻り値
        GREY = 0,    // 無し
        BLACK = 1,   // 黒
        BLUE = 2 ,   // 青
        GREEN = 3,   // 緑
        YELLOW = 4,  // 黄
        RED = 5,     // 赤
        WHITE = 6,   // 白
    };
    enum PID {
          // PID パターンに名前をつけただけ。
          Slow,
          Midium,
          Fast
    };
};

#endif  // ENUMS_H_