#include <iostream>
#include <fstream>
#include <string.h>
#include "File.h"

using std::cout;
using std::endl;
using std::ifstream;
const char* extention = ".txt";

int main() {
    char* fileName = new char[128];
    std::cin >> fileName;
    cout << fileName << endl;
    char* fullPathFile = new char[strlen(fileName) + strlen(extention) + 1];
    strcpy(fullPathFile, fileName);
    strcat(fullPathFile, extention);
    std::cout << fullPathFile << std::endl;
    size_t numberOfLines = 0;
    char line[1024];
    ifstream iFile (fullPathFile);
    while(!iFile.eof()) {
        iFile.getline(line, 1024);
        numberOfLines++;
    }
    iFile.close();

    File* file = new File(fileName, numberOfLines-1);
    if(!file->parser()) {
        cout << "Can not parse the file!" << endl;
        return -1;
    }
    cout << "After parse" << endl;
    file->makeChanges();

    delete fileName;
    delete fullPathFile;
    return 0;
}