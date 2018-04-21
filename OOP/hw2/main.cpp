#include <iostream>
#include <fstream>
#include <string.h>
#include "File.h"
#include "Constants.h"

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, const char* argv[]) {
    size_t numberOfLines = 0;
    char line[lenghtOfLine];
    ifstream iFile (argv[1]);

    while(!iFile.eof()) {
        iFile.getline(line, lenghtOfLine);
        numberOfLines++;
    }

    iFile.close();

    File* file = new File(argv[1], numberOfLines-1);
    if(!file->parser()) {
        cout << "Can not parse the file!" << endl;
        return -1;
    }

    file->makeChanges();

    return 0;
}