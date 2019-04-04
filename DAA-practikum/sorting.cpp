#include <iostream>

int main() {

	int n;
	std::cin >> n;
	
	int* array = new int[n];
	for(int i = 0; i < n; ++i) {
		std::cin >> array[i];
	}
	int minIndex;
	for(int i = 0; i < n-1; ++i) {
		minIndex = i;
		for(int j = i + 1; j < n; ++j) {
			if(array[j] < array[minIndex]) {
				minIndex = j;
			}
		}
		std::swap(array[i], array[minIndex]);
	}

	for(int i = 0; i < n; ++i) {
		std::cout << array[i] << ' ';
	}
	delete[] array;
	return 0;
}
