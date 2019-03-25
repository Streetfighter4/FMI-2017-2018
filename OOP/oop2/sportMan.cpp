#include <iostream>
#include <string.h>

#define MAX_N 1<<5;

struct SportMan {
	private:
		char name[MAX_N];
		char sport[MAX_N];
		unsigned int age;

	public:
		SportMan(const char* new_name, const char* new_name, 
				unsigned int new_age);

		const char* getName() const { return name; }
		inline const char* getSport() const { return sport; }
		inline int getAge() const { return age; }

		inline void introduce() const {
			std::cout << name << " " << sport << " " << age << std::endl;	
		}
		inline void play() const {
			//
		}
};

inline const char* SportMan::getName() const { return name; }
SportMan::SportMan(const char* new_name, const char* new_name, 
				unsigned int new_age) : age(new_age){
				strcpy(name, new_name);
				strcpy(sport, new_sport);
}

int main() {

	return 0;
}
