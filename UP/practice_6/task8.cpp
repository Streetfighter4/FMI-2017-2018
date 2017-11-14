#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

float function(int radius) {
	double pi = atan(1)*4;
	float aria = pi*radius*radius;
	return aria;
}


int main() {
	int radius;
	cin >> radius;
	float aria = function(radius);
	cout << setprecision(3) << aria << endl;
	return 0;
}
