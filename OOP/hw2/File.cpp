//
// Created by yasen on 4/3/18.
//

#include "File.h"
#include "Line.h"
#include "Constants.h"
#include <string.h>
#include <fstream>
#include <cstring>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;

File::File() {}

File::File(const char *name, size_t countLines) : cntLines(countLines){
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->lines = new Line*[countLines];
}

File::~File() {
    delete[] name;

    for (int i = 0; i < cntLines; ++i) {
        delete lines[i];
    }
    delete[] lines;
}

bool File::parser() {
    char* fullName = new char[strlen(name) + strlen(extentionTXT) + 1];
    strcpy(fullName, name);
    strcat(fullName, extentionTXT);
    ifstream file (fullName);
    cout << fullName << endl;
    delete[] fullName;
    if(!file.is_open()){
        cout << "Bla bla bla" << endl;
        return false;
    }
    char buffer[lenghtOfLine];
    size_t numLine = 0;
    while(file) {
        file.getline(buffer, lenghtOfLine);

        cout << "numLine: " << numLine << endl;
        cout << "cntLines: " << cntLines << endl;
        if(numLine == cntLines) break;
        if(file.good()) {

            cout << "One line is ready!" << endl;
            Line* line = new (std::nothrow) Line(numLine+1, buffer);
            cout << "After Line constructor" << endl;
            this->lines[numLine] = line;
            numLine++;
        } else {
            cout << "File is not good!" << endl;
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

void File::exit() {
    cout << "In exit()" << endl;
    char* fullName = new char[strlen(name) + strlen(extentionMD) + 1];
    strcpy(fullName, name);
    strcat(fullName, extentionMD);
    cout << "Name of file: " << fullName << endl;
    ofstream file (fullName);
    bool boldScope;
    bool italicScope;
    cout << "In exit() 1" << endl;
    for (size_t i = 0; i < cntLines; ++i) {
        boldScope = italicScope = false;
        if(lines[i]->isHeadingLine()) {
            file << headingSymbol;
        }
        for (size_t j = 0; j < lines[i]->getCntWords(); ++j) {
            if(lines[i]->getWord(j).getIsBold() && !boldScope) {
                file << boldSymbol;
                boldScope = true;
            }
            if(!lines[i]->getWord(j).getIsBold() && boldScope) {
                file << boldSymbol;
                boldScope = false;
            }
            if(lines[i]->getWord(j).getIsItalic() && !italicScope) {
                file << italicSymbol;
                italicScope = true;
            }
            if(!lines[i]->getWord(j).getIsItalic() && italicScope) {
                file << italicSymbol;
                italicScope = false;
            }

            file << lines[i]->getValueWord(j);
        }
        if(boldScope)
            file << boldSymbol;
        if(italicScope)
            file << italicSymbol;

        file << endl;
    }
    file.close();
}

void File::addLine(char *content) {
    Line** newLines = new Line*[cntLines + 1];
    for (int i = 0; i < cntLines; ++i) {
        newLines[i] = lines[i];
    }
    Line* newLine = new Line(cntLines+1, content);
    newLines[cntLines] = newLine;
    cntLines++;
}

void File::removeLine(size_t index) {
    for (size_t i = index; i < cntLines; ++i) {
        lines[i] = lines[i + 1];
    }
    cntLines--;
}

void File::makeChanges() {
    cin.ignore();
    while(true) {
        char request[256];
        cin.getline(request, 256);
        cout << "request: " << request << endl;
        cout << "In makeChanges" << endl;
        char* token;
        char* array[4];
        token = strtok(request, " ");
        cout << "token: " << token << endl;
        int i = 0;
        array[i] = token;
        cout << "array[i]: " << array[i] << endl;
        while (token != NULL) {
            array[i++] = token;
            token = strtok(NULL, " ");
        }
        cout << "array[0]: " << array[0] << endl;
        if(!strcmp(array[0], "makeHeading")) {
            cout << "In makeChanges/makeHeading()" << endl;
            int indexOfLine = atoi(array[1]);
            this->lines[indexOfLine-1]->makeHeading();

        } else if(!strcmp(array[0], "makeItalic")) {
            int indexOfLine = atoi(array[1]);
            size_t from = atoi(array[2]);
            size_t to = atoi(array[3]);
            if(from > to) {
                cout << "Invalid scope. Try again." << endl;
                continue;
            }
            this->lines[indexOfLine]->makeItalic(from, to);

        } else if(!strcmp(array[0], "makeBold")) {
            int indexOfLine = atoi(array[1]);
            size_t from = atoi(array[2]);
            size_t to = atoi(array[3]);
            if(from > to) {
                cout << "Invalid scope. Try again." << endl;
                continue;
            }

            this->lines[indexOfLine]->makeBold(from,to);

        } else if(!strcmp(array[0], "makeCombine")) {
            int indexOfLine = atoi(array[1]);
            size_t from = atoi(array[2]);
            size_t to = atoi(array[3]);
            if(from > to) {
                cout << "Invalid scope. Try again." << endl;
                continue;
            }

            this->lines[indexOfLine]->makeCombine(from,to);

        } else if(!strcmp(array[0], "addLine")) {

            this->addLine(array[1]);

        } else if(!strcmp(array[0], "remove")) {
            cout << "In makeChanges/remove()" << endl;
            size_t indexOfLine = atoi(array[1]);
            this->removeLine(indexOfLine);

        } else if(!strcmp(array[0], "exit")) {
            cout << "In makeChanges/exit()" << endl;
            this->exit();
            return;
        }

    }
}

