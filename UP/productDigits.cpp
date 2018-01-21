#include <iostream>

using namespace std;

typedef unsigned int u_int;

u_int productDig(u_int number) {
	if(number/10 == 0) {
		return number;
	}
	return number%10 * productDig(number/10);
}

int main() {
	u_int number;
	cin >> number;
	cout << productDig(number) << endl;
	
	return 0;
}
