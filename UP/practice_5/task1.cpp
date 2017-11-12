#include <iostream>

using namespace std;

int main() {
	unsigned int a, b, c;
	cin >> a >> b >> c;
	
	if (a > b) {
		int buff = a + b;
		a = b;
		b = buff - a;
	}
	if (a > c) {		
		int buff = a + c;
		a = c;
		c = buff - a;
	}
	if (b > c) {			
		int buff = b + c;
		b = c;
		c = buff - b;
	}

	cout << a << b << c << endl;

	return 0;
}
