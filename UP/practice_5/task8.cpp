#include <iostream>
#include <math.h>
using namespace std;

int main() {
	unsigned int number;
	cin >> number;

	bool is_prime = true;

	for(int i = 2; i <= sqrt(number); i++) {
		is_prime = !(number%i == 0) ? true : false;
		if (!is_prime) { break; }
	}

	(is_prime) ? cout << "Prime" << endl : cout << "Compose" << endl;
	return 0;
}
