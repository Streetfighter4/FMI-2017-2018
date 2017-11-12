#include <iostream>

using namespace std;

int main() {
	unsigned int n;
	cin >> n;
	unsigned int sum = 0;

	for(int i = 0; i < n; ++i) {
		int number;
		cin >> number;

		while (number > 0) {
			sum += number%10;
			number /= 10;
		}
	}
	
	cout << sum << endl;

	return 0;
}
