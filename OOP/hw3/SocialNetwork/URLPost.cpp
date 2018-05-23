//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <iostream>
#include "URLPost.h"

URLPost::URLPost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, 0, id, authorId) { }

Post *URLPost::clone() {
    return new URLPost(*this);
}

void URLPost::parseToHTML(std::ofstream& ofile) {
    if(ofile.is_open()) {
        std::cout << "In parseToHTML in URLPost!" << std::endl;
        const char* str1 = "<!DOCTYPE html>\n<html>\n<body>\n\n<a href=\"";
        const char* str2 = "</a>\n\n</body>\n</html>";
        ofile.write(str1, strlen(str1));
        ofile.write(getContent(), strlen(getContent()));
        ofile.write("\">", 2);
        ofile.write(getContent(), strlen(getContent()));
        ofile.write(str2, strlen(str2));

        ofile.close();
    }

}
