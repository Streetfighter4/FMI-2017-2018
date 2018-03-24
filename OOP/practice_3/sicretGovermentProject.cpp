#include <iostream>
#include <fstream>
using namespace std;
enum School {
	SMG,
	NTBG,
	NFSG,
	IEG,
};


struct Student {
	char name[23];
	School school;
	double mark;
};

for(int i = 0; i < n; i+=3){
	cout << i << endl;

}

int main() {
	int option;
	while(true) {		
		cin >> option;
		switch(option) {
			case 1:
				cout << "New record!" << endl;
				break;
			case 2:
				cout << "Best student." << endl;
				break;
			case 3:
				cout << "Generate report.txt file." << endl;
				break;
			case 4:
				cout << "Increase marks in school." << endl;
				break;
			case 5:
				cout << "Exit" << endl;
				break;
		}
	}
	return 0;
}
