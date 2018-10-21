//
// Created by yasen on 10/20/18.
//

#ifndef HW1_HELPER_H
#define HW1_HELPER_H

#include <cstdlib>
#include <algorithm>
#include <cstring>


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

    bool isCompatible(const char* uni1, const char* uni2) {
        if(strcmp(uni1, uni2) == 0) {
            return true;
        }
        if(strcmp(uni2, "fmi") == 0) {
            return strcmp(uni1, "tu") == 0;
        }
        if(strcmp(uni2, "tu") == 0) {
            return strcmp(uni1, "unss") == 0;
        }
        if(strcmp(uni2, "unss") == 0) {
            return strcmp(uni1, "fmi") == 0;
        }
    }

}


#endif //HW1_HELPER_H
