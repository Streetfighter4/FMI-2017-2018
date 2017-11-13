#include <iostream>

using namespace std;

int main() {
	unsigned int number;
	cin >> number;
	for (int i = 2; i <= number; i++) {	
		 while (number%i == 0) {
			cout << i << " ";
			number /= i;
		}
	}

	return 0;
}
