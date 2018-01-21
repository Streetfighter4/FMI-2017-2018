#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

typedef unsigned int u_int;

bool isDig(const char c) {
	return ((c >= '0') && (c <= '9'));
}

int atoi(const char* str, u_int index) {
	u_int res = 0;
	while(str[index] && isDig(str[index])) {
		res *= 10;
		res += str[index] - '0';
		index++;
	}
	return res;
}

char* decompres(char* str, u_int index) {	
	u_int start_index = index;
	while(str[index]) {
		u_int res = 0;
		u_int digInRes = 0;
		if(isDig(str[index])){
			res = atoi(str, index);
			digInRes = (u_int)log10(res)+1;
			index += digInRes;
		}
		if(str[index] == '(') {
			char* newStr = decompres(str, index+1);
			char* memStr = new(nothrow) char[strlen(str) + strlen(newStr)*res];
			strncpy(memStr, str, index);
			for(u_int i = 0; i < res; i++) {
				strncpy(memStr + index - digInRes + i*strlen(newStr), newStr, strlen(newStr));
			}

			strncpy(memStr+index-digInRes + res*strlen(newStr),
					str+index + 2 + strlen(newStr),
					strlen(str) - index);
			str = memStr;
		}
		if(str[index] == ')') {
			char* newStr = new(nothrow) char[index-start_index];
			strncpy(newStr, str+start_index, index-start_index);
			return newStr;
		}
		index++;
	}
	char* newStr = new(nothrow) char[index-start_index];
	strncpy(newStr, str+start_index, index-start_index);
	return newStr;
}

int main() {
	size_t size = 1024;
	char* str = new(nothrow) char[size];
	cin.getline(str, size);
	u_int index = 0;
	char* decompresedStr = decompres(str, index);
	cout << decompresedStr << endl;
	return 0;
}
