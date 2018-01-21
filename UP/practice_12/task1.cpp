#include <iostream>
#include <cstring>

bool isAlph(char c) {
	return (((c >= 'A') && (c <= 'Z')) || (c >= 'a') && (c <= 'z'));
}

bool isDig(char c) {
	return ((c >= '0') && (c <= '9'));
}

void toUpper(char* s) {
	int i = 0;
	while(s[i]){
		if((s[i] >= 'a') && (s[i] <= 'z'))
			s[i] -= 'a' - 'A';
	}
}

void changeSpSymbol(char* str, char ch, char sp) {
	int i = 0;
	while (str[i]) {
		if (str[i] == ch)
			str[i] = sp;

		i++;
	}
}

int atoi(const char* str) {
	int sign;
	if (*str == '-') {
		sign = -1;
		str++
	} else
		sign = 1;

	int res = 0;
	int i = 0;
	while(str[i]) {
		res *= 10;
		res += str[i] - '0';	
	}
	return res;
}

bool isPalindrome(const char* str) {
	size_t size = strlen(str);

	while(i < size/2) {
		if(str[i] != str[size-i])
			return false;
		
		i++;
	}
	return true;
}


void dynamicConcat(char*& dest, const char* src) {
	char* newMem = new[strlen(dest) + strlen(src) + 1];
	if(!newMem) return;

	strcpy(newMem, dest);
	strcat(newMem, src);
	delete[] dest;
	dest = newMem;
}

int main() {

	return 0;
}
