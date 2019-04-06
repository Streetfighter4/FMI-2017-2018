#include<stdio.h>
#define MAX_N 2000000

unsigned long long int merge(int* array, size_t l, size_t mid, size_t h) {
	size_t n1 = mid - l + 1;
	size_t n2 = h - mid;
	int L[n1], R[n2];
	size_t i, j, k;

	for(i = 0; i < n1; ++i)
		L[i] = array[l+i];
	for (j = 0; j < n2; ++j)
		R[j] = array[mid+1+j];


	i = 0;
	j = 0;
	k = l;
	unsigned long long int c3 = 0;
	while((i < n1) && (j < n2)) {
		if(L[i] <= R[j]) {
			array[k++] = L[i++];
		} else {
	 		c3 += (n1-i);
			array[k++] = R[j++];
		}
	}
	while(i < n1) {
		array[k++] = L[i++];
	}
	while(j < n2) {
		array[k++] = R[j++];
	}

	return c3;
}

unsigned long long int permSwap(int* array, size_t l, size_t h) {
	unsigned long long int c1 = 0, c2 = 0, c3 = 0;
	if(l<h) {
		size_t mid = l+(h-l)/2;
		c1 = permSwap(array, l, mid);
		c2 = permSwap(array, mid+1, h);
		c3 = merge(array, l, mid, h);
	}

	return c1+c2+c3;
}

int main() {
	int array[MAX_N];
	int n;
	scanf("%d", &n);
	
	for(int i = 0; i < n; ++i) {
		scanf("%d", array+i);
	}
	unsigned long long int k = permSwap(array, 0, n-1);
	printf("%lld", k);
	return 0;
}
