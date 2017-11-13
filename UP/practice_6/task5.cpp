#include <iostream>

using namespace std;

int fib(int n) {
	int fib1 = 1;
	int fib2 = 1;
	int fib3 = 0;
	for (int i = 1; i <= n-2; ++i) {
		fib3 = fib1 + fib2;
		fib1 = fib2;
		fib2 = fib3;
	}
	return fib3;
}

int main() {
	unsigned int n;
	cin >> n;

	int res = fib(n);
	cout << res << endl;

	return 0;
}
