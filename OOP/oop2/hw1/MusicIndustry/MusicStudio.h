//
// Created by yasen on 3/28/19.
//

#ifndef MUSICINDUSTRY_MUSICSTUDIO_H
#define MUSICINDUSTRY_MUSICSTUDIO_H


#include <stdlib.h>
#include <iostream>

class MusicStudio {
    double minimumPricePerHour;
    double capacityPerDay;
    double rentedHours;
public:
    MusicStudio(double newMinimumPricePerHour, double newCapacityPerDay);

public:
    bool rent(double hours);
    double getMinimimPricePerHour() const;
};


#endif //MUSICINDUSTRY_MUSICSTUDIO_H
