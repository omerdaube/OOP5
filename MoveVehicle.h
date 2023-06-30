#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "Direction.h"
#include "CellType.h"
#include "Utilities.h"
#include "List.h"
template <CellType T, Direction D, int A>
struct Move{
    static constexpr CellType type = T;
    static_assert(type != CellType::EMPTY, "Move cannot be empty");
    static constexpr Direction direction = D;
    static constexpr int amount = A;
};

//template <typename boardGame, int R, int C, int Corigin, Direction D>
//struct FindStartPoint{ //---  : direction (vert.)
//    typedef typename boardGame::board rows_list;
//    typedef typename  GetAtIndex<R, rows_list>::value row;
//    static constexpr bool chk = GetAtIndex<Corigin, row>::value::type == GetAtIndex<C, row>::value::type;
//    static constexpr int answer = ConditionalInteger<chk,
//            FindStartPoint<boardGame, R, C - 1, Corigin, D>::answer + 1, 0>::answer;
//};
//
//template <typename boardGame, int R, int C, int Corigin, Direction D>
//struct FindEndPoint{ //---  : direction (vert.)
//    typedef typename boardGame::board rows_list;
//    typedef typename  GetAtIndex<R, rows_list>::value row;
//    static constexpr bool chk = GetAtIndex<Corigin, row>::value::type == GetAtIndex<C, row>::value::type;
//    static constexpr int answer = ConditionalInteger<chk,
//            FindStartPoint<boardGame, R, C + 1, Corigin, D>::answer + 1, 0>::answer;
//};


template <typename list, CellType car, int currIdx>
struct FindStartIndex{
    typedef typename GetAtIndex<currIdx, list>::value cell;
    static constexpr CellType carHere = cell::type;
    static constexpr int startIdx = ConditionalInteger<carHere == car,
            FindStartIndex<list, car, currIdx - 1>::startIdx,
            currIdx + 1>::value;
};

template <typename list, CellType car>
struct FindStartIndex<list, car, 0>{
    static constexpr int startIdx = 0;
};


//template <typename list, CellType car, int currIdx, int listSize>
//struct FindEndIndexAux{
//    typedef typename GetAtIndex<currIdx, list>::value cell;
//    static constexpr CellType carHere = cell::type;
//    static constexpr int EndIdx = ConditionalInteger<
//            (carHere == car),
//            FindEndIndexAux<list, car, currIdx + 1, listSize>::EndIdx,
//            currIdx - 1>::value;
//};
//
//template <typename list, CellType car,int currIdx>
//struct FindEndIndexAux<list, car, currIdx, currIdx + 1>{
//    static constexpr int EndIdx = currIdx;
//};
//
//
//template <typename list, CellType car, int currIdx>
//struct FindEndIndex{
//    static constexpr int EndIdx = FindEndIndexAux<list, car, currIdx, list::size>::EndIdx;
//};

template <typename row, typename carCell, int startIdx, int endIdx, int amount>
struct moveForward{
    static_assert(GetAtIndex<endIdx + 1, row>::value::type == CellType::EMPTY, "collision!!");
    typedef typename SetAtIndex<startIdx, BoardCell<EMPTY, UP, 0>, row>::list startEmptiedList;
    typedef typename SetAtIndex<endIdx + 1, carCell, startEmptiedList>::list listAfterMove;
    typedef typename moveForward<listAfterMove, carCell, startIdx+1, endIdx+1, amount-1>::final final;
};

template <typename row, typename carCell, int startIdx, int endIdx>
struct moveForward<row, carCell, startIdx, endIdx, 0>{
    typedef row final;
};



template <typename row, typename carCell, int startIdx, int endIdx, int amount>
struct moveBack{
    static_assert(GetAtIndex<startIdx - 1, row>::value::type == CellType::EMPTY, "collision!!");
    typedef typename SetAtIndex<endIdx, BoardCell<EMPTY, UP, 0>, row>::list endEmptiedList;
    typedef typename SetAtIndex<startIdx - 1, carCell, endEmptiedList>::list listAfterMove;
    typedef typename moveBack<listAfterMove, carCell, startIdx-1, endIdx-1, amount-1>::final final;
};

template <typename row, typename carCell, int startIdx, int endIdx>
struct moveBack<row, carCell, startIdx, endIdx, 0>{
    typedef row final;
};


template <typename row, typename carCell, int startIdx, int endIdx, int amount, Direction dir>
struct moveByDir;


template <typename row, typename carCell, int startIdx, int endIdx, int amount>
struct moveByDir<row, carCell, startIdx, endIdx, amount, RIGHT>{
    typedef typename moveForward<row, carCell, startIdx, endIdx, amount>::final newList;
};


template <typename row, typename carCell, int startIdx, int endIdx, int amount>
struct moveByDir<row, carCell, startIdx, endIdx, amount, LEFT>{
    typedef typename moveBack<row, carCell, startIdx, endIdx, amount>::final newList;
};


//only works for horizontal vehicles, & right
template <typename boardGame, int R, int C, Direction D, int A>
struct MoveVehicle{
    static_assert(R >= 0 && R < boardGame::length, "Row out of bounds");
    static_assert(C >= 0 && C < boardGame::width, "Column out of bounds");
    typedef typename boardGame::board rows_list;
    typedef typename GetAtIndex<R, rows_list>::value row;
    typedef typename GetAtIndex<C, row>::value cell;
    static_assert(cell::type != CellType::EMPTY, "Cell is empty");
    static_assert((cell::direction == D) ||
                  (cell::direction == Direction::RIGHT && D == Direction::LEFT) ||
                  (cell::direction == Direction::LEFT && D == Direction::RIGHT) ||
                  (cell::direction == Direction::UP && D == Direction::DOWN) ||
                  (cell::direction == Direction::DOWN && D == Direction::UP), "Direction does not match");

    static constexpr int startIdx = FindStartIndex<row, cell::type, C>::startIdx;
//    static constexpr int endIdx = FindEndIndex<row, cell::type, C>::EndIdx;
    static constexpr int endIdx = startIdx + cell::length - 1;
    typedef typename moveByDir<row, cell, startIdx, endIdx, A, cell::direction>::newList newRow;
    typedef typename SetAtIndex<R, newRow, rows_list>::list newBoard;
    typedef GameBoard<newBoard> board;
};

//template <typename boardGame, int R, int C, Direction D>
//struct MoveVehicle<boardGame, R, C, D, 0>{
//    typedef boardGame board;
//};


//template <typename boardGame, int R, int Corigin, int Cend, Direction D, int A>
//struct moveAllPieces{
//
//};

#endif //OOP5_MOVEVEHICLE_H

