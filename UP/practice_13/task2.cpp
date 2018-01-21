#include <iostream>
#include <math.h>
using namespace std;

typedef unsigned int u_int;

bool isPrimeHelper(u_int n, u_int d) {
	if(d < 2) return true;

	if(n%d == 0) {
		return false;
	} else {
		isPrimeHelper(n, d-1);
	}
}

bool isPrime(u_int n) {
	return isPrimeHelper(n, sqrt(n));
}

int main() {
	u_int n;
	cin >> n;

	cout << isPrime(n) << endl;

}
