#include "List.h"
#include "Utilities.h"
#include "int.h"
#include <iostream>
#include "MoveVehicle.h"
using namespace std;
int main(){
    typedef List<Int<1>, Int<89>, Int<3>> list;
    static_assert(list::head::value == 1, ""); // = Int<1>
    //typedef typename list::next listTail; // = List<Int<2>, Int<3>>
    cout << list::size; // = 3
    cout << GetAtIndex<1, list>::value::value; // = Int<1>
    //GetAtIndex<2, list>::value;
    typedef typename PrependList<Int<4>, list>::list newList; // = List< Int<4>,
    cout << "h" << GetAtIndex<0, newList>::value::value << "h";
    typedef typename SetAtIndex<2, Int<868696>, newList>::list newList2; // = List< Int<4>, Int<2>, Int<868696>>
    cout << GetAtIndex<2, newList2>::value::value;
    typedef typename Conditional<(0 == 1), Int<0>, Int<1>>::value test1; // = Int<0>
    cout << "test1::"  << test1::value;

    int amount = Move<X, RIGHT, 1>::amount;
    return 0;
}