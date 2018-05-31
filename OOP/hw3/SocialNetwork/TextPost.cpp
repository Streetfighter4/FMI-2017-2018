//
// Created by yasen on 5/17/18.
//

#include <iostream>
#include "TextPost.h"

TextPost::TextPost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, id, authorId) { }

Post* TextPost::clone() {
    return new TextPost(*this);
}

void TextPost::parseToHTML(std::ofstream& ofile) {
    const char* str1 = "<p>";
    const char* str2 = "</p>\n";

    ofile << str1;
    ofile << getContent();
    ofile << str2;
}

