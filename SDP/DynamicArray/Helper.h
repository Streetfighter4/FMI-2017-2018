//
// Created by yasen on 10/12/18.
//

#ifndef DYNAMICARRAY_HELPER_H
#define DYNAMICARRAY_HELPER_H


#include <cstdlib>
#include <algorithm>


namespace Helper {

    template <typename T>
    void insertionSort(T& array, size_t size) {
        for (int i = 0; i < size-1; ++i) {
            for (int j = i+1; j < size; ++j) {
                if(array[i] > array[j]) {
                    std::swap(array[i], array[j]);
                }
            }
        }
    }

    template <typename T>
    int liniar_search(const T* data, size_t size, const T& elem) {
        for (int i = 0; i < size; ++i) {
            if(data[i] == elem) {
                return i;
            }
        }
        return -1;
    }

    template <typename T>
    int binary_search(const T* data, size_t size, const T& elem) {
        size_t l = 0;
        size_t r = size-1;
        while(l <= r) {
            int m = l + (r-1) / 2;

            if(data[m] == elem) {
                return m;
            }
            if(data[m] < elem) {
                l = m+1;
            }
            else {
                r = m-1;
            }
        }
        return -1;
    }
}
#endif //DYNAMICARRAY_HELPER_H
