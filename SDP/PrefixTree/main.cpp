#include <ctime>
#include <cstring>
#include <fstream>
#include "Graph.hpp"


void fillDictionary(Graph& prefixTree, const char* filename);

void minimizedPrefixTree(Graph& prefixTree);

void search(Graph& prefixTree);

int main() {
    Graph prefixTree;

    fillDictionary(prefixTree, "strings.txt");

    minimizedPrefixTree(prefixTree);

    search(prefixTree);

    return 0;
}

void fillDictionary(Graph& prefixTree, const char* filename) {
    std::wifstream ifs(filename);
    if(!ifs.is_open()) {
        return;
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

    std::cout << "Count words: " << countWords << std::endl;
    std::cout << "Time to construct prefix tree: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;

    prefixTree.print();
    std::cout << std::endl;

}


void minimizedPrefixTree(Graph& prefixTree) {

    clock_t start = clock();
    prefixTree.minimized();
    clock_t stop = clock();

    std::cout << "Time to minimize prefix tree: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;
    prefixTree.print();
    std::cout << std::endl << std::endl;

}


const wchar_t* COMMAND_SET_K = L"SET_K";
const wchar_t* COMMAND_ADD_PHRASE = L"ADD_PHRASE";
const wchar_t* COMMAND_EXIT = L"EXIT_T";

void search(Graph& prefixTree) {

    wchar_t prefix[64];
    clock_t start, stop;
    size_t newK;
    while (true) {
        std::wcin >> prefix;
        if (wcscmp(prefix, COMMAND_SET_K) == 0) {
            std::cin >> newK;
            //TODO: set new K
            continue;
        } else if(wcscmp(prefix, COMMAND_ADD_PHRASE) == 0) {
            //TODO: get new phrase
            continue;
        } else if(wcscmp(prefix, COMMAND_EXIT) == 0) {
            break;
        }
        start = clock();
        prefixTree.findEveryPhraseWithPrefix(prefix);
        stop = clock();
        std::cout << "Time for search: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;
    }



}
