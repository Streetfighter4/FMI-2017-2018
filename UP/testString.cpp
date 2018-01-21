#include <iostream>
#include <string.h>
using namespace std;

char* subString(const char* str) {
	int i = 0;
	int start_index, end_index;
	while(str[i]) {
		if(str[i] == '(')
			start_index = i+1;

		if(str[i] == ')')
			end_index = i;	

		i++;
	}
	int size = end_index-start_index;
	char* substring = new(nothrow) char[size];
	strncpy(substring, str+start_index, size);

	return substring;
}

int main() {
	size_t size = 1024;
	char* str = new(nothrow) char[size];
	cin.getline(str, size);
	char* substring = subString(str);
	cout << substring << endl;
	return 0;
}
