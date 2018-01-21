#include <iostream>

using namespace std;

typedef unsigned int u_int;

bool isDigRepeat(u_int number, u_int buff[]) {
	if(buff[number%10] == 0) {
		buff[number%10]++;
		isDigRepeat(number/10, buff);
	} else {
		return false;
	}
	return true;
}

int main() {
	u_int number;
	cin >> number;
	u_int buff[10];
	cout << isDigRepeat(number, buff) << endl;
	return 0;
}
