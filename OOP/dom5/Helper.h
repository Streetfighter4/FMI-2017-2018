//
// Created by yasen on 7/23/18.
//

#include "Message.h"
#include "Hashtag.h"
#include "Date.h"
#include "Simple.h"
#include <ctime>
#include <cstring>
#include <cctype>

namespace Helper {

    inline Word* createWord(const char *content) {
        struct tm tm;
        if (content[0] == '#') {
            return new Hashtag(content);
        } else if (strptime(content, "%d-%m-%Y", &tm)) {
            return new Date(content);
        } else {
            return new Simple(content);
        }
    }

    inline char* ToLower(char *str) {
        size_t lenght = strlen(str);
        char *contentToLower = new char[lenght + 1];
        for (int i = 0; i < lenght; ++i) {
            contentToLower[i] = static_cast<char>(tolower(str[i]));
        }
        contentToLower[lenght] = '\0';
        return contentToLower;
    }

    struct date_struct {
        int day,
                month,
                year;
    };

    inline void convertDateToIntegers(char *str, date_struct &date) {
        char day[3];
        char month[3];
        char year[5];

        day[0] = str[0];
        day[1] = str[1];
        day[2] = '\0';

        month[0] = str[3];
        month[1] = str[4];
        month[2] = '\0';


        year[0] = str[6];
        year[1] = str[7];
        year[2] = str[8];
        year[3] = str[9];
        year[4] = '\0';

        date.day = atoi(day);
        date.month = atoi(month);
        date.year = atoi(year);
    }

    inline unsigned long returnJulianDays(date_struct &date) {
        return (1461 * (date.year + 4800 + (date.month - 14) / 12)) / 4 +
               (367 * (date.month - 2 - 12 * ((date.month - 14) / 12))) / 12 -
               (3 * ((date.year + 4900 + (date.month - 14) / 12) / 100)) / 4 +
               date.day - 32075;
    }

    inline unsigned daysBetweenDates(char *str1, char *str2) {
        date_struct date1{}, date2{};
        convertDateToIntegers(str1, date1);
        convertDateToIntegers(str2, date2);

        unsigned long days1 = returnJulianDays(date1);
        unsigned long days2 = returnJulianDays(date2);

        return abs(days1 - days2);
    }

};
