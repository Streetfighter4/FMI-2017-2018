#include <iostream>
#include "MusicCompany.h"

void testRentMusicStudio(MusicCompany& musicCompany) {
    musicCompany.rendStudio(4);
    musicCompany.rendStudio(3);
    musicCompany.rendStudio(2);

    std::cout << "===========================" << std::endl;
}

void testSetNewRentPrice(MusicCompany& musicCompany) {
    musicCompany.setNewRentPrice(120.0);
    musicCompany.setNewRentPrice(80.0);

    std::cout << "===========================" << std::endl;
}

void testIncomeForDay(const MusicCompany& musicCompany) {

    std::cout << "Income for day is: " << musicCompany.getIncomeForDay() << " in FMI coins " << std::endl;
    std::cout << "Income for day is: " << musicCompany.getIncomeForDayInEuro() << " in euros " << std::endl;
    std::cout << "Income for day is: " << musicCompany.getIncomeForDayInDollars() << " in dollars " << std::endl;

    std::cout << "===========================" << std::endl;
}

void testComparisonCompanyPerRent(const MusicCompany& m1, const MusicCompany& m2, const MusicCompany& m3) {
    if(m1.lessThen(m2)) { // 150.0 < 120.0 ?
        std::cout << "Choose music company 1" << std::endl;
    } else {
        std::cout << "Choose music company 2" << std::endl;
    }

    if(m1.lessThen(m3)) { // 150.0 < 200.0 ?
        std::cout << "Choose music company 1" << std::endl;
    } else {
        std::cout << "Choose music company 3" << std::endl;
    }

    std::cout << "===========================" << std::endl;
}

void testReductionWithPercentages(MusicCompany& musicCompany) {
    musicCompany.reductionWithPercentages(10.0);
    musicCompany.reductionWithPercentages(10.0);

    std::cout << "===========================" << std::endl;
}

void testComparisonCompanyByDirector(const MusicCompany& m1, const MusicCompany& m2, const MusicCompany& m3) {
    if(m1.haveYoungerDirector(m2)) { // 20 < 8 ?
        std::cout << m1.getDirector()->getName() << " is younger than " << m2.getDirector()->getName() << std::endl;
    } else {
        std::cout << m2.getDirector()->getName() << " is younger than " << m1.getDirector()->getName() << std::endl;
    }

    if(m1.haveYoungerDirector(m3)) { // 20 < 80 ?
        std::cout << m1.getDirector()->getName() << " is younger than " << m3.getDirector()->getName() << std::endl;
    } else {
        std::cout << m3.getDirector()->getName() << " is younger than " << m1.getDirector()->getName() << std::endl;
    }

    std::cout << "===========================" << std::endl;
}

int main() {
    Director yasen("Yasen Alexiev", 20);
    Director ali("Aleksanda Stoqnova", 18);
    Director toni("Antonio Mindov", 80);

    MusicStudio musicStudio(100.0, 8);

    MusicCompany musicCompany1("Stars", &yasen, &musicStudio, 150.0);
    MusicCompany musicCompany2("Talents", &ali, &musicStudio, 120.0);
    MusicCompany musicCompany3("Whales", &toni, &musicStudio, 200.0);

    testRentMusicStudio(musicCompany1);

    testComparisonCompanyPerRent(musicCompany1, musicCompany2, musicCompany3);

    testSetNewRentPrice(musicCompany1);
    testIncomeForDay(musicCompany1);

    testReductionWithPercentages(musicCompany1);

    testComparisonCompanyByDirector(musicCompany1, musicCompany2, musicCompany3);
    return 0;
}