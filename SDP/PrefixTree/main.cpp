#include <ctime>
#include <fstream>
#include <cstring>
#include "Graph.hpp"


void fillDictionary(Graph& prefixTree, const char* filename);

void minimizedPrefixTree(Graph& prefixTree);

void search(Graph& prefixTree);

int main() {
    Graph prefixTree;

    std::cout << "Enter file name: " << std::endl;

    std::string filename;
    std::cin >> filename;
    fillDictionary(prefixTree, filename.c_str());

    minimizedPrefixTree(prefixTree);

    search(prefixTree);

    return 0;
}


void fillDictionary(Graph& prefixTree, const char* filename) {
    std::wifstream ifs(filename);
    if(!ifs.is_open()) {
        return;
    }

    wchar_t str[MAX_N];
    int countWords = 0;

    clock_t start = clock();


    while (!ifs.eof()) {
        ifs.getline(str, MAX_N);
        prefixTree.add_word(str);
        memset(str, 0, MAX_N);
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
    if(prefixTree.size() >= 80000) {
        return;
    }
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
    std::cout << "Ready for searching...." << std::endl << std::endl;
    std::wstring prefix;
    clock_t start, stop;
    size_t newK;
    wchar_t phrase[MAX_N];

    while (true) {
        std::wcin >> prefix;
        if (prefix == COMMAND_SET_K) {
            std::wcin.ignore();
            std::wcin >> newK;
            prefixTree.setK(newK);
            continue;
        } else if(prefix == COMMAND_ADD_PHRASE) {
            std::wcin.ignore();
            std::wcin.getline(phrase, MAX_N);
            prefixTree.add_word(phrase);
            continue;
        } else if(prefix == COMMAND_EXIT) {
            break;
        }
        start = clock();
        prefixTree.findEveryPhraseWithPrefix(prefix.c_str());
        stop = clock();
        std::cout << "\nTime for search: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;
    }
}
