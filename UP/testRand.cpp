#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	int luck = 150;
	float chance_for_crit = luck*0.5;
	bool p_hit_crit;
	srand(time(NULL));
	
	for(int i = 0; i < 50; i++) {
		p_hit_crit = ((rand()%100) <= (int)chance_for_crit) ? true : false;
		cout << p_hit_crit;
	}

	return 0;
}
