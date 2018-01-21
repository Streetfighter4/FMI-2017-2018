#include <iostream>
#include <string.h>

using namespace std;

int main() {
	char word[10];
	word[0] = '\0';
	cout << "first lenght: " << strlen(word) << endl;
	word[0] = 'a';
	word[1] = 'b';
	word[2] = '\0';
	cout << "second lenght: " << strlen(word) << endl;

	return 0;
}
