#include <iostream>
#include <time.h>
#include <stdlib.h>

void clean(int** matrix, size_t index) {
	for(int i = 0; i < index; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}


void printMatrix(int** matrix, size_t columns, size_t rows) {	
	for(int i = 0; i < rows; ++i) {		
		for(int j = 0; j < columns; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


void fillMatrixRand(int** matrix, size_t columns, size_t rows) {	
	srand(time(NULL));
	for(int i = 0; i < rows; ++i) {		
		for(int j = 0; j < columns; ++j) {
			matrix[i][j] = rand() % 100;
		}
	}
}

int main() {
	const size_t columns = 10;
	const size_t rows = 8;

	int** matrix = new (std::nothrow)int*[rows];
	if(matrix) {
		for (size_t i = 0; i < rows; ++i) {
			matrix[i] = new(std::nothrow)int[columns];
			if(matrix[i] == NULL) {
				clean(matrix, i);
			}
		}
	} else {
		clean(matrix, 0);
	}

	fillMatrixRand(matrix, columns, rows);
	printMatrix(matrix, columns, rows);

	clean(matrix, rows);

	return 0;
}
