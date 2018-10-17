#include <iostream>

int countBits(const int n) {
	int count = 0;
	int mask = 1;
	int shift = 0;
	while(shift < 31) {
		if((n & mask) != 0) {
			count++;
		}
		shift++;
		mask <<= 1;
	}
	return count;
}

int main() {
	size_t m, n;
	std::cin >> m >> n;

	size_t** matrix = new size_t*[m];
	for(int i = 0; i < m; ++i) {
		matrix[i] = new size_t[n];
	}

	size_t* indexOfMagicRows = new size_t[m];
	size_t bitsInRow;
	size_t j = 0;
	
	for(int i = 0; i < m; ++i) {

		bitsInRow = 0;
		for(int k = 0; k < n; ++k) {
			std::cin >> matrix[i][k];
			bitsInRow += countBits(matrix[i][k]);
		}
		if(bitsInRow%2 == 0) {
			indexOfMagicRows[j++] = i;
		}
	}

	size_t* newArray = new size_t[j*n];
	int i = 0;
	for(int k = 0; k < j; ++k) {
		for(int l = 0; l < n; ++l) {	
			newArray[k*n+l] = matrix[indexOfMagicRows[k]][l];
		}
	}

	for(int k = 0; k < j*n; ++k) {
		std::cout << newArray[k] << " ";
	}

	delete[] newArray;	
	delete[] indexOfMagicRows;	
	
	for(int i = 0; i < m; ++i) {
		delete matrix[i];
	}
	delete[] matrix;
	
	return 0;
}
