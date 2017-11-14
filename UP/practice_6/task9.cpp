#include <iostream>

using namespace std;

void print(int max) {
	cout << max << endl;
}

int input() {
	int n;
	cin >> n;
	int number;
	int max = 0;
	for (int i = 0; i < n; i++) {
		cin >> number;
		if (max < number) {
			max = number;
		}
	}
	return max;
}

int main() {
	print(input());
	return 0;
}
