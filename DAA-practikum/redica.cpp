#include <iostream>


int main() {
	unsigned int n;
	std::cin >> n;

	unsigned int counter = 0;
	unsigned int siquenceSize = 1;
	int prev, current;
	std::cin >> current;	

	for(int i = 1; i < n; ++i) {
		prev = current;
		std::cin >> current;

		if(prev == current) {
			++siquenceSize;
		} else {
			counter += ((siquenceSize * (siquenceSize-1))/2);	
			siquenceSize = 1;
		}
	}
	if(siquenceSize > 1) {
		counter += ((siquenceSize * (siquenceSize-1))/2);
	}

	std::cout << counter+n << std::endl;

	return 0;
}
