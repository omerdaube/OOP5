

template <bool Expr, typename T, typename F>
struct Conditional;


template <typename T, typename F>
struct Conditional <true, T, F > {
    typedef T value;
};

template <typename T, typename F>
struct Conditional <false, T, F > {
    typedef F value;
};

template <bool Expr, int T, int F>
struct ConditionalInteger{
    static constexpr int value = Expr ? T : F;
};

