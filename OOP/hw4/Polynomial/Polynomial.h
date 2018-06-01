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
    explicit Polynomial(size_t maxDeg);
    Polynomial(const Polynomial& poly);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();

    const T operator[](size_t) const;
    T& operator[](size_t);


    Polynomial& operator+=(const Polynomial&);
    Polynomial<T> operator+(const Polynomial&);

    Polynomial& operator-=(const Polynomial&);
    Polynomial<T> operator-(const Polynomial&);


    Polynomial& operator*=(const Polynomial&); //multiply polynomial with polynomial
    Polynomial operator*(const Polynomial&) const; //multyiply polynomial with polynomial
    Polynomial& operator*=(T); //multiply polynomial with T
    Polynomial operator*(T) const; //multiply polynomial with T

    Polynomial& operator/=(const Polynomial&);
    Polynomial operator/(const Polynomial&) const;
    Polynomial& operator/=(T);
    Polynomial operator/(T) const;

    Polynomial& operator%=(const Polynomial&);
    Polynomial operator%(const Polynomial&) const;

    T operator()(const T&);
    double operator()(const T&, const T&);


    Polynomial& operator++();
    const Polynomial operator++(int);

    Polynomial& operator--();
    const Polynomial operator--(int);

    friend std::ostream& operator<<(std::ostream& ofs, const Polynomial<T>& poly) {
        for (int i = 0; i < poly.maxDeg; ++i) {
            ofs << poly.coeff[i] << "x^" << i << ' ';
        }

        return ofs;
    }
    friend std::istream& operator>>(std::istream&, Polynomial<T>&);

    friend bool operator==(const Polynomial<T>&, const Polynomial<T>&);
    friend bool operator<(const Polynomial<T>&, const Polynomial<T>&);


private:
    void resize(size_t newSize);
    void copy(const Polynomial<T>&);

private:
    T* coeff;
    size_t  maxDeg{};

};


template <typename T>
inline bool operator==(const Polynomial<T>& rhs, const Polynomial<T>& lhs) {
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

template <typename T>
inline bool operator!=(const Polynomial<T>& rhs, const Polynomial<T>& lhs) {
    return !(rhs == lhs);
}

template <typename T>
inline bool operator<(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    return (lhs.maxDeg < rhs.maxDeg);
}

template <typename T>
Polynomial<T>::Polynomial(): coeff(nullptr), maxDeg(0) { }

template <typename T>
Polynomial<T>::Polynomial(size_t maxDeg) {
    coeff = new T[maxDeg];
    this->maxDeg = maxDeg;
}

template <typename T>
void Polynomial<T>::copy(const Polynomial& other) {

    coeff = new T[other.maxDeg];
    maxDeg = other.maxDeg;

    for (size_t i = 0; i < maxDeg; i++)
        coeff[i] = other.coeff[i];

}

template <typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& poly) {
    copy(poly);
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& other) {
    if(this != &other) {
        delete[] coeff;
        copy(other);
    }
    return *this;
}

template <typename T>
Polynomial<T>::~Polynomial() {
    delete[] coeff;
}

template <typename T>
void Polynomial<T>::resize(size_t newSize) {
    if (coeff == nullptr) {

        coeff = new T[newSize];
        maxDeg = newSize;
    } else {

        T* old = coeff;
        coeff = new T[newSize];

        for (size_t i = 0; i < maxDeg; i++)
            coeff[i] = old[i];

        delete[] old;
        maxDeg = newSize;
    }
}

template <typename T>
const T Polynomial<T>::operator[](size_t pos) const {
    if (pos >= maxDeg)
        const_cast<Polynomial*>(this)->resize(pos + 1);

    return coeff[pos];
}

template <typename T>
T& Polynomial<T>::operator[](size_t pos) {
    if (pos >= maxDeg)
        resize(pos + 1);

    return coeff[pos];
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& other) {
    if(other.maxDeg > maxDeg)
        resize(other.maxDeg);

    for (int i = 0; i < other.maxDeg; ++i) {
        coeff[i] += other.coeff[i];
    }
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& other) {
    Polynomial<T> poly(*this);
    poly += other;

    return poly;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& other) {
    if(other.maxDeg > maxDeg)
        resize(other.maxDeg);

    for (int i = 0; i < other.maxDeg; ++i) {
        coeff[i] -= other.coeff[i];
    }
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& other) {
    Polynomial<T> poly(*this);
    poly -= other;

    return poly;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& other) {
    Polynomial<T>* resPoly = new Polynomial<T>[maxDeg + other.maxDeg -1];

    for (int i = 0; i < maxDeg; ++i) {
        for (int j = 0; j < other.maxDeg; ++j) {
            std::cout << "i: " << i << " j: " << j << std::endl;

            std::cout << resPoly->coeff[i+j] << std::endl;
            std::cout << coeff[i] << std::endl;
            std::cout << other.coeff[j] << std::endl;
            resPoly->coeff[i+j] += (coeff[i]*other.coeff[j]);
        }
    }
    return *resPoly;
}


template <typename T>
inline bool operator>(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    return rhs < lhs;
}

template <typename T>
inline bool operator<=(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    return !(lhs > rhs);
}

template <typename T>
inline bool operator>=(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {

    return !(lhs < rhs);
}

template <typename T>
const Polynomial<T> operator*(const Polynomial<T>& , const Polynomial<T>&);

template <typename T>
const Polynomial<T> operator/(const Polynomial<T>& , const Polynomial<T>&);

#endif //POLYNOMIAL_POLYNOMIAL_H
