#include <iostream>

long int matrix1[20][20];
long int matrix2[20][20];

int main() {
	unsigned short m, n, k;
	std::cin >> m >> n >> k;

	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			std::cin >> matrix1[i][j];
		}
	}

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < k; ++j) {
			std::cin >> matrix2[i][j];
		}
	}
	long long int res;	
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < k; ++j) {
			res = 0;
			for(int a = 0; a < n; ++a) {
				res += (matrix1[i][a] * matrix2[a][j]);
			}
			std::cout << res << " ";
		}
		std::cout << std::endl;
	}

	
	return 0;
}
