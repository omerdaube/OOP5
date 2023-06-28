#ifndef OOP5_LIST_H
#define OOP5_LIST_H

template <typename... Ts>
struct List;

template <>
struct List<> {
    static constexpr int size = 0;
};

template <typename T, typename... Ts>
struct List<T, Ts...> {
    typedef T head;
    typedef List<Ts...> next;
    static constexpr int size = sizeof...(Ts) + 1;
};


template <int N, typename L>
struct GetAtIndex {
    typedef L list;
    typedef typename GetAtIndex<N - 1, typename list::next>::value value;
};

template <typename L>
struct GetAtIndex<0, L> {
    typedef L list;
    typedef typename list::head value;
};

template<typename T, typename L>
struct PrependList{
    typedef List<T, typename L::head, typename L::next> list;
};

template <typename T, typename... Ts>
struct PrependList<T, List<Ts...>> {
    typedef List<T, Ts...> list;
};

template <int N, typename T, typename L>
struct SetAtIndex{
    typedef L oldList;
    typedef typename PrependList<typename oldList::head, typename SetAtIndex<N - 1, T, typename oldList::next>::list>::list list;
};

template <typename T, typename L>
struct SetAtIndex<0, T, L>{
    typedef L oldList;
    typedef typename PrependList<T, typename oldList::next>::list list;
};

#endif //OOP5_LIST_H