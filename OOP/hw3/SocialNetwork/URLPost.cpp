//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <iostream>
#include "URLPost.h"

URLPost::URLPost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, id, authorId) { }

Post *URLPost::clone() {
    return new URLPost(*this);
}

void URLPost::parseToHTML(std::ofstream& ofile) {
    const char* str1 = "<a href=\"";
    const char* str2 = "</a>\n";

    size_t lenght = strlen(getContent());
    char* str = new char[lenght+1];
    strcpy(str, getContent());

    size_t i;
    for (i = 1; i < lenght; ++i) {
        if(str[i] == ' ')
            break;
    }
    char* str3 = new char[i];
    strncpy(str3, str, i);
    str3[i] = '\0';

    char* str4 = new char[lenght-i];
    for (size_t j = i; j < lenght; ++j) {
        str4[j-i] = str[j];
    }
    str4[lenght-i] = '\0';

    ofile << str1;
    ofile << str3;
    ofile << "\">";
    ofile << str4;
    ofile << str2;

    delete[] str;
    delete[] str3;
    delete[] str4;
}
