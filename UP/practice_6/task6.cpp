#include <iostream>
#include <math.h>

using namespace std;

bool isPrime(int number) {
	bool isPrime = true;
	for(int i = 2; i < sqrt(number); ++i) {
		isPrime = !(number%i == 0) ? true : false;
		if(!isPrime) { break; }
	}
	return isPrime;
}

int main() {
	int number;
	cin >> number;

	(isPrime(number)) ? cout << "Prime" << endl : cout << "Compose" << endl;
	return 0;
}
