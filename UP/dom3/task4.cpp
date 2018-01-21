#include <iostream>
#include <string.h>

using namespace std;

typedef unsigned int u_int;

const u_int MAX_INPUT = 1024;

bool isAlpha(const char c){
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool checkDictionary(char* word, char* dictionary[], u_int wordsCount) {
	for(u_int i = 0; i < wordsCount; i++) {
		if(!strcmp(word, dictionary[i])) {
			return true;
		}
	}
	return false;
}

void fillDictionary(char**& dictionary) {
	char str[MAX_INPUT];
	cin.getline(str, MAX_INPUT);
	u_int i = 0;
	char* token = strtok(str, " ");
	while(token != NULL) {
		dictionary[i] = new(nothrow) char[strlen(token) + 1];
		
		strcpy(dictionary[i++], token);
	
		token = strtok(NULL, " ");
	}

}

void fillCrossWord(char**& crossWord, u_int width, u_int height) {
	for(u_int i = 0; i < width; i++){
		crossWord[i] = new char[height];
	}
	
	for(u_int i = 0; i < width; i++) {
		for(u_int j = 0; j < height; j++) {
			cin >> crossWord[i][j];
		}
	}	
}

void printCrossWord(char** crossWord, u_int width, u_int height) {
	for(u_int i = 0; i < width; i++) {
		for(u_int j = 0; j < height; j++) {
			cout << crossWord[i][j];
		}
		cout << endl;
	}	
}

bool checkRows(char** crossWord, char** dictionary, u_int width, u_int height, u_int wordsCount) {
	u_int indexInWord = 0;
	char word[width+1];
	for(u_int i = 0; i < width; i++) {	
		bool haveWord = false;
		for(u_int j = 0; j < height; j++) {	
			if(isAlpha(crossWord[i][j])) {
				word[indexInWord++] = crossWord[i][j];
				word[indexInWord] = '\0';
				haveWord = true;
			} else {
				haveWord = false;
				if(indexInWord > 1) {
					if(!checkDictionary(word, dictionary, wordsCount)) {
						return false;
					}
				}
				indexInWord = 0;
				word[0] = '\0';
			}
		}
		if(haveWord) {	
			if(indexInWord > 1) {
				if(!checkDictionary(word, dictionary, wordsCount)) {
					return false;
				}
			}
		}
		indexInWord = 0;
		word[0] = '\0';
	}
	return true;
}

void transposition(char** crossWord, char**& transpositionMatrix, u_int width, u_int height) {	
	for(u_int i = 0; i < height; ++i) {
		for(u_int j = 0; j < width; ++j)
			transpositionMatrix[i][j] = crossWord[j][i];
	}
}

int main() {
	u_int wordsCount;
	cin >> wordsCount;
	cin.ignore(256, '\n');// remaining input characters up to the next newline character are ignored
	char** dictionary = new char*[wordsCount];
	fillDictionary(dictionary);

	u_int width, height;
	cin >> width >> height;
	char** crossWord = new char*[width];
	fillCrossWord(crossWord, width, height);
	bool isColumnsOk = checkRows(crossWord, dictionary, width, height, wordsCount);	
	char** transpositionMatrix = new char*[height];	
	for(u_int i = 0; i < height; i++){
		transpositionMatrix[i] = new char[width];
	}
	
	transposition(crossWord, transpositionMatrix, width, height);
	bool isRowsOk = checkRows(transpositionMatrix, dictionary, height, width, wordsCount);	
	cout << ((isColumnsOk && isRowsOk) ? "True!\n" : "False!\n");
	return 0;
}
