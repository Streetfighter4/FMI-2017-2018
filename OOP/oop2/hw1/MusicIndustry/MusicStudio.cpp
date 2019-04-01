//
// Created by yasen on 3/28/19.
//

#include "MusicStudio.h"

MusicStudio::MusicStudio(double newMinimumPricePerHour, double newCapacityPerDay) :
                            minimumPricePerHour(newMinimumPricePerHour), capacityPerDay(newCapacityPerDay) {
    rentedHours = 0;
}

bool MusicStudio::rent(double hours) {
    if(capacityPerDay - rentedHours > hours) {
        rentedHours += hours;
        std::cout << "Successful rented studio per " << hours << std::endl;
        return true;
    } else {
        std::cout << "Studio has limit hours per day. Check tomorrow :)" << std::endl;
        return false;
    }
}

double MusicStudio::getMinimimPricePerHour() const {
    return minimumPricePerHour;
}

