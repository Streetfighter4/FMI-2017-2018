#include <stdio.h>
#include <algorithm>
#include <queue>
#define MAX_N 10000

int main() {
	int N, M, K;
	std::priority_queue<int, std::vector<int>, std::greater<int> > q;
	
	scanf("%i %i %i", &N, &M, &K);

	int prev, current;
	scanf("%i", &prev);
	if(N == 1) {
		q.push(prev);
	}
	for(int i = 0; i < N-1; ++i) {
		scanf("%i", &current);
		q.push(current - prev);
		prev = current;
	}

	int lenght = N;	
	int i = 0;
	while(!q.empty() && i < N-K) {
		lenght += q.top()-1;
		q.pop();
		++i;
	}
	printf("%d", lenght);
	return 0;
}





