#include <iostream>

using namespace std;

int main() {
	unsigned int x, y;
	cin >> x >> y;

	for(int i = 0; i < y; ++i) {
		for(int j = 0; j < x; ++j) {
			if (i == 0 || i == y-1 || j == 0 || j == x-1) {
				cout << "*";
			} else {
				cout << " ";
			}
		}
		cout << endl;
	}


	return 0;
}
