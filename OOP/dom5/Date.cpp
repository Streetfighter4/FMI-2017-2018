//
// Created by yasen on 7/23/18.
//

#include <time.h>
#include "Date.h"
#include "Helper.h"

Date::Date(const char* content) : Word(content) { }

unsigned short int Date::similarity(char* searchedWord) {
    struct tm tm;
    if(strptime(searchedWord, "%d-%m-%Y", &tm)) {
        unsigned days = Helper::daysBetweenDates(getContent(), searchedWord);
        if(days >= 100) {
            return 0;
        } else {
            return 100 - days;
        }
    } else {
        return 0;
    }

}

Word* Date::clone() {
    return new Date(*this);
}
