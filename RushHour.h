#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "GameBoard.h"
#include "List.h"
#include "MoveVehicle.h"
#include "Utilities.h"


template<typename row, CellType cellType, int idx>
struct SearchColAux{
    static constexpr int col = ConditionalInteger<(GetAtIndex<idx, row>::value::type == cellType),
            idx,
            SearchColAux<row, cellType, idx - 1>::col>::value;
};

template<typename row, CellType cellType>
struct SearchColAux<row, cellType, -1>{
    static constexpr int col = -1;//not found

};

template<typename row, CellType cellType>
struct SearchCol{
    static constexpr int col = SearchColAux<row, cellType, row::size-1>::col;
};



template<typename board, CellType cellType, int rowIdx>
struct SearchRowAux{
    typedef typename GetAtIndex<rowIdx, board>::value currentRow;
    static constexpr int col = SearchCol<currentRow, cellType>::col;
    static constexpr int row = ConditionalInteger<(col != -1),
            rowIdx,
            SearchRowAux<board, cellType, rowIdx - 1>::row>::value;
};

template<typename board, CellType cellType>
struct SearchRowAux<board, cellType, -1>{
    static constexpr int col = -1;//not found
};

template<typename board, CellType cellType>
struct SearchRow{
    static constexpr int row = SearchRowAux<board, cellType, board::size-1>::col;
};

template<typename row, int endIdx, int currIdx>
struct CheckRowEmptyAux{
    static constexpr int isEmpty = ConditionalInteger<(endIdx == currIdx)
                                                , 1
                                                , ConditionalInteger<(GetAtIndex<currIdx, row>::value::type == EMPTY),
                                                                CheckRowEmptyAux<row, endIdx, currIdx-1>::isEmpty,
                                                                0>::value
                                                >::value;
};

template<typename row, int endIdx>
struct CheckRowEmpty{
    static constexpr bool isEmpty = (CheckRowEmptyAux<row, endIdx, row::size-1>::isEmpty == 1);
};


template<typename gameBoard>
struct CheckWin {
    //finding the red car (assuming horizontal)
    typedef typename gameBoard::board board;
    static constexpr int row = SearchRow<board, CellType::X>::row;
    static constexpr int endCol = SearchCol<typename GetAtIndex<row, board>::value, CellType::X>::col;
    static constexpr bool result = CheckRowEmpty<typename GetAtIndex<row, board>::value, endCol>::isEmpty;
};


template<typename gameBoard, typename moves>
struct CheckSolution {
    typedef typename moves::head currentMove;

};


#endif //OOP5_RUSHHOUR_H