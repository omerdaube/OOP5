#include "List.h"
#include "Direction.h"
#include "CellType.h"
template <CellType CT, Direction D, int N>
struct BoardCell{
    static constexpr CellType type = CT;
    static constexpr Direction direction = D;
    static constexpr int length = N;
    ///TO DO: IMP
};