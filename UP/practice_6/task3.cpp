#include <iostream>

using namespace std;

int pow(int number, int power) {
	int res = 1;
	for(int i = 0; i < power; ++i) {
		res *= number;
	}
	return res;
}

int main() {
	int number, power;
	cin >> number >> power;

	int res = pow(number, power);
	cout << res << endl;

	return 0;
}
