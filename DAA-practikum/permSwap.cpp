#include<stdio.h>
#define MAX_N 2000000

int merge(int* array, int l, int mid, int h) {
	int n1 = mid - l + 1;
	int n2 = h - mid;
	int L[n1], R[n2];

	int i, j, k;
	for(i = 0; i < n1; ++i){
		L[i] = array[l+i];
	}	
	for(j = 0; j < n2; ++j){
		R[j] = array[mid+1+j];
	}
	i = 0;
	j = 0;
	k = l;
	int c3 = 0;
	for(k = l; k <= h; ++k) {
		if(L[i] <= R[j]) {
			array[k] = L[i++];
		} else {
			c3 += n1+1-i;
			array[k] = R[j++];
		}	
	}
	return c3;	
}

int permSwap(int* array, int l, int h) {
	int c1 = 0, c2 = 0, c3 = 0;
	if(l<h) {
		int mid = l+(h-l)/2;
		c1 = permSwap(array, l, mid-1);
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

	printf("%d", permSwap(array, 0, n-1));

	return 0;
}
