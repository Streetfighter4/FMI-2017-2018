#include <iostream>

using namespace std;

#define SIZE 10

void printMatrix(int a, int b, int matrix[][SIZE]) {
	for(int i = 0; i < a; i++) {
		for(int j = 0; j < b; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}


void fillMatrix() {
	int m, n;
	cin >> m >> n;
	int matrix[SIZE][SIZE];
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}
	printMatrix(m, n, matrix);
}

int main() {
	fillMatrix();	
	return 0;
}
