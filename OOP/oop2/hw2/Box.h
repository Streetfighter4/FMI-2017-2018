//
// Created by yasen on 4/20/19.
//

#ifndef HW2_BOX_H
#define HW2_BOX_H


#include <cstdlib>

class Box {
    size_t width;
    size_t height;
    size_t depth;

public:
    Box();
    Box(size_t newWidth, size_t newHeight, size_t newDepth);
    Box(const Box&) = default;
    Box&operator=(const Box&) = default;
    ~Box() = default;
public:
    inline size_t getVolume() const { return width*height*depth; }
};


#endif //HW2_BOX_H
