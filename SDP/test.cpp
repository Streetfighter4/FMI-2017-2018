#include <iostream>
#include <stdlib.h>

class X {};

int main() {
	X obj;
	X array[100];	
	std::cout << "sizeof X: " << sizeof(X) << "bytes" << std::endl;
	std::cout << "sizeof obj: " << sizeof(obj) << "bytes" << std::endl;
	std::cout << "sizeof array: " << sizeof(array) << "bytes" << std::endl;
	return 0;
}
