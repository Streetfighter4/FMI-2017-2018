//
// Created by yasen on 3/21/18.
//

#include "Clock.h"

Clock::Clock() {}
Clock::Clock(unsigned short hour, unsigned short minute, unsigned short second) {
    this.hour = hour;
    this.minute = minute;
    this.second = second;
}
unsigned short Clock::getHour() const {
    return hour;
}
unsigned short Clock::getMinute() const {
    return minute;
}
unsigned short Clock::getSecond() const {
    return second;
}

void Clock::setHour(unsigned short hour) {
    this->hour = hour;
}

void Clock::setMinute(unsigned short minute) {
    this->minute = minute;
}

void Clock::setSecond(unsigned short second) {
    this->second = second;
}

void Clock::print() {
    if(this->hour < 10) {
        if(this->minute < 10) {
            if(this->second < 10) {
                cout << '0' << this->hour << ":0" << this->minute << ":0" << this->second << endl;
            } else {
                cout << '0' << this->hour << ":0" << this->minute << ":" << this->second << endl;
            }
        } else {
            if(this->second < 10) {
                cout << '0' << this->hour << ":" << this->minute << ":0" << this->second << endl;
            } else {
                cout << '0' << this->hour << ":" << this->minute << ":" << this->second << endl;
            }
        }
    } else {
        if(this->minute < 10) {
            if(this->second < 10) {
                cout << this->hour << ":0" << this->minute << ":0" << this->second << endl;
            } else {
                cout << this->hour << ":0" << this->minute << ":" << this->second << endl;
            }
        } else {
            if (this->second < 10) {
                cout << this->hour << ":" << this->minute << ":0" << this->second << endl;
            } else {
                cout << this->hour << ":" << this->minute << ":" << this->second << endl;
            }
        }
    }
}

