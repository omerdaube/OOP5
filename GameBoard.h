#include "List.h"
template <typename B, int W, int N>
struct GameBoard{
    typedef B board;
    static constexpr int width = W;
    static constexpr int length = N;
};