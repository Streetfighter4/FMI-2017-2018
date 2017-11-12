#include <iostream>

using namespace std;

int main() {
	int x1 = -3;
	int y1 = 2;
	int x2 = 2;
	int y2 = -3;

	int x_point, y_point;
	cin >> x_point >> y_point;

	if ((x_point >= x1 && x_point <= x2) && 
		(y_point <= y1 && y_point >= y2)) {
		cout << "Point is in the figure!" << endl;
	} else {
		cout << "Point is not in the figure!" endl;
	}

	return 0;
}
