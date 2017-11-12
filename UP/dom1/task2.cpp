#include <iostream>

using namespace std;

int main() {
	unsigned int num;
	cin >> num;
	unsigned short int i;
	for (i = sizeof(unsigned int)*8 - 1; i >= 0; i--) {
		int mask = 1 << i;
		mask&=num;
		if (mask != 0) { break; }
	}

	int curr_bit = 0;
	int prev_bit = 0;
	int rv_prev_bit = 0;
	int mask = 1 << i;
	while (mask > 0) {
		curr_bit = mask&num;
		if (curr_bit != 0) {
			if (prev_bit == 1 && rv_prev_bit == 1) {
				num ^= mask;
				prev_bit = 0;
				rv_prev_bit = 1;
			} else {
				prev_bit = 1;
				rv_prev_bit = 1;
			}
		} else {
			if (prev_bit == 0 && rv_prev_bit == 0) {
				num |= mask;
				prev_bit = 1;
				rv_prev_bit = 0;
			} else {
				prev_bit = 0;
				rv_prev_bit = 0;
			}
		}
		mask >>= 1;
	}
	cout << num << endl;
	return 0;
}
