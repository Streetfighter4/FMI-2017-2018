#include <iostream>

using namespace std;

short int checkBitsInNumberRec(const int num, unsigned int mask, short int count) {
	if(!mask) return count;
	else {
		if(num&mask)	
			checkBitsInNumberRec(num, mask >> 1, ++count);
		else	
			checkBitsInNumberRec(num, mask >> 1, --count);
	}
}

bool checkBitsInNumber(const int num) {
	return checkBitsInNumberRec(num, 1 << 31, 0);
}


int main() {
	int num = (1 << 16) - 1;
	cout << num << endl;
	cout << ((!checkBitsInNumber(num)) ? "Equal bits" : "Not equal bits") << endl;

	return 0;
}
