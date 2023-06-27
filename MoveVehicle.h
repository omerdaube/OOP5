#include "Direction.h"
#include "CellType.h"
#include "Utilities.h"
#include "List.h"
template <CellType T, Direction D, int A>
struct Move{
    static constexpr CellType type = T;
    static_assert(type != CellType::EMPTY, "Move cannot be empty");
    static constexpr Direction width = D;
    static constexpr int amount = A;
};

template <typename boardGame, int R, int C, int Corigin, Direction D>
struct FindStartPoint{ //---  : direction (vert.)
    typedef typename  GetAtIndex<R, boardGame>::value rowList;
    static constexpr bool chk = GetAtIndex<Corigin, rowList>::value::type == GetAtIndex<C, rowList>::value::type;
    static constexpr int answer = ConditionalInteger<chk,
            FindStartPoint<boardGame, R, C - 1, Corigin, D>::answer + 1, 0>::answer;
};

template <typename boardGame, int R, int C, int Corigin, Direction D>
struct FindEndPoint{ //---  : direction (vert.)
    typedef typename  GetAtIndex<R, boardGame>::value rowList;
    static constexpr bool chk = GetAtIndex<Corigin, rowList>::value::type == GetAtIndex<C, rowList>::value::type;
    static constexpr int answer = ConditionalInteger<chk,
            FindStartPoint<boardGame, R, C + 1, Corigin, D>::answer + 1, 0>::answer;
};


//only works for horizontal vehicles, & right
template <typename boardGame, int R, int C, Direction D, int A>
struct MoveVehicle{
    static_assert(R >= 0 && R < boardGame::length, "Row out of bounds");
    static_assert(C >= 0 && C < boardGame::width, "Column out of bounds");
    typedef typename  GetAtIndex<R, boardGame>::value rowList;
    static_assert(GetAtIndex<C, rowList>::value::type != CellType::EMPTY, "Cell is empty");
    static_assert((GetAtIndex<C, rowList>::value::direction == D) ||
            (GetAtIndex<C, rowList>::value::direction == Direction::RIGHT && D == Direction::LEFT)||
            (GetAtIndex<C, rowList>::value::direction == Direction::LEFT && D == Direction::RIGHT)||
            (GetAtIndex<C, rowList>::value::direction == Direction::UP && D == Direction::DOWN)||
            (GetAtIndex<C, rowList>::value::direction == Direction::DOWN && D == Direction::UP), "Direction does not match");
    typedef boardGame newBoard;
    //static_assert((D==Direction::RIGHT && ));
    typedef typename GetAtIndex<FindStartPoint<boardGame, R,C,C,D>::answer, rowList>::value start_cell;
    typedef typename GetAtIndex<FindEndPoint<boardGame, R,C,C,D>::answer, rowList>::value end_cell; //one after
    //SetAtIndex<>

    typedef typename MoveVehicle<boardGame, R, C + 1, D, A - 1>::board board;
    //need to change the board
};

template <typename boardGame, int R, int C, Direction D>
struct MoveVehicle<boardGame, R, C, D, 0>{
    typedef boardGame board;
};


template <typename boardGame, int R, int Corigin, int Cend, Direction D, int A>
struct moveAllPieces{

};

