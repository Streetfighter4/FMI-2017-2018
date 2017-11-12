#include <iostream>

using namespace std;

int main() {
	int num;
	cin >> num;
	cout << "Before: \n";
	unsigned int i;
	for (i = 1 << 31; i > 0; i >>=1) {
		cout << !!(num&i);
	}
	cout << endl;
	int bit1 = num&1;
	cout << "bit1: " << bit1 << endl;
	int bit2 = !!(num&(1<<1));
	cout << "bit2: " << bit2 << endl;
	num = 0 << 2;
	for (i = 1 << 31; i > 0; i >>=1) {
		cout << !!(num&i);
	}
	cout << endl;
	num = bit1 >> 1;
	num = bit2 >> 1;
	cout << "After: \n";
	for (i = 1 << 31; i > 0; i >>=1) {
		cout << !!(num&i);
	}
	return 0;
}
