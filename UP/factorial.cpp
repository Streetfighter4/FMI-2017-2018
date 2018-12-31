#include <iostream>

unsigned int fact(unsigned int number) {
	if(number == 1) {
		return 1;
	}	
		
	return number * fact(number-1);
}

int main() {
	unsigned int res = fact(5);
	std::cout << res << std::endl;
	
}
