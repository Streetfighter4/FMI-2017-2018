#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "HashTable.h"

const size_t MAXN = 30;

bool isExistInVector(std::vector<std::string> names, char name[]) {
    for(std::string& str : names) {
        if(str == name) {
            return true;
        }
    }
    return false;
}

void eraseRepeatedNames(const std::string& fileName, std::vector<std::string>& names) {
    std::ifstream ifs(fileName);
    char name[MAXN+1];
    if(ifs.is_open()) {
        while(!ifs.eof()) {
            ifs.getline(name, MAXN+1);
            if(strcmp(name, "") && !isExistInVector(names, name)) {
                names.push_back(name);
            }
            memset(name, 0, MAXN);
        }
        ifs.close();
    }
}


void fillFile(HashTable& table, const std::string& fileName) {
    std::vector<std::string> names;
    eraseRepeatedNames(fileName, names);

    table.firstName = names[0];

    for (int i = 1; i < names.size()-1; ++i) {
        table.insert(names[i], names[i-1], names[i+1]);
    }

    table.insert(names[0], names[names.size()-1], names[1]);
    table.insert(names[names.size()-1], names[names.size()-2], names[0]);
}


int main(int argc, char* argv[]) {
    HashTable table;

    fillFile(table, argv[1]);

    std::string command, str1, str2, str3, choice;
    while(true) {
        std::cin >> command;
        if(command == "RELEASE") {
            std::cin >> str1 >> choice;
            std::replace(str1.begin(), str1.end(), '_', ' ');

            table.release(str1, choice);
        } else if(command == "GRAB") {
            std::cin >> str1 >> choice;
            std::replace(str1.begin(), str1.end(), '_', ' ');

            table.grab(str1, choice);
        } else if(command == "INFO") {
            std::cin >> str1;
            std::replace(str1.begin(), str1.end(), '_', ' ');

            table.info(str1);
        } else if(command == "ADD") {
            std::cin >> str1 >> str2 >> str3;

            std::replace(str1.begin(), str1.end(), '_', ' ');
            std::replace(str2.begin(), str2.end(), '_', ' ');
            std::replace(str3.begin(), str3.end(), '_', ' ');

            table.addBetween(str1, str2, str3);
        } else if(command == "REMOVE") {
            std::cin >> str1;
            std::replace(str1.begin(), str1.end(), '_', ' ');

            if(table.remove(str1)) { // end of dance
                break;
            }
        } else if(command == "SWAP") {
            std::cin >> str2 >> str3;

            std::replace(str2.begin(), str2.end(), '_', ' ');
            std::replace(str3.begin(), str3.end(), '_', ' ');
            table.swap(str2, str3);
        } else if(command == "PRINT") {
            table.print();
        } else if(command == "EXIT") {
            break;
        }
    }


    return 0;
}