#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
const int MAXN = 1024;
int main() {
	ifstream file("self_print.cpp");
		
	if(!file.is_open()) {
		cout << "File is not open!" << endl;
		return -1;
	}
	char c;	
	while(!file.eof()) {
		file.get(c);
		if(file) {
			cout << c;
		}
	}

	file.close();

	return 0;
}
