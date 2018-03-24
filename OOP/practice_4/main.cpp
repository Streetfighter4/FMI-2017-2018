//
// Created by yasen on 3/21/18.
//
#include <iostream>
#include "Clock.h"

using std::cout;
using std::cin;

int main() {
    Clock c1;

    c1.setHour(1);
    c1.setMinute(10);
    c1.setSecond(37);
    c1.print();

    Clock c2(1, 2, 3);
    c2.print();

    return 0;
}
