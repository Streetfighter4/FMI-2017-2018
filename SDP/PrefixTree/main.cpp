#include <ctime>
#include <cstring>
#include <fstream>
#include "Graph.hpp"

int main() {
    Graph prefixTree;

    std::wifstream ifs("strings.txt");
    if(!ifs.is_open()) {
        return -1;
    }

    wchar_t str[64];
    int countWords = 0;

    clock_t start = clock();


    while (!ifs.eof()) {
        ifs >> str;
        prefixTree.add_word(str);
        memset(str, 0, 64);
        ++countWords;
    }
    ifs.close();

    clock_t stop = clock();
    std::cout << "count words: " << countWords << std::endl;
    std::cout << "time to construct prefix tree: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;


    prefixTree.print();
    std::cout << std::endl;
    start = clock();
    prefixTree.minimized();
    stop = clock();

    std::cout << "time to minimize prefix tree: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;
    prefixTree.print();
    std::cout << std::endl << std::endl;



    wchar_t prefix[64];
    while (true) {
        std::wcin >> prefix;
        if(wcscmp(prefix, L"zzz") == 0) {
            break;
        }
        start = clock();
        prefixTree.findEveryPhraseWithPrefix(prefix);
        stop = clock();
        std::cout << "time: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;
    }


    return 0;
}
