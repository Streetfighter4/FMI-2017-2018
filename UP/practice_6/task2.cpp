#include <iostream>

using namespace std;

int abs(int x) {
	return (x >= 0) ? x : -x;
}

int main() {
	int x;
	cin >> x;
	int res = abs(x);
	cout << res << endl;

	return 0;
}
