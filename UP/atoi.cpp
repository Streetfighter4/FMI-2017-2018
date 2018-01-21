#include <iostream>

using namespace std;

typedef unsigned int u_int;

bool isDig(const char c) {
	return ((c <= '9') && (c >= '0'));
}

u_int atoi(const char* str) {
	u_int res = 0;
	u_int i = 0;
	while(str[i]) {
		if(isDig(str[i])) {	
			res *= 10;
			res += str[i] - '0';
		}
		i++;
	}
	return res;
}


int main() {
	char str[100];
	cin >> str;
	cout << atoi(str) << endl;

	return 0;
}
