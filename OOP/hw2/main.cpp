#include <iostream>
#include <fstream>
#include <string.h>
#include "File.h"
#include "Constants.h"

using std::cout;
using std::endl;
using std::ifstream;

int main() {
    char* fileName = new char[128];
    std::cin >> fileName;

    char* fullPathFile = new char[strlen(fileName) + strlen(extentionTXT) + 1];
    strcpy(fullPathFile, fileName);
    strcat(fullPathFile, extentionTXT);

    size_t numberOfLines = 0;
    char line[lenghtOfLine];
    ifstream iFile (fullPathFile);
    delete fullPathFile;

    while(!iFile.eof()) {
        iFile.getline(line, lenghtOfLine);
        numberOfLines++;
    }

    iFile.close();

    File* file = new File(fileName, numberOfLines-1);
    if(!file->parser()) {
        cout << "Can not parse the file!" << endl;
        return -1;
    }
    delete fileName;

    file->makeChanges();

    return 0;
}