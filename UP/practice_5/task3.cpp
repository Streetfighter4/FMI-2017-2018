#include <iostream>

using namespace std;

int main() {
	int num;
	cin >> num;
	if (num > 51 || num < 0) {
		cin >> num;
	}

	switch(num/13):
	case 0:
		cout << "spatiq" << endl;
		switch(num%13):
		case 0: cout << "A" << endl; break;
		case 1: cout << "A" << endl; break;
		case 2: cout << "A" << endl; break;
		case 3: cout << "A" << endl; break;
		case 4: cout << "A" << endl; break;
		case 5: cout << "A" << endl; break;
		case 6: cout << "A" << endl; break;
		case 7: cout << "A" << endl; break;	
		case 8: cout << "A" << endl; break;
		case 9: cout << "A" << endl; break;
		case 10: cout << "A" << endl; break;
		case 11: cout << "A" << endl; break;
		case 12: cout << "A" << endl; break;

		break;
	case 1:
		cout << "karo" << endl;
		break;
	case 2:
		cout << "kupa" << endl;
		break;
	case 3:
		cout << "pika"


	return 0;
}
