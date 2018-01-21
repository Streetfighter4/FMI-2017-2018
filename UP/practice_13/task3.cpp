#include <iostream>

using namespace std;

typedef unsigned int u_int;

void binaryNumber(u_int n) {
	if(n == 0) return;

	binaryNumber(n >> 1);
	cout << n%2;
}

int main() {
	u_int n;
	cin >> n;

	binaryNumber(n);	

	return 0;
}
