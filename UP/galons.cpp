#include <iostream>

size_t count = 0;

void galonsRecursive(int restWater, int galonsIndex, int previous) {
	if(restWater < galonsIndex) {
		return;
	}
	if(galonsIndex == 0 && restWater > 0) {
		return;	
	}
	if(galonsIndex == 0 && restWater == 0) {
		count++;
		std::cout << std::endl;
		return;
	}

	
	std::cout << "restWater: " << restWater << std::endl;
	std::cout << "galonsIndex: " << galonsIndex << std::endl;
	for(int i = previous; i >= (int)(restWater/galonsIndex); --i) {
		std::cout << i << ' ';
		galonsRecursive(restWater-i, galonsIndex-1, i);
	}
}

void galons(size_t n) {

	galonsRecursive(n, 4, 0);
}

int main() {
	size_t n;
	std::cin >> n;
	
	galons(n);
	std::cout << count << std::endl;

	return 0;
}
