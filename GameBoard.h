#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "List.h"
#include "BoardCell.h"
template <typename B, int W, int N>
struct GameBoard{
    typedef B board;
    static constexpr int width = W;
    static constexpr int length = N;
};

#endif //OOP5_GAMEBOARD_H