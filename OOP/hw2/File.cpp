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
    delete[] fullName;
    if(!file.is_open()){
        cout << "Bla bla bla" << endl;
        return false;
    }
    char buffer[lenghtOfLine];
    size_t numLine = 0;
    while(file) {
        file.getline(buffer, lenghtOfLine);

        if(numLine == cntLines) break;
        if(file.good()) {
            Line* line = new (std::nothrow) Line(numLine+1, buffer);
            this->lines[numLine] = line;
            numLine++;
        } else {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

void File::exit() {
    char* fullName = new char[strlen(name) + strlen(extentionMD) + 1];
    strcpy(fullName, name);
    strcat(fullName, extentionMD);
    ofstream file (fullName);
    bool boldScope;
    bool italicScope;
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
            if(hasSpace(i, j)) {
                file << ' ';
            }

        }
        if(boldScope){
            file << boldSymbol;
        }
        if(italicScope)
            file << italicSymbol;

        file << endl;
    }
    file.close();
}

bool File::hasSpace(size_t i, size_t j) const {
    const Word &curr = lines[i]->getWord(j);
    const Word &next = lines[i]->getWord(j + 1);
    return (!curr.getIsBold() || next.getIsBold()) && (!curr.getIsItalic() || next.getIsItalic());
}

void File::addLine(char* content) {
    cout << "In addLine. content: " << content << endl;
    Line** newLines = new Line*[cntLines + 1];
    for (int i = 0; i < cntLines; ++i) {
        newLines[i] = lines[i];
    }
    Line* newLine = new Line(cntLines+1, content);
    newLines[cntLines] = newLine;
    delete[] lines;
    lines = newLines;
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
        char command[20];
        cin >> command;
        cout << command << endl;
        if(!strcmp(command, "makeHeading")) {
            cout << "In makeChanges/makeHeading()" << endl;
            int indexOfLine;
            cin >> indexOfLine;
            this->lines[indexOfLine-1]->makeHeading();

        } else if(!strcmp(command, "makeItalic")) {
            int indexOfLine;
            size_t from, to;
            cin >> indexOfLine >> from >> to;

            if(from > to) {
                cout << "Invalid scope. Try again." << endl;
                continue;
            }
            this->lines[indexOfLine-1]->makeItalic(from-1, to-1);

        } else if(!strcmp(command, "makeBold")) {
            int indexOfLine;
            size_t from, to;
            cin >> indexOfLine >> from >> to;

            if(from > to) {
                cout << "Invalid scope. Try again." << endl;
                continue;
            }

            this->lines[indexOfLine-1]->makeBold(from-1, to-1);

        } else if(!strcmp(command, "makeCombine")) {
            int indexOfLine;
            size_t from, to;
            cin >> indexOfLine >> from >> to;

            if(from > to) {
                cout << "Invalid scope. Try again." << endl;
                continue;
            }

            this->lines[indexOfLine-1]->makeCombine(from-1, to-1);

        } else if(!strcmp(command, "addLine")) {
            char content[lenghtOfLine];
            cin.getline(content, lenghtOfLine);
            cout << content << endl;
            this->addLine(content);

        } else if(!strcmp(command, "remove")) {
            cout << "In makeChanges/remove()" << endl;
            size_t indexOfLine;
            cin >> indexOfLine;
            this->removeLine(indexOfLine-1);

        } else if(!strcmp(command, "exit")) {
            cout << "In makeChanges/exit()" << endl;
            this->exit();
            return;
        }

    }
}

