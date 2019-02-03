#include <ctime>
#include <fstream>
#include <cstring>
#include "Graph.hpp"


void fillDictionary(Graph& prefixTree, const char* filename);

void minimizedPrefixTree(Graph& prefixTree);

void search(Graph& prefixTree);

int main() {
    Graph prefixTree;

    fillDictionary(prefixTree, "suggest.txt");

    minimizedPrefixTree(prefixTree);

    search(prefixTree);

    return 0;
}

const size_t MAX_N = 2 << 6;

void fillDictionary(Graph& prefixTree, const char* filename) {
    std::wifstream ifs(filename);
    if(!ifs.is_open()) {
        return;
    }

    wchar_t str[MAX_N];
    int countWords = 0;

    clock_t start = clock();


    while (!ifs.eof()) {
        ifs >> str;
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

    std::wstring prefix;
    clock_t start, stop;
    size_t newK;
    wchar_t phrase[MAX_N];

    while (true) {
        std::wcin >> prefix;
        std::wcout << "prefix: " << prefix << std::endl;
        if (prefix == COMMAND_SET_K) {
            std::wcin >> newK;
            prefixTree.setK(newK);
            continue;
        } else if(prefix == COMMAND_ADD_PHRASE) {
            std::wcin.ignore();
            std::wcin.getline(phrase, MAX_N);
            std::wcout << L"New phrase: " << phrase << std::endl;
            prefixTree.add_word(phrase);
            std::cout << "New phrase has been added" << std::endl;
            continue;
        } else if(prefix == COMMAND_EXIT) {
            break;
        }
        start = clock();
        prefixTree.findEveryPhraseWithPrefix(prefix.c_str());
        stop = clock();
        std::cout << "Time for search: " << (stop-start)/double(CLOCKS_PER_SEC) << " seconds"<< std::endl;
    }
}
