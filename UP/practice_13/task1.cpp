#include <iostream>

using namespace std;

typedef unsigned int u_int;

u_int fact(u_int n) {
	if(n == 1) return 1;

	return n*fact(n-1);
}

int main() {
	u_int n;
	cin >> n;

	cout << fact(n) << endl;

	return 0;
}
