#include <iostream>

void function(char* array, int size) {
	int j = 0;
	for(int i = 'a'; i <= 'z'; ++i) {
		array[j++] = i;
	}
	array[size] = '\0';
}

int main() {
	char* array = new char[27];
	if(array != NULL) {	
		function(array, 26);
		std::cout << array;
		delete[] array;
	}
	return 0;
}
