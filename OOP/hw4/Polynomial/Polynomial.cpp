//
// Created by yasen on 5/31/18.
//

#include "Polynomial.h"

template<typename T>
std::istream &operator>>(std::istream& ifs, Polynomial<T>& poly) {
    for (int i = 0; i < poly.maxDeg; ++i) {
        ifs >> poly.coeff[i];
    }
    return ifs;
}
