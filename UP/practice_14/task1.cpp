#include <iostream>

using namespace std;

typedef unsigned int u_int;

u_int gcd(u_int a, u_int b) {
	if(b == 0) return a;
	else return gcd(b, a%b);
}

int main() {
	cout << gcd(15, 60) << endl;
	return 0;
}
