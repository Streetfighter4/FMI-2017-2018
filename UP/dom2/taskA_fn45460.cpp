#include <iostream>

using namespace std;

#define MAX_SIZE_ARRAY 10
int valueRows = 0;
int valueCols = 0;

bool checkLines(int array[][MAX_SIZE_ARRAY], int size, bool rowOrCol) {
	int sum;
	int sumPrev = 0;
	bool magicLines = false;
	for(int i = 0; i < size; ++i) {
		sum = 0;
		for(int j = 0; j < size; ++j) {
			if(rowOrCol)
				sum += array[i][j];
			else
				sum += array[j][i];
		}
		if (sum != sumPrev && i != 0) {
			magicLines = false;
			break;
		} else {
			sumPrev = sum;
			magicLines = true;
		}
	}		
	if(rowOrCol)
		valueRows = sum;
	else
		valueCols = sum;

	return magicLines;
}

int checkDiagonal(int array[][MAX_SIZE_ARRAY], int size, bool diagonal) {
	int sumDiagonal = 0;
	for(int i = 0; i < size; ++i) {
		if(diagonal)
			sumDiagonal += array[i][i];
		else
			sumDiagonal += array[size - (i+1)][i];
	}
	return sumDiagonal;
}


int main() {
	int array[MAX_SIZE_ARRAY][MAX_SIZE_ARRAY];
	int size = 0;
	cin >> size;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cin >> array[i][j];
		}
	}

	bool magicRows = checkLines(array, size, true);
	bool magicCols = checkLines(array, size, false);
		
	int valueFirstDiagonal = checkDiagonal(array, size, true);
	int valueSecondDiagonal = checkDiagonal(array, size, false);
	
	if ((magicCols && magicRows) &&
			(valueRows == valueCols) &&
			(valueRows == valueFirstDiagonal) &&
			(valueRows == valueSecondDiagonal))
		cout << "True" << endl;
	else {
		cout << "False" << endl;
	}

	return 0;
}
