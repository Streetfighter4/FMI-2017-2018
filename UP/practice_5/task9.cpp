#include <iostream>
#include <math.h>
using namespace std;

int main() {
	unsigned int a, b;
	cin >> a >> b;
	bool is_prime;
	int sum = 0;
	for(; a <= b; ++a) {
		is_prime = true;
		for(int i = 2; i <= sqrt(a); ++i) {
			if (!(a%i != 0)) {
				is_prime = false;	
				break;
			}
		}
		if (is_prime) {
			sum += a;
		}
	}

	cout << sum << endl;

	return 0;
}
