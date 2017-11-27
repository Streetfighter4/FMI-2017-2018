#include <iostream>

using namespace std;

#define SIZE 10

int smallestNum(int a, int b, int matrix[][SIZE]) {
	int smallestNum = matrix[0][0];
	for (int i = 0; i < a; i++) {
		for (int j = 1; j < b; j++) {
			if(matrix[i][j] < smallestNum)
				smallestNum = matrix[i][j];
		}
	}
	return smallestNum;
}


void fillMatrix(){
	int m, n;
	cin >> m >> n;
	int matrix[SIZE][SIZE];
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}
	cout << smallestNum(n, m, matrix);

}

int main() {
	fillMatrix();
	
	return 0;
}
