//
// Created by yasen on 3/28/19.
//

#include "MusicCompany.h"

MusicCompany::MusicCompany(Director *newDirector, MusicStudio *newMusicStudio, double newReadlPriceForStudio)
            : director(newDirector), musicStudio(newMusicStudio), realPriceForStudio(newReadlPriceForStudio) {
    incomeForDay = 0;
}

void MusicCompany::rendStudio(size_t perHour) {
    if(musicStudio->rent(perHour)) {
        incomeForDay += realPriceForStudio*perHour;
    }
}

void MusicCompany::setNewRentPrice(double newRentPrice) {
    if(newRentPrice < musicStudio->getMinimimPricePerHour()) {
        std::cout << "Studio has minimum price per hour. Do not undercutting the price" << std::endl;
        return;
    }
    realPriceForStudio = newRentPrice;
    std::cout << "New price per hour is: " << realPriceForStudio << std::endl;
}

double MusicCompany::getIncomeForDay() const {
    return incomeForDay;
}

double MusicCompany::getIncomeForDayInDollars() const {
    return incomeForDay*0.57;
}

double MusicCompany::getIncomeForDayInEuro() const {
    return incomeForDay*0.51;
}

bool MusicCompany::lessThen(const MusicCompany& other) const {
    return realPriceForStudio < other.realPriceForStudio;
}

bool MusicCompany::haveYoungerDirector(const MusicCompany &other) const {
    return director->getAge() < other.director->getAge();
}

void MusicCompany::reductionWithPercentages(double percentages) {
    double reduction = realPriceForStudio * (percentages/100.0);
    std::cout << "Reduction: " << reduction << std::endl;
    if(realPriceForStudio - reduction < musicStudio->getMinimimPricePerHour()) {
        std::cout << "Percentages is to high for reduction!" << std::endl;
        return;
    }
    realPriceForStudio -= reduction;
    std::cout << "New price per hour is: " << realPriceForStudio << std::endl;
}
