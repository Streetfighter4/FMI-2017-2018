#include <iostream>

using namespace std;

const int BUFF_SIZE = 1024;
// strstr()
// strtok()
// memset(buff, 0, 1024)
//
int strcmp(const char* lhs, const char* rhs) {
	size_t = 0;
	while(lhs[i] && lhs[i] == rhs[i])
		i++;

	return (int)(lhs[i] - rhs[i]);
}


void strcat(char *dest, const char* src) {
	size_t size = strlen(dest);
	size_t i = 0;
	while(src[i]) {
		dest[size++] = src[i++];
	
	dest[size+i] = '\0';
}

size_t strlen(const char *buff) {
	size_t len = 0;
	while(buff[len] != '\0')
		len++;

	return len;
}

void strcpy(char *dest, const char* src) {	
	size_t len = strlen(src);
	for(int i = 0; i <= len; i++)
		dest[i] = src[i];
}

int main() {

	char buff[BUFF_SIZE];

	cin.getline(buff, BUFF_SIZE);

	

	char *str = new nothrow char[len+1];



	return 0;
}
