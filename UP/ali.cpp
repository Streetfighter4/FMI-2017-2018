#include <iostream>
#include <cmath>

void printAddressArray(char* array, size_t size) {
	for(int i = 0; i < size; ++i) {
		std::cout << &array[i] << std::endl;
	}
}


int main() {
	char* array = new char[10];
	printAddressArray(array, 10);
	return 0;
}
