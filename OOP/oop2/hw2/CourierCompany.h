//
// Created by yasen on 4/26/19.
//

#ifndef HW2_COURIERCOMPANY_H
#define HW2_COURIERCOMPANY_H


#include <cstdlib>
#include "Item.h"

class CourierCompany {
    size_t size;
    size_t capacity;
    Item** items;

private:
    double allCostForTransport;
    size_t allVolume;
private:
    void clean();
    void resize(size_t newCapacity);
public:
    explicit CourierCompany(size_t newCapacity = 16);
    CourierCompany(const CourierCompany& other) = delete;
    CourierCompany&operator=(const CourierCompany& rhs) = delete;
    ~CourierCompany();

public:
    void addItem(Item* item);
    double getAllCostForTransport() const;
    size_t getAllVolume() const;
    void print() const;
};


#endif //HW2_COURIERCOMPANY_H
