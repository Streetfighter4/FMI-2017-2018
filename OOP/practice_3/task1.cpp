#include <iostream>
#include <fstream>

using namespace std;

int main() {

	ofstream file ("numbers.bin", std::ios::binary);
	
	if(!file.is_open()) {
		return -1;
	}
	
	int n;
	cin >> n;
	int number;
	for(int i = 0; i < n; ++i) {
		cin >> number;
		file.write((const char*)&number, sizeof(int));
	}
	file.close();	
	ifstream file1 ("numbers.bin", std::ios::binary);
	int count = 1;
	number = 0;
	while(!file1.eof()) {	
		file1.read((char*)&number, sizeof(int));
		
		if(count%3 == 0)
			cout << number;
		
		count++;	
	}

	
	file1.close();
	
	return 0;
}
