#include <iostream>

using namespace std;

void clean(int **&matrix, int n) {
	for(int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = NULL;
}

void alloc(int **&matrix, int n, int m) {
	for(int i = 0; i < n; i++) {
		*matrix[i] = new[m];
	}
}


int main() {

	return 0;
}
