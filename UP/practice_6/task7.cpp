#include <iostream>

using namespace std;

int function(int x, int y) {
	int times = 0;
	while (x%y == 0) {
		times++;
		x /= y;
	}
	return times;
}

int main() {
	int x, y;
	cin >> x >> y;
	int times = function(x, y);
	cout << times << endl;

	return 0;
}
