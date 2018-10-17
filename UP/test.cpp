#include <iostream>

void function(int array[]) {
	std::cout << &array << std::endl;
}

int main() {
	int a = 10;
	int* pa = &a;
	
	std::cout << a << std::endl;
	std::cout << *(&a) << std::endl;
	
	//function(array);
	return 0;
}
