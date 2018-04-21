//
// Created by yasen on 4/3/18.
//

#include "File.h"
#include "Constants.h"
#include <cstring>
#include <fstream>
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
    ifstream file (name);
    if(!file.is_open()){
        cout << "Can't open a file" << endl;
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
    size_t i;
    for (i = strlen(name); i > 0; --i) {
        if(name[i] == '.') break;
    }
    name[i] = '\0';
    char* fullName = new char[i + strlen(extentionMD) + 1];
    strcpy(fullName, name);
    strcat(fullName, extentionMD);

    ofstream file (fullName);

    bool boldScope;
    bool italicScope;
    for (i = 0; i < cntLines; ++i) {
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
        if(italicScope) {
            file << italicSymbol;
        }

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
    while(true) {
        char command[20];
        cin >> command;
        if(!strcmp(command, "makeHeading")) {
            int indexOfLine;
            cin >> indexOfLine;

            if(!validInput(indexOfLine)) {
                continue;
            }
            this->lines[indexOfLine-1]->makeHeading();

        } else if(!strcmp(command, "makeItalic")) {
            int indexOfLine, from, to;
            cin >> indexOfLine >> from >> to;

            if(!validInput(indexOfLine, from, to)) {
                continue;
            }

            this->lines[indexOfLine-1]->makeItalic((size_t)from-1, (size_t)to-1);

        } else if(!strcmp(command, "makeBold")) {
            int indexOfLine, from, to;
            cin >> indexOfLine >> from >> to;

            if(!validInput(indexOfLine, from, to)) {
                continue;
            }

            this->lines[indexOfLine-1]->makeBold((size_t)from-1, (size_t)to-1);

        } else if(!strcmp(command, "makeCombine")) {
            int indexOfLine, from, to;
            cin >> indexOfLine >> from >> to;

            if(!validInput(indexOfLine, from, to)) {
                continue;
            }

            this->lines[indexOfLine-1]->makeCombine((size_t)from-1, (size_t)to-1);

        } else if(!strcmp(command, "addLine")) {
            char content[lenghtOfLine];
            cin.getline(content, lenghtOfLine);
            this->addLine(content);

        } else if(!strcmp(command, "remove")) {
            int indexOfLine;
            cin >> indexOfLine;
            if(!validInput(indexOfLine)) {
                continue;
            }
            this->removeLine((size_t)indexOfLine-1);

        } else if(!strcmp(command, "exit")) {
            this->exit();
            return;
        } else {
            cout << "Invalid command. Try again!" << endl;
        }

    }
}

bool File::validInput(int indexOfLine, int from, int to) {
    if(indexOfLine > cntLines || indexOfLine < 1) {
        cout << "Invalid line. Try again" << endl;
        return false;
    }
    size_t wordsOnLine = lines[indexOfLine-1]->getCntWords();
    if(from > to || from < 1 || to < 1 || (from > wordsOnLine) || (to > wordsOnLine)) {
        cout << "Invalid scope of words. Try again." << endl;
        return false;
    }
    return true;
}

