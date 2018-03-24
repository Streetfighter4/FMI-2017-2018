#include <iostream>
#include <fstream>
using namespace std;

int main() {
	int fn;
	char name[256];
	std::ofstream file("text.txt");
	cin.getline(name, 256);	
	cin >> fn;

	if(file.is_open()) {
		file << fn << endl;
		file << name << endl;
	} else
		return -1;


	file.close();

	return 0;
}
