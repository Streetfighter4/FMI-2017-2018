#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int nod(int x, int y) {
	int nod;
	int min_number = abs(min(x, y));
	for (int i = 1; i <= min_number; i++) {
		if (x%i == 0 && y%i == 0) {
			nod = i;
		}
	}
	return nod;
}

int main() {
	int x, y;
	cin >> x >> y;

	int res = nod(x, y);
	cout << res << endl;

	return 0;
}
