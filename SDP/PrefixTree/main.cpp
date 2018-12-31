#include <iostream>
#include <fstream>
#include <cstring>

#include "Graph.hpp"

int main() {
    Graph prefixTree;

    std::ifstream ifs("strings.txt");
    if(!ifs.is_open()) {
        return -1;
    }
    char str[30];
    while (!ifs.eof()) {
        ifs >> str;
        prefixTree.add_word(str);
        memset(str, 0, 30);
    }
    ifs.close();


    prefixTree.print();
    std::cout << "Minimized prefix tree...." << std::endl;
    clock_t start = clock();
    prefixTree.minimized();
    clock_t stop = clock();
    std::cout << "time: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << " milliseconds"<< std::endl;

    prefixTree.print();
    return 0;
}