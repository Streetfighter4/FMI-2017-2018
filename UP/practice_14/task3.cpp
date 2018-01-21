#include <iostream>

using namespace std;

bool isDigRepeatRes(int num, int currDigit) {
	if(num < 10) return num == currDigit;

	if(num%10 == currDigit) return true;

	if(isDigRepeatRes(num/10, currDigit)) return true;
	else
		return isDigRepeatRes(num/10, num%10);
}

bool isDigitRepeat(int num) {
	if(num < 10) {
		return false;
	}	
	return isDigRepeatRes(num/10, num%10);
}

int main() {
	cout <<(isDigitRepeat(12334) ? "Yes" : "No") << endl;	
	return 0;
}
