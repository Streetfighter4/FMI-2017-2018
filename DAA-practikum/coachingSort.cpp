#include <iostream>
#include <string.h>
#include <stdio.h>

bool isDigit(const char c) {
	return (c >= '0' && c <= '9');
}

bool isAlphaLetter(const char c) {
	return (c >= 'A' && c <= 'Z');
}

bool isSmallLetter(const char c) {
	return (c >= 'a' && c <= 'z');
}


unsigned int convertData(const char c) {
	if(isDigit(c)) {
		return c - '0';
	} else if(isAlphaLetter(c)) {
		return c - 29;
	} else if(isSmallLetter(c)) {
		return c - 87;
	}
}

char restoreData(int i) {
	if(i >= 0 && i <= 9) {
		return i + 48;
	} else if(i >= 10 && i <= 35) {
		return i + 87;
	} else if(i >= 36 && i <= 61) {
		return i + 29;
	}
}

void countingSort(char* str, size_t size) {
	int buff[62];
	for(int i = 0; i < 62; ++i) {
		buff[i] = 0;
	}
	for(int i = 0; i < size; ++i) {
		buff[convertData(str[i])]++;
	}
	
	int j = 0;
	char c;
	for(int i = 0; i < 62; ++i) {
		c = restoreData(i);
		for(int k = 0; k < buff[i]; ++k) {
			str[j++] = c;
		}
	}
}

int main() {
	size_t n;
	std::cin >> n;
	char* str = new char[n];	
	scanf("%s", str);

	countingSort(str, n);

	printf("%s", str);
	delete[] str;
	return 0;
}
