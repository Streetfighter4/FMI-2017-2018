#include <iostream>
#include <math.h>

int main() {
	double n;
	double fn;
	std::cin >> n >> fn;
	
	unsigned long long k = ceil((-fn - 0.5) + sqrt(fn*fn - fn + 2*n + 0.25)) + 1;
	std::cout << k << std::endl;
	
	return 0;
}
