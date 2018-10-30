#include <iostream>
#include <iomanip>
#include <math.h>

double distanceBetweenPoints(double x1, double x2, double y1, double y2){
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

int main() {
	double x, y;
	std::cin >> x >> y;

	if(distanceBetweenPoints(x, 0, y, 0) <= 4) {
		double d = distanceBetweenPoints(x, -2, y, 0);
		if(y >= 0) {
			if(distanceBetweenPoints(x, 2, y, 0) < 2 || d < 1) {
				std::cout << "Out" << std::endl;
			} else {
				std::cout << "In" << std::endl;	
			}
		} else {
			if(d < 1 || d > 2) {
				std::cout << "Out" << std::endl;
			} else {
				std::cout << "In" << std::endl;
			}
		}
	} else {
		std::cout << "Out" << std::endl;
	}


	return 0;
}
