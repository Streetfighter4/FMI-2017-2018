#include <iostream>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

struct Point {
	int x, y;
};

struct Rectangle {
	Point p1, p2;
};

void printPoint(const Point p) {
	cout << '(' << p.x << ',' << p.y << ')' << endl;
}

void fillPoint(Point& p) {
	cout << "Point x: " << endl;
	cin >> p.x;
	cout << "Point y: " << endl;
	cin >> p.y;
}

void fillRect(Point& p1, Point& p2) {
	fillPoint(p1);
	fillPoint(p2);
}

void printRect(const Rectangle rec) {
	cout << "In printRect() " << endl;
	Point p1 = rec.p1;
	Point p2 = rec.p2;
	printPoint(p1);
	printPoint(p2);
	for(int i = p1.x; i < p2.x; ++i) {
		for(int j = p1.y; j < p2.y; ++j) {
			cout << '*';
		}
		cout << endl;
	}
}

double distanceToCenter(const Point p) {
	return sqrt(pow(p.x,2) + pow(p.y, 2));
}

double distancePointToPoint(const Point p1, const Point p2) {
	return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

int main() {
	Point p1, p2;
	fillPoint(p1);
	fillPoint(p2);
	printPoint(p1);
	printPoint(p2);
	cout << distanceToCenter(p1) << endl;
	cout << distancePointToPoint(p1, p2) << endl;
	Rectangle rec;
	fillRect(p1, p2);
	printRect(rec);
	return 0;
}
