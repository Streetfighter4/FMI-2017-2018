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
    std::cout << "enter three numbers of polynomial A\n";
    std::cin >> A;

    std::cout << "A: ";
    A.print();

    Polynomial<T> B(A);
    std::cout << "B :";
    B.print();

    B += A;
    std::cout << "B += A // B: ";
    B.print();

    A = A + B;
    std::cout << "A = A + B // A: ";
    A.print();


    Polynomial<T> C = A - B;
    std::cout << "C = A - B // B: ";
    C.print();

    std::cout << "C -= A // C: ";
    C -= A;
    C.print();

    C *= -1;
    std::cout << "C *= -1 // C: ";
    C.print();

    C = A * 3;
    std::cout << "C = A * 3 // C: ";
    C.print();

    Polynomial<T> D;
    D = C/A;
    std::cout << "D = C/A // D: ";
    D.print();

    C/=A;
    std::cout << "C/=A // C: ";
    C.print();

    Polynomial<T> F;
    F = B%D;
    std::cout << "F = B%D // F: ";
    F.print();

    //special operators tests
    std::cout << "--------------------------------------" << std::endl;
    Polynomial<T> poly(4); //1, 2, 3, 4

    for (int i = 0; i < 4; i++)
        poly[i] = i + 1;

    std::cout << "Polynomial poly : \n";
    poly.print();

    std::cout << "poly first derivative: \n";
    poly--;
    poly.print();

    std::cout << "poly second derivative but with prefix operator: \n";
    --poly;
    poly.print();

    Polynomial<T> integral(4);
    for (int i = 0; i < 4; i++)
        integral[i] = i * 10;

    std::cout << "polynomial for integrate: ";
    integral.print();

    std::cout << "integrate polynomial: \n";
    integral++;
    integral.print();

    std::cout << "integrate polynomial but with prefix operator: \n";
    ++integral;
    integral.print();

    std::cout << "Enter a value of point to sum the polynomial: ";
    T a;
    std::cin >> a;
    std::cout << "Sum of integral in point " << a << " is: " << integral(a) << std::endl;

    Polynomial<T> integral1(4);
    for (int i = 0; i < 4; i++)
        integral1[i] = i + 5;

    std::cout << "polynomial for integrate: ";
    integral1.print();

    std::cout << "Enter interval with 2 points: ";
    T b, c;
    std::cin >> b >> c;
    std::cout << "Area of integral in interval (" << b << ", " << c << ")" <<" is: " << integral1(b, c) << std::endl;

}

int main() {

    std::cout << "-----running tests with INTs-------\n";
    run_tests<int>();

    std::cout << "\n\n\n-----running tests with DOUBLEs-------\n";
    run_tests<double>();

    std::cout << "\n\n\n-----running tests with RATIONALs-------\n";
    std::cout << "Enter 3 rational numbers for simplify and test operator ->\n";
    Polynomial<Rational> poly(3);
    std::cin >> poly;
    for (Polynomial<Rational>::iterator<Rational> it = poly.begin(); it != poly.end(); ++it) {
        it->simplify();
    }
    poly.print();
    return 0;
}
