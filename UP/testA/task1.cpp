#include <iostream>

int main() {
	int n;
	std::cin >> n;
	double* array = new double[n];
	double number;
	bool inArray = false;
	int k = 0;
	for(int i = 0; i < n; ++i) {
		std::cin >> number;
		
		for(int j = 0; j < i; ++j) {
			if(number == array[j]) {
				inArray = true;
				break;
			} else {
				inArray = false;
			}
		}
		if(!inArray) {
			array[k++] = number;
		}
	}

		
	for(int i = 0; i < k; ++i) {
		for(int j = 0; j < i; ++j) {
			if(array[i] > array[j]) {
				int buff = array[i];
				array[i] = array[j];
				array[j] = buff;
			}
		}
	}
	
	for(int i = 0; i < k; ++i) {
		std::cout << array[i];
	}


	delete[] array;

	return 0;
}
