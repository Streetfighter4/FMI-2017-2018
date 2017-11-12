#include <iostream>

using namespace std;

int main() {
	unsigned int number;
	cin >> number;
	int i = 2;
	while (number >= 0) {
		if (number%i == 0) {
			do {
				cout << i << " ";
				number /= i;
			} while (number%i == 0);
		}
		++i;
	}

	return 0;
}
