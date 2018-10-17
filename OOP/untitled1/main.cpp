#include <iostream>
#include <cstring>

using std::cin;
using std::cout;

void clean(char**&, size_t);

int readAndInitDictionary(char**& str, const size_t n) {
    str = new(std::nothrow)char*[n];
    if (!str) {
        cout << "Not enough memory!" << std::endl;
        return -1;
    }
    char* word;
    for (size_t i = 0; i < n; i++) {
        cin >> word;
        str[i] = new(std::nothrow)char[strlen(word)+1];
        if (!str[i]) {
            cout << "Not enough memory!" << std::endl;
            clean(str, i-1);
        }
        strcpy(str[i], word);
        str[i][strlen(word)] = '\0';
    }
}

void clean(char**& str, size_t n) {
    for (size_t i = 0; i < n; i++) {
        delete str[i];
    }
    delete[] str;
    str = NULL;
}

void initSentence(char*& sentence, char**& words) {
    size_t countWords = 0;
    std::cout << "sentence is: " << sentence << std::endl;

    bool inSpaces = true;

    while (*sentence != NULL)
    {
        if (std::isspace(*sentence)) {
            inSpaces = true;
        }
        else if (inSpaces)
        {
            countWords++;
            inSpaces = false;
        }

        ++sentence;
    }
    std::cout << "countWords is: " << countWords << std::endl;
}

int main() {
/*
	char** Dictionary = nullptr;
	size_t numberOfWordsInDictionary;
	cin >> numberOfWordsInDictionary;

	readAndInitDictionary(Dictionary, numberOfWordsInDictionary);
*/	char** words = nullptr;
    char* sentence = nullptr;
    cin.getline(sentence, 80);
    std::cout << "sentence is: " << sentence << std::endl;
    initSentence(sentence, words);
    //clean(Dictionary, numberOfWordsInDictionary*maxCharactersInWord);
    return 0;
}