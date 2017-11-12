#include <iostream>
#include <amth.h>

using namespace std;

int main() {
	unsigned int number;
	cin >> number;

	if (number == 0) {
		cout << "-Inf" << endl;
	} else if (number > 0) {
		cout << 1 + log10(number) << endl;
	}

	return 0;
}
