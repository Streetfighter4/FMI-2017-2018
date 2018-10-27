#include <iostream>
#include <iomanip>

int main() {
	int n = 30;
	int count = n;
	for(char c = 'A'; c < 'A' + n; ++c) {	
		std::cout << std::setw(count);	
		--count;
		for(char d = 'A'; d < c; ++d) {
			std::cout << d;	
		}
		for(char d = c; d >= 'A'; --d) {
			std::cout << d;
		}
		std::cout << std::endl;
	}
	
	
	return 0;
}
