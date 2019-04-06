//
// Created by yasen on 3/28/19.
//
#ifndef MUSICINDUSTRY_MUSICCOMPANY_H
#define MUSICINDUSTRY_MUSICCOMPANY_H


#include "Director.h"
#include "MusicStudio.h"

class MusicCompany {
private:
    char* name;
    Director* director;
    MusicStudio* musicStudio;
    double realPriceForStudio;
    double incomeForDay;

public:
    MusicCompany(const char* newName, Director* newDirector, MusicStudio* newMusicStudio, double newRealPriceForStudio);
    MusicCompany(const MusicCompany&) = delete;
    MusicCompany&operator=(const MusicCompany&) = delete;
    ~MusicCompany();
public:
    void rendStudio(size_t perHour);
    void setNewRentPrice(double newRentPrice);
    void reductionWithPercentages(double percentages);

    inline const Director* getDirector() const { return director; }

    double getIncomeForDay() const;
    double getIncomeForDayInDollars() const;
    double getIncomeForDayInEuro() const;
    bool lessThen(const MusicCompany& other) const;
    bool haveYoungerDirector(const MusicCompany& other) const;
};


#endif //MUSICINDUSTRY_MUSICCOMPANY_H
