#include <iostream>
#include <string.h>
const char* grammar[] = {"aSa", "aSb" , "bSa", "bSb", ""};
const char letter = 'S';

void deleteLetter(char *&str, char a1){
	if (str == NULL){
		return;
	}
	unsigned int len = strlen(str);
	unsigned int count = 0;
	for (int i = 0; i < len; i++){
		if (str[i] == a1){
			count++;
		}
	}
	char *buff = new(std::nothrow) char[len - count + 1];
	if (buff != NULL){
		int i = 0;
		int j = 0;
		while (str[i] != '\0'){
			if (str[i] != a1){
				buff[j++] = str[i];
			}
			i++;
		}
		buff[len - count] = '\0';
		delete[] str;
		str = buff;
		buff = NULL;
	}
}


void changeLetter(char *&str, char a1, char a2){
	if (str == NULL){
		return;
	}
	unsigned int len = strlen(str);
	char* buff = new(std::nothrow)char[len + 1];
	if(buff != NULL){
		for (int i = 0; i < len; i++){
			if (str[i] == a1){
				buff[i] = a2;
			}
			else{
				buff[i] = str[i];
			}
		}
		buff[len] = '\0';
		delete[] str;
		str = buff;
		buff = NULL;
	}
}

void changeLetterWithString(char *&str, char a1, const char* removeStr){
	if (str == NULL){
		return;
	}
	unsigned int lenStr = strlen(str);
	unsigned int lenRemover = strlen(removeStr);
	if (lenRemover == 0){
		deleteLetter(str, a1);
	}
	else if (lenRemover == 1){
		changeLetter(str, a1, removeStr[0]);
	}
	unsigned int count = 0;
	for (int i = 0; i < lenStr; i++){
		if (str[i] == a1){
			count++;
		}
	}
	char *buff = new(std::nothrow) char[lenStr - count + count*lenRemover + 1];
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	while (str[i] != '\0'){
		if (str[i] == a1){
			while (k < lenRemover){
				buff[j++] = removeStr[k++];
			}
			k = 0;
		}
		else{
			buff[j++] = str[i];
		}
		i++;
	}
	buff[lenStr - count + count*lenRemover] = '\0';
	delete[] str;
	str = buff;
	buff = NULL;
}




void generateStrings(char*& str, size_t k) {
	if(k == 0) {
		deleteLetter(str, letter);
		std::cout << str << std::endl;
		return;
	}
	for(int i = 0; i < 4; ++i) {
		changeLetterWithString(str, letter, grammar[i]);
		generateStrings(str, k-2);
	}

}


int main() {
	size_t k = 4;
	char* startString = new char[1];
	startString[0] = 'S';
	generateStrings(startString, k);

	return 0;
}
