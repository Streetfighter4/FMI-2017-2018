//
// Created by yasen on 5/31/18.
//

#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H

#include <cstddef>
#include <iostream>
#include <stdexcept>


template <typename T>
class Polynomial {
public:
    template <typename I>
    class iterator {
    public:
        I* it;

        explicit iterator(I* coeff) : it(coeff) {};

    public:
        iterator<I>& operator++() {
            ++this->it;
            return *this;
        }
        const iterator<I> operator++(int) {
            iterator it(*this);
            this->operator++();
            return it;
        }

        iterator<I>& operator--() {
            --this->it;
            return *this;
        }
        const iterator<I> operator--(int) {
            iterator it(*this);
            this->operator--();
            return it;
        }

        inline bool operator==(const iterator<I>& other) const { return it == other.it; }
        inline bool operator!=(const iterator<I>& other) const { return !(*this == other); }
        inline bool operator<(const iterator<I>& other) const { return it < other.it; }
        inline bool operator>(const iterator<I>& other) const { return *this < other; }
        inline bool operator<=(const iterator<I>& other) const { return !(*this > other); }
        inline bool operator>=(const iterator<I>& other) const { return !(*this < other); }


        inline const I* operator->() { return &(this->it); }
        inline const I& operator*() { return *(this->it); }

    };

public:
    Polynomial();
    explicit Polynomial(size_t maxDeg);
    Polynomial(const Polynomial<T>&);
    Polynomial<T>& operator=(const Polynomial<T>&);
    ~Polynomial();


public:
    void print(std::ostream& = std::cout) const;
public:
    iterator<T> begin() const { return iterator<T>(coeff); }
    iterator<T> end() const { return iterator<T>(coeff+maxDeg); }

public:
    const T operator[](size_t) const;
    T& operator[](size_t);


    Polynomial<T>& operator+=(const Polynomial<T>&);
    Polynomial<T> operator+(const Polynomial<T>&) const;

    Polynomial<T>& operator-=(const Polynomial<T>&);
    Polynomial<T> operator-(const Polynomial<T>&) const;


    Polynomial<T>& operator*=(const Polynomial<T>&); //multiply polynomial with polynomial
    Polynomial<T> operator*(const Polynomial<T>&) const; //multyiply polynomial with polynomial
    Polynomial<T>& operator*=(T); //multiply polynomial with T
    Polynomial<T> operator*(T) const; //multiply polynomial with T

    Polynomial<T>& operator/=(const Polynomial<T>&);
    Polynomial<T> operator/(const Polynomial<T>&) const;
    Polynomial<T>& operator/=(T);
    Polynomial<T> operator/(T) const;

    Polynomial<T>& operator%=(const Polynomial<T>&);
    Polynomial<T> operator%(const Polynomial<T>&) const;

    T operator()(const T&);
    T operator()(const T&, const T&);


    Polynomial<T>& operator++();
    const Polynomial<T> operator++(int);

    Polynomial<T>& operator--();
    const Polynomial<T> operator--(int);

    friend std::ostream& operator<<(std::ostream& ofs, const Polynomial<T>& poly) {
        poly.print(ofs);
        return ofs;
    }
    friend std::istream& operator>>(std::istream& ifs, Polynomial<T>& poly) {
        for (int i = 0; i < poly.maxDeg; ++i) {
            ifs >> poly.coeff[i];
        }
        return ifs;
    }

    inline bool operator==(const Polynomial<T>& other) {
        if (maxDeg != other.maxDeg)
            return false;
        else {
            for (int i = 0; i < maxDeg; ++i) {
                if(coeff[i] != other.coeff[i])
                    return false;
            }
        }
        return true;
    }

    inline bool operator!=(const Polynomial<T>& other) {
        return !(*this == other);
    }


    inline bool operator<(const Polynomial<T>& other) {
        return (maxDeg < other.maxDeg);
    }

    inline bool operator>(const Polynomial<T>& other) {
        return *this < other;
    }

    inline bool operator<=(const Polynomial<T>& other) {
        return !(*this > other);
    }

    inline bool operator>=(const Polynomial<T>& other) {
        return !(*this < other);
    }

private:
    void resize(size_t newSize);
    void copy(const Polynomial<T>&);
    Polynomial<T> division(const Polynomial<T>&);
private:
    T* coeff;
    size_t maxDeg;

};



template <typename T>
Polynomial<T>::Polynomial(): coeff(nullptr), maxDeg(0) { }

template <typename T>
Polynomial<T>::Polynomial(size_t maxDeg) : maxDeg(maxDeg) {
    coeff = new T[maxDeg];
}

