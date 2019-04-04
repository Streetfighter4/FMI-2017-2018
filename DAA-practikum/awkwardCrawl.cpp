#include <iostream>
#include <iomanip>

#define MAX_N 100

int main() {
	int array[MAX_N][MAX_N];
	int n;
	std::cin >> n;

	int num = 1;
	int i = 0, j = n;
	while(i < n) {
		for(int temp = 0; temp < j; ++temp, ++num) {
			array[i][temp] = num;
		}
		--num;
		for(int temp = i; temp < n; ++temp, ++num) {
			array[temp][j-1] = num;	
		}
		++i;
		--j;
		for(int temp = n-1; temp >= i; --temp, ++num) {
			array[temp][j-1] = num;
		}
		--num;
		for(int temp = j-1; temp >= 0; --temp, ++num) {
			array[i][temp] = num;
		}
		++i;
		--j;
	}

	for(int m = 0; m < n; ++m) {
		for(int p = 0; p < n; ++p) {
			std::cout << std::setw(5) << array[m][p];
		}
		std::cout << std::endl;
	}

	return 0;
}
