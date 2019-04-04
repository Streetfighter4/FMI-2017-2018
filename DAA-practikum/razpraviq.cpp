#include <iostream>
#include <stdlib.h>

int main() {
	unsigned int n;
	std::cin >> n;

	unsigned* array = new unsigned[n];
	for(int i = 0; i < n; ++i) {
		std::cin >> array[i];	
	}
	unsigned sum = 0;
	int minIndex;
	for(int i = 0; i < n-1; ++i) {
		minIndex = i;
		for(int j = i; j < n; ++j) {
			if(array[j] > array[minIndex]) {
				minIndex = j;
			}
		}
		sum += array[minIndex];
		std::swap(array[i], array[minIndex]);
	}
	sum += array[n-1];
	
	int k = (sum+1)/2;
	int b = 0;
	while(b < n && k != 0) {
		if(array[b] <= k) {
			k -= array[b];
		}
		++b;
	}
	if(sum%2 == 1) k++;

	std::cout << k << std::endl;

	delete[] array;
	return 0;
}
