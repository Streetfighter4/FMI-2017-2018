#include <iostream>
#include <unistd.h>
unsigned int microseconds = 1000000;

size_t const MAXN = 20;

void reset(int matrix1[][MAXN], int matrix2[][MAXN]) {
	
	for(int i = 0; i < MAXN; ++i) {	
		for(int j = 0; j < MAXN; ++j) {
			matrix1[i][j] = matrix2[i][j];
		}
	}
}

void print(int matrix[][MAXN]) {	
	for(int i = 0; i < MAXN; ++i) {	
		for(int j = 0; j < MAXN; ++j) {
			std::cout << ((matrix[i][j]) ? '#' : ' ');
		}
		std::cout << std::endl;
	}
}


int countLifeNeighbours(int matrix[][MAXN], size_t x, size_t y) {
	int count = 0;
	if(x == 0) {
		if(y == 0) {		
			return matrix[x+1][y] + matrix[x+1][y+1] + matrix[x][y+1];	
		} else if(y == MAXN-1) {
			return matrix[x+1][y] + matrix[x+1][y-1] + matrix[x][y-1];	
		} else {	
			return matrix[x][y-1] + matrix[x+1][y-1] + matrix[x+1][y] + matrix[x+1][y+1] + matrix[x][y+1];	
		}
	} else if(x == MAXN-1) {	
		if(y == 0) {
			return matrix[x-1][y] + matrix[x-1][y+1] + matrix[x][y+1];	
		} else if(y == MAXN-1) {
			return matrix[x-1][y] + matrix[x-1][y-1] + matrix[x][y-1];	
		} else {	
			return matrix[x][y-1] + matrix[x-1][y-1] + matrix[x-1][y] + matrix[x-1][y+1] + matrix[x][y+1];	
		}
	} else {	
		if(y == 0) {		
			return matrix[x-1][y] + matrix[x-1][y+1] + matrix[x][y+1] + matrix[x+1][y+1] + matrix[x+1][y];	
		} else if(y == MAXN-1) {
			return matrix[x-1][y] + matrix[x-1][y-1] + matrix[x][y-1] + matrix[x+1][y-1] + matrix[x+1][y];	
		}	
	}
	
	return matrix[x-1][y-1] + matrix[x][y-1] + matrix[x+1][y-1] +
		   matrix[x-1][y] +                    matrix[x+1][y] +
		   matrix[x-1][y+1] + matrix[x][y+1] + matrix[x+1][y+1];	
}

bool makeLifeDecision(int cell, int countNeighbours) {
	if(cell == 1) {
		if(countNeighbours == 2 || countNeighbours == 3) {
			return true;
		} else {
			return false;
		}
	} else {
		if(countNeighbours == 3) {
			return true;
		} else {
			return false;
		}
	}
}


void play(int matrix1[][MAXN], int matrix2[][MAXN]) {
	int countNeighbours = 0;
	bool lifeDecision = false;
	for(int i = 0; i < MAXN; ++i) {	
		for(int j = 0; j < MAXN; ++j) {
			countNeighbours = countLifeNeighbours(matrix1, i, j);
			lifeDecision = makeLifeDecision(matrix1[i][j], countNeighbours);
			matrix2[i][j] = ((lifeDecision) ? 1 : 0);
		}
	}
	reset(matrix1, matrix2);
	print(matrix1);
}

void init(int matrix[][MAXN]) {

	matrix[1][3] = 1;
	matrix[1][4] = 1;
	matrix[1][5] = 1;
	matrix[1][9] = 1;
	matrix[1][10] = 1;
	matrix[1][11] = 1;
	matrix[3][1] = matrix[4][1] = matrix[5][1] = matrix[3][6] = matrix[4][6] = matrix[5][6] = 1;
	matrix[3][8] = matrix[4][8] = matrix[5][8] = matrix[3][13] = matrix[4][13] = matrix[5][13] = 1;	
	matrix[6][3] = matrix[6][4] = matrix[6][5] = matrix[6][9] = matrix[6][10] = matrix[6][11] = 1;

	matrix[8][3] = matrix[8][4] = matrix[8][5] = matrix[8][9] = matrix[8][10] = matrix[8][11] = 1;
	matrix[9][1] = matrix[10][1] = matrix[11][1] = matrix[9][6] = matrix[10][6] = matrix[11][6] = 1;
	matrix[9][8] = matrix[10][8] = matrix[11][8] = matrix[9][13] = matrix[10][13] = matrix[11][13] = 1;	
	matrix[13][3] = matrix[13][4] = matrix[13][5] = matrix[13][9] = matrix[13][10] = matrix[13][11] = 1;

}


int main() {
	
	int matrix1[MAXN][MAXN] = {{0, }, };
	init(matrix1);
	int matrix2[MAXN][MAXN] = {{0, }, };

	while(true) {
		std::cout << "\033[2J\033[1;1H";
		play(matrix1, matrix2);
		usleep(microseconds);
	}
	
	return 0;
}
