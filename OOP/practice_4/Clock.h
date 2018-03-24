//
// Created by yasen on 3/21/18.
//

#ifndef PRACTICE_4_CLOCK_H
#define PRACTICE_4_CLOCK_H

class Clock{
private:
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
public:
    Clock();
    Clock(unsigned short hour, unsigned short minute, unsigned short second);

    unsigned short getHour() const;
    unsigned short getMinute() const;
    unsigned short getSecond() const;

    void setHour(unsigned short);
    void setMinute(unsigned short);
    void setSecond(unsigned short);

    void print();

};
#endif //PRACTICE_4_CLOCK_H


