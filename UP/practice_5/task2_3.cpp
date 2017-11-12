#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int point_x, point_y;
	cin >> point_x >> point_y;
	bool in = false;

	if(point_y >= 0) {
		float distance = sqrt(point_x*point_x + point_y*point_y);
		in = (distance <= 5.0f) ? true : false;
	} else {
		if (point_x <= 4 && point_x >= -4 && point_y >= -2) {
			in = true;
		} else {
			in = false;
		}
	}
	(in) ? cout << "In" << endl : cout << "Out" << endl;

	return 0;
}
