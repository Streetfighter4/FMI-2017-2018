#include <iostream>
#include <cmath>

const int max_size = 80;

void initDict(unsigned short*& dict, size_t n) {
	dict = new(std::nothrow) unsigned short[n];

	for(int i = 0; i < n; ++i) {
		std::cin >> dict[i];
	}
}

bool isDig(const char c) {
	return ((c <= '9') && (c >= '0'));
}

unsigned atoi(const char* str) {
	unsigned res = 0;
	unsigned i = 0;
	while(isDig(*str)) {
		if(isDig(*str)) {	
			res *= 10;
			res += (*str - '0');
		}
		str++;
	}
	return res;
}

unsigned sumNumbers(const char* str, unsigned short*& dict, size_t n) {
	unsigned res = 0;	
	unsigned num = 0;
	while(*str != '\n') {
		if(isDig(*str)) {
			num = atoi(str);
			if(num > pow(2,16)) {
				str++;
				continue;
			}
			for(int i = 0; i < n; ++i) {
				if(num == dict[i]) {
					res += num;
					break;
				}
			}
		}
		str++;
	}
	return res;
}


int main() {
	size_t n;
	std::cin >> n;
	unsigned short* dict;
	initDict(dict, n);
	
	char buff[max_size];

	std::cin.ignore();
	std::cin.getline(buff, max_size);
	std::cout << "result: " << sumNumbers(buff, dict, n) << std::endl;	

	delete[] dict;
	return 0;
}
