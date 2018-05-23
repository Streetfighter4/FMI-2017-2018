//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <iostream>
#include "TextPost.h"

TextPost::TextPost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, -1, id, authorId) { }

Post* TextPost::clone() {
    return new TextPost(*this);
}

void TextPost::parseToHTML(std::ofstream& ofile) {
    if(ofile.is_open()) {

        std::cout << "In parseToHTML in TextPost!" << std::endl;
        const char* str1 = "<!DOCTYPE html>\n<html>\n<body>\n\n<p>";
        const char* str2 = "</p>\n\n</body>\n</html>";

        ofile.write(str1, strlen(str1));
        ofile.write(getContent(), strlen(getContent()));
        ofile.write(str2, strlen(str2));

        ofile.close();
    }

}

