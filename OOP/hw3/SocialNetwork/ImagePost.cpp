//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <iostream>
#include "ImagePost.h"

ImagePost::ImagePost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, id, authorId) { }

Post* ImagePost::clone() {
    return new ImagePost(*this);
}

void ImagePost::parseToHTML(std::ofstream& ofile) {
    std::cout << "In parseToHTML in ImagePost!" << std::endl;

    const char* str1 = "<img src=\"";
    const char* str2 = "\">\n";
    ofile << str1;
    ofile << getContent();
    ofile << str2;
}
