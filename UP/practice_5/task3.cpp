#include <iostream>

using namespace std;

int main() {
	int num;
	cin >> num;
	if (num > 51 || num < 0) {
		cin >> num;
	}

	switch(num/13){
		case 0:
			cout << "spatiq" << endl;
			break;
		case 1:
			cout << "karo" << endl;
			break;
		case 2:
			cout << "kupa" << endl;
			break;
		case 3:
			cout << "pika" << endl;
			break;
	}
	
	switch(num%13) {
		case 0: cout << "A" << endl; break;
		case 1: cout << "2" << endl; break;
		case 2: cout << "3" << endl; break;
		case 3: cout << "4" << endl; break;
		case 4: cout << "5" << endl; break;
		case 5: cout << "6" << endl; break;
		case 6: cout << "7" << endl; break;
		case 7: cout << "8" << endl; break;	
		case 8: cout << "9" << endl; break;
		case 9: cout << "10" << endl; break;
		case 10: cout << "J" << endl; break;
		case 11: cout << "Q" << endl; break;
		case 12: cout << "K" << endl; break;
	}
	return 0;

}
