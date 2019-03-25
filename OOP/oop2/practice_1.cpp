#include <iostream>
#include <string.h>
#include <stdlib.h>

enum color { brown, green, orange, red, yellow };
enum yn { yes, no };

struct Fruit {
		char name[32];
		color cl;
		yn annual;
		yn perennial;
		yn tropical;
	public:	

		inline const char* getName() const { return name; }
		inline color getColor() const { return cl; }
		inline yn getAnnual() const { return annual; }
		inline yn getPerennial() const { return perennial; }
		inline yn getTropical() const { return tropical; }
};

int main() {
	
	Fruit array[5];
	for(int i = 0; i < 5; ++i) {
		strcpy(array[i].name, "fruit1");	
		array[i].cl = brown;
		array[i].annual = yes;
		array[i].perennial = no;
		array[i].tropical = no;
	}	

	for(int i = 0; i < 5; ++i) {	
		std::cout << array[i].getName();
		std::cout << array[i].getColor() << std::endl;
		std::cout << array[i].getAnnual() << std::endl;
		std::cout << array[i].getPerennial() << std::endl;
		std::cout << array[i].getTropical() << std::endl;
	}	

	return 0;
}
