#include <iostream>

using namespace std;

int main() {
	unsigned int number;
	do {
		cin >> number;
	} while (number < 0 || number > 40);

	unsigned long long int sum = 1;
	
	for(int i = 2; i <= number; i++) {
		sum *= i;
	}

	cout << sum << endl;

	return 0;
}
