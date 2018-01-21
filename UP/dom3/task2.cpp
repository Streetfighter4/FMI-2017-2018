#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

typedef unsigned int u_int;

const char* words[] = {"apple", "orange", "month", "vehicle", "bookmarks"};
const u_int wordsCount = 5;
const u_int historyLetters = 26;
const u_int maxMistakes = 5;


bool isGuessWord(char historyArray[], u_int indexWord, u_int letters) {
	u_int guessedLetters = 0;
	u_int i = 0;
	while(words[indexWord][i]) {
		u_int j = 0;
		while(historyArray[j]) {
			if(words[indexWord][i] == historyArray[j++]) {
				++guessedLetters;
			}
		}
		i++;
	}

	return (guessedLetters == letters);
}

void print(char historyArray[], u_int indexWord, u_int mistakes, u_int letters) {
		cout << '[' << mistakes << '/' << maxMistakes << "] ";
		for(u_int j = 0; j < letters; j++) {
			u_int index = 0;
			bool noSuchLetter = true;
			while(historyArray[index]) {
				if(words[indexWord][j] == historyArray[index]) {
					cout << historyArray[index] << ' ';
					noSuchLetter = false;
					break;
				}
				index++;
			}
			if (noSuchLetter) {
				cout << "_ ";
			}
		}
		cout << "History: ";
		u_int i = 0;
		while(historyArray[i])
			cout << historyArray[i++] << ' ';

		cout << endl;
}

char enterLetter(u_int indexWord, u_int& mistakes) {
	cout << "Choose a letter: ";
	char letter;
	cin >> letter;
	u_int j = 0;
	bool noSuchLetter = true;
	while(words[indexWord][j]) {
		if(words[indexWord][j] == letter) {
			noSuchLetter = false;
			cout << "OK" << endl;
			break;
		}
		j++;
	}
	if(noSuchLetter) {
		mistakes++;
		cout << "No such letter" << endl;	
	}

	return letter;
}

void play() {
	u_int indexInHistoryArray;
	u_int mistakes;
	u_int indexWord;	
	srand(time(NULL));	
	
	while(true) {
		indexInHistoryArray = 0;
		mistakes = 0;
		char historyArray[historyLetters] = {0};
		indexWord = rand()%wordsCount;
		
		while(mistakes < maxMistakes) {
			u_int lettersInWord = strlen(words[indexWord]);
			print(historyArray, indexWord, mistakes, lettersInWord);	
			char letter = enterLetter(indexWord, mistakes);	
			historyArray[indexInHistoryArray++] = letter;
			
			if(isGuessWord(historyArray, indexWord, lettersInWord)) {
				cout << "Congratulations, you guessed the word!!!" << endl;
				break;
			}
		}

		char choice;
		do {
			cout << "One more word? [Y/N]" << endl;
			cin >> choice;
		} while(!(tolower(choice) == 'y' || tolower(choice) == 'n'));
		
		if(tolower(choice) == 'y') {
			continue;
		} else if(tolower(choice) == 'n') {
			cout << "Bye, bye :)" << endl;
			return;
		}
	}
}
int main() {
	play();	
	return 0;
}
