#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int x1 = 1;
	int y1 = 1;
	int r = 3;
	int x_point, y_point;
	cin >> x_point >> y_point;
	int length_x, length_y;	
	if(x_point <= 0) {
		length_x = abs(x_point) + x1;
	} else {
		length_x = x_point - x1;
	}
	

	if(y_point <= 0) {
		length_y = abs(y_point) + y1;
	} else {
		length_y = y_point - y1;
	}

	(sqrt(length_x*length_x + length_y*length_y) <= 3)? cout << "In\n": cout << "Out\n";
	return 0;
}
