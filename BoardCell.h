//
// Created by nizni on 28/06/2023.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H
#include "Direction.h"
#include "CellType.h"
template <CellType CT, Direction D, int N>
struct BoardCell{
    static constexpr CellType type = CT;
    static constexpr Direction direction = D;
    static constexpr int length = N;
};
#endif //OOP5_BOARDCELL_H
