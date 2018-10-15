#include <stdio.h>
typedef enum { false, true } bool;
#define MAXN 30000

const unsigned n = 200;
bool sieve[MAXN];

void eratosten(unsigned n) {
	unsigned i = 2, j = 2;
	while(i <= n) {	
		if(sieve[i] == false) {
			//printf("    %d", i);
			j = i*i;
			while(j <= n) {
				sieve[j] = true;
				j += i;
			}
		}
		i++;
	}
}


int main() {
	unsigned i;
	for(i = 0; i < n; ++i){
		sieve[i] = false;
	}

	eratosten(n);	
	return 0;
}
