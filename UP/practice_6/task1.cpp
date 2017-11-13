#include <iostream>

using namespace std;

int max(int x, int y) {
	return (x>=y) ? x : y;
}


int main() {
	int x, y;
	cin >> x >> y;

	int res = max(x, y);
	cout << res << endl;

	return 0;
}
