//
// Created by yasen on 5/31/18.
//

#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H

#include <cstddef>
#include <iostream>

template <typename T>
class Polynomial {
public:
    Polynomial();
    Polynomial(size_t maxDeg);
    Polynomial(const Polynomial& poly);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();

    const T operator[](size_t) const;
    T& operator[](size_t);

    T& operator+=(const T&);

    T& operator-=(const T&);

    T& operator*=(const T&);
    T operator*(const T&) const;
    T& operator*=(T);
    T operator*(T) const;

    T& operator/=(const T&);
    T operator/(const T&) const;
    T& operator/=(T);
    T operator/(T) const;

    T& operator%=(const T&);
    T operator%(const T&) const;

    T operator()(const T&);
    double operator()(const T&, const T&);


    Polynomial& operator++(); //<-prefix ++i;
    const Polynomial operator++(int); //takes int as a rule , but uses 0
    //constant return, because i++++ shouldn't be possible

    Polynomial& operator--();
    const Polynomial operator--(int);

    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
    friend std::istream& operator>>(std::istream&, Polynomial&);



    friend bool operator==(const Polynomial&, const Polynomial&);
    friend bool operator<(const Polynomial&, const Polynomial&);


private:
    void resize(size_t newSize);

private:
    T* coeff;
    size_t  maxDeg;
    size_t* degArr;

};

inline
bool operator==(const Polynomial& rhs, const Polynomial& lhs) {
    if (rhs.maxDeg != lhs.maxDeg)
        return false;
    else {
        for (int i = 0; i < rhs.maxDeg; ++i) {
            if(rhs.coeff[i] != lhs.coeff[i])
                return false;
        }
    }
    return true;
}

inline
bool operator!=(const Polynomial& rhs, const Polynomial& lhs) {
    return !(rhs == lhs);
}

inline
bool operator<(const Polynomial& lhs, const Polynomial& rhs) {

    return (lhs.maxDeg < rhs.maxDeg);
}

inline
bool operator>(const Polynomial& lhs, const Polynomial& rhs) {

    return rhs < lhs;
}

inline
bool operator<=(const Polynomial& lhs, const Polynomial& rhs) {

    return !(lhs > rhs);
}

inline
bool operator>=(const Polynomial& lhs, const Polynomial& rhs) {

    return !(lhs < rhs);
}

const Polynomial operator+(const Polynomial& , const Polynomial&);
const Polynomial operator-(const Polynomial& , const Polynomial&);
const Polynomial operator*(const Polynomial& , const Polynomial&);
const Polynomial operator/(const Polynomial& , const Polynomial&);


#endif //POLYNOMIAL_POLYNOMIAL_H