template <typename T>
void Polynomial<T>::copy(const Polynomial<T>& other) {

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
        throw std::out_of_range("invalid index");

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
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& other) const {
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
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& other) const {
    Polynomial<T> poly(*this);
    poly -= other;

    return poly;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& other) {
    size_t resDeg = maxDeg + other.maxDeg - 1;
    Polynomial<T> resPoly(resDeg);

    for (int k = 0; k < resDeg; ++k) {
        resPoly.coeff[k] = 0;
    }
    for (int i = 0; i < maxDeg; ++i) {
        for (int j = 0; j < other.maxDeg; ++j) {
            resPoly.coeff[i+j] += (coeff[i]*other.coeff[j]);
        }
    }

    *this = resPoly;

    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(T multy) {
    for (int i = 0; i < maxDeg; ++i) {
        coeff[i] *= multy;
    }
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& other) const {
    Polynomial<T> poly(*this);
    poly *= other;

    return poly;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator*(T multy) const {
    Polynomial<T> poly(*this);
    poly *= multy;

    return poly;
}

template<typename T>
T Polynomial<T>::operator()(const T& elem) {
    T res(0);
    for (int i = 0; i < maxDeg; ++i) {
        T res1(1);
        for (int j = 0; j < i; ++j) {
            res1 *= elem;
        }
        res1 *= coeff[i];
        res += res1;
    }
    return res;
}

template<typename T>
T Polynomial<T>::operator()(const T& a, const T& b) {
    if(a > b) {
        return 0;
    }
    return (++(*this))(b) - (*this)(a);
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator++() {
    Polynomial<T> poly(maxDeg + 1);
    for (int j = 0; j < poly.maxDeg; ++j) {
        poly[j] = 0;
    }
    for (int i = 0; i < poly.maxDeg-1; ++i) {
        poly.coeff[i+1] = (coeff[i]/(i+1));
    }

    *this = poly;
    return *this;
}

template<typename T>
const Polynomial<T> Polynomial<T>::operator++(int) {
    Polynomial<T> temp(*this); //old value
    this->operator++(); //increment our value

    return temp; //return the old
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator--() {
    Polynomial<T> poly(maxDeg - 1);

    for (int i = 0; i < poly.maxDeg; ++i) {
        poly.coeff[i] = (coeff[i+1]*(i+1));
    }

    *this = poly;
    return *this;
}

template<typename T>
const Polynomial<T> Polynomial<T>::operator--(int) {
    Polynomial<T> temp(*this);
    this->operator--();

    return temp;
}

template<typename T>
Polynomial<T> Polynomial<T>::division(const Polynomial<T>& other) {
    size_t newMaxDeg = maxDeg - other.maxDeg;
    size_t newSize = newMaxDeg + 1;

    Polynomial<T> temp(*this);
    Polynomial<T> div(other);

    size_t i = temp.maxDeg-1;
    size_t j = div.maxDeg-1;

    for (int k = 0; k < maxDeg; ++k) {
        this->coeff[k] = 0;
    }
    resize(newSize);
    size_t it = 0;
    while (temp.maxDeg >= div.maxDeg) {
        if (i == 0 || newSize == 0)
            break;

        this->coeff[newSize - 1] = temp.coeff[i] / div.coeff[j];
        Polynomial<T> s(*this);
        for (int t = 0; t < s.maxDeg; t++) {
            s.coeff[t] = 0;
        }
        s.coeff[newSize - 1] = coeff[newSize - 1];
        if (it > 0)
            s.resize(s.maxDeg - it);

        temp -= div * s;

        --newSize;
        --i;
        ++it;
    }
    return temp;
}
// 7 -5 3
// 7 9 -7 6

template<typename T>
Polynomial<T>& Polynomial<T>::operator/=(const Polynomial<T>& other) {
    division(other);
    return *this;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator/(const Polynomial<T>& other) const {
    Polynomial<T> poly(*this);
    poly /= other;

    return poly;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator/=(T dev) {
    for (int i = 0; i < maxDeg; ++i) {
        coeff[i] /= dev;
    }
    return *this;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator/(T dev) const {
    Polynomial<T> poly(*this);
    poly /= dev;

    return poly;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator%=(const Polynomial<T>& other) {
    Polynomial<T> poly = division(other);
    *this = poly;

    return *this;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator%(const Polynomial<T>& other) const {
    Polynomial<T> poly(*this);
    poly %= other;

    return poly;
}

template<typename T>
void Polynomial<T>::print(std::ostream&) const {
    int i = 0;
    for (Polynomial::iterator<T> it = begin(); it < end(); ++it, ++i) {
        std::cout << ((*it) >= 0 ? '+' : ' ') << (*it) << "x^" << i << ' ';
    }
    std::cout << std::endl;
}


#endif //POLYNOMIAL_POLYNOMIAL_H
