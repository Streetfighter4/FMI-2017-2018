#include <iostream>
#include <cmath>
#include "Polynomial.h"
#include "Rational.h"

//specialization of the method
//because sqrt can't have Rational as parameter
/*template<>
double Polynomial<Rational>::operator~() const {

    return sqrt(operator%(*this).asDouble());
}
*/

template<typename T>
void run_tests() {

    //some tests ..
    Polynomial<T> A(3);

    std::cout << "enter three nummbers of polynomial A\n";
    std::cin >> A[0] >> A[1] >> A[2];

    std::cout << "A : ";
    A.print();

    Polynomial<T> B(A);
    std::cout << "B :";
    B.print();

    B += A;
    std::cout << "B += A // B:";
    B.print();

    A = A + B;
    std::cout << "A = A + B // A:";
    A.print();


    Polynomial<T> C = A - B;
    std::cout << "C = A - B // B:";
    C.print();

    std::cout << "C -= A // C:";
    C -= A;
    C.print();

    C *= -1;
    std::cout << "C *= -1 // C:";
    C.print();

    C = A * 3;
    std::cout << "C = A * 3 // C:";
    C.print();


    //special operators tests

    Polynomial<T> poly(4); //1, 2, 3, 4

    for (int i = 0; i < 4; i++)
        poly[i] = i + 1;

    std::cout << "Polynomial poly : \n";
    poly.print();

    Polynomial<T> other(4);
    other[0] = 2;
    other[1] = 4;
    other[2] = 6;
    other[3] = 8;

    std::cout <<"\nother.poly = " << other/poly << std::endl;

    other/=poly;
    other.print();
    std::cout << "Polynomial other : \n";

    Polynomial<T> poly2(4); // a perpendicular vector to vec
    poly2[0] = -2;
    poly2[1] = 1;
    poly2[2] = -4;
    poly2[3] = 3;



}

int main() {

    std::cout << "-----running tests with INTs-------\n";
    run_tests<int>();

    std::cout << "\n\n\n-----running tests with DOUBLEs-------\n";
    run_tests<double>();

    std::cout << "\n\n\n-----running tests with CHARs-------\n";
    run_tests<char>();

    std::cout << "\n\n\n-----running tests with RATIONALs-------\n";
    run_tests<Rational>();

    return 0;
}
