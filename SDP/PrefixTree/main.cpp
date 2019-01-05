#include <iostream>
#include <fstream>
#include <cstring>

#include "Graph.hpp"

int main() {
    Graph prefixTree1, prefixTree2;

    std::ifstream ifs("strings.txt");
    if(!ifs.is_open()) {
        return -1;
    }
    char str[30];

    while (!ifs.eof()) {
        ifs >> str;
        prefixTree1.add_word(str);
        memset(str, 0, 30);
    }
    ifs.close();


    prefixTree1.print();
    std::cout << "Minimized prefix tree...." << std::endl;
    clock_t start = clock();
    prefixTree1.minimized();
    clock_t stop = clock();
    prefixTree1.print();
    std::cout << "time: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;


    return 0;
}