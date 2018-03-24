#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct Student {
	char* name;
	unsigned int fn;
} yasen = {"Yasen Alexiev", 45460};


int main() {
	//int n;
	//cin >> n;
	ofstream sFile ("students.bin", ios::binary);
	if(!sFile.is_open()) {
		return -1;
	}
	sFile.write((const char*)&yasen.name, strlen(yasen.name));
	sFile.write((const char*)&yasen.fn, sizeof(unsigned int));
	sFile.close();
	return 0;
}
