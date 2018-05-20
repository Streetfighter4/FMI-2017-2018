//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include "ImagePost.h"

ImagePost::ImagePost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, 1, id, authorId) { }

Post* ImagePost::clone() {
    return new ImagePost(*this);
}

void ImagePost::parseToHTML(std::ofstream& ofile) {
    if(ofile.is_open()) {

        const char* str1 = "<!DOCTYPE html>\n<html>\n<body>\n\n<img src=";
        const char* str2 = ">\n\n</body>\n</html>";
        ofile.write(str1, strlen(str1));
        ofile.write(getContent(), strlen(getContent()));
        ofile.write(str2, strlen(str2));

        ofile.close();
    }
}
