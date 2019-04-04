#include <iostream>
#include <string.h>
#define MAX_N 10000

void lexicSort(char* array[], int n) {
	int minIndex;
	char c;
	for(int i = 0; i < n-1; ++i) {
		minIndex = i;
		for(int j = i + 1; j < n; ++j) {
			if(strcmp(array[j], array[minIndex]) < 0) {
				minIndex = j;
			}
		}
		std::swap(array[i], array[minIndex]);
	}
}


int main() {
	int n;
	char* array[MAX_N];
	std::cin >> n;
		
	for(int i = 0; i < n; ++i) {
		array[i] = new char[10];
		std::cin >> array[i];
	}
	
	lexicSort(array, n);	
	
	for(int i = 0; i < n; ++i) {
		std::cout << array[i] << std::endl;
		delete[] array[i];
	}
	

	return 0;
}
