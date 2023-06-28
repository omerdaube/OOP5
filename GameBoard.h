#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "List.h"
#include "BoardCell.h"
template <typename list_of_lists>
struct GameBoard{
    typedef list_of_lists board;
    static constexpr int width = board::head::size;
    static constexpr int length = board::size;
};

#endif //OOP5_GAMEBOARD_H