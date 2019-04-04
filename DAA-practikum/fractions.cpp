#include <iostream>
#define MAX_N 100
struct Fraction {
	int x;
	int y;
};

int gcd(int a, int b) {
	if(a == 1 || b == 1) {
		return 1;
	}
	int r;
	while(b != 0) {
		r = b;
		b = a%b;
		a = r;
	}
	return a;
}

bool largestFraction(const Fraction& f1, const Fraction& f2) {
	if(f1.x*f2.y > f2.x*f1.y) {
		return false;
	}
	return true;
}

int main() {
	int n;
	std::cin >> n;	
	Fraction array[MAX_N*MAX_N];	
	int k = 0;
	for(int i = 1; i < n; ++i) {	
		for(int j = n; j > i; --j) {
			if(gcd(i, j) == 1) {
				array[k].x = i;
				array[k].y = j;
				++k;
			}
		}
	}

	int minIndex;
	for(int i = 0; i < k-1; ++i) {
		minIndex = i;
		for(int j = i + 1; j < k; ++j) {
			if(largestFraction(array[j], array[minIndex])) {
				minIndex = j;
			}
		}
		std::swap(array[i], array[minIndex]);
	}

	std::cout << "0 ";	
	for(int i = 0; i < k; ++i) {
		std::cout << array[i].x << '/' << array[i].y << ' ';
	}

	return 0;
}
