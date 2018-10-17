#include <iostream>
#include <string.h>

char letters[26];
void generateLetters() {
	for(int i = 0; i < 26; ++i)
		letters[i] = 'a' + i;
}


void generatePass(char str[], int n, int k, int pos) {
	if(n == k) {
		std::cout << str << std::endl;
		return;
	} else {
		str[pos] = letters[k];
		if(pos == n) {
			k++;
		}
		generatePass(str, n, k, pos+1);
	}
}

int main() {
	generateLetters();
	char str[3];	
	int n = 3;

	int pos = 0;
	for(int i = 0; i < 26; ++i) {
		str[pos] = letters[i];
		generatePass(str, n, i, pos);
		memset(str, 0, n);
	}	
	return 0;
}
