#include <stdio.h>
#include <iostream>
#include <stack>
#include <math.h>
#include <iomanip>

int main() {
	std::stack<unsigned> s;
	unsigned num;
	while(std::cin >> num) {
		s.push(num);
	}

	while(!s.empty()) {
		printf("%lf\n", sqrt(s.top()));
		s.pop();
	}

	return 0;
}
