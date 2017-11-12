#include <iostream>
using namespace std;

int main () {
	unsigned int n;
	cin >> n;
	if (n <= 2) {
		cout << "Yes!" << endl;
		return 0;
	} else {
		int a, b, c;
		bool boolean = true;
		cin >> a;
		cin >> b;
		for (int i = 0; i < n-2; i++) {
			cin >> c;		
			if ((a <= b && b >= c) || (a >= b && b <= c)) {
				continue;
			} else {
				boolean = false;
				break;
			}				
			a = b;
			b = c;
		}
		(boolean == true) ? cout << "Yes!\n" : cout << "No!\n";
	}
	return 0;
}
