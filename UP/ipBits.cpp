#include <iostream>
#include <math.h>
using namespace std;

int main() {
	unsigned int number;
	cin >> number;
	int mask = 0;
	int power = 7;
	int sum = 0;
	for(int i = (sizeof(unsigned int)*8) - 1; i >= 0; --i) {
		mask = (1 << i);
		mask &= number;
		if (power >= 0) {
			if (mask != 0) {
				sum	+= 1*(pow(2, power));
			}
			power--;
		} else {
			cout << sum << ".";
			power = 7;
			sum = 0;
		}
	}

	return 0;
}
