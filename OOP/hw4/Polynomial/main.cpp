#include <iostream>
#include "Polynomial.h"

int main() {

    Polynomial<int> poly1(3);
    Polynomial<int> poly2(4);

    for (int i = 0; i < 3; ++i) {
        std::cin >> poly1[i];
    }
    for (int j = 0; j < 4; ++j) {
        std::cin >> poly2[j];
    }

    std::cout << poly2 << std::endl;

    std::cout << std::endl;
    //std::cout << poly1 + poly2 << std::endl;
    //std::cout << poly1 - poly2 << std::endl;

    //Polynomial<int> poly3;
    //poly3 = poly1;
    poly2%=poly1;
    std::cout << poly2 << std::endl;
    //std::cout << poly2(2, 3) << std::endl;
    //std::cout << poly3 << std::endl;

    std::cout << poly1(2) << std::endl;
    //poly1 += poly2;
    //poly3 -= poly2;

    std::cout << std::endl;

    poly1 *= poly2;
    std::cout << poly1 << std::endl;
    //std::cout << poly3 << std::endl;

    return 0;
}