#include <stdio.h>
#include <iostream>
#define MAX_N 100000

int partition(int* array, int l, int h) {
	int pivot = array[h];

	int i = l-1;

	for(int j = l; j < h; ++j){
		if(array[j] < pivot) {
			++i;
			std::swap(array[i], array[j]);
		}
	}
	std::swap(array[i+1], array[h]);
	return i+1;
}

void quickSort(int* array, int l, int h) {
	if(l<h) {	
		int pivot = partition(array, l, h);
		quickSort(array, l, pivot-1);
		quickSort(array, pivot+1, h);
	}
}


int main() {
	int array[MAX_N];
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		scanf("%d", array+i);
	}
	
	quickSort(array, 0, n-1);

	for(int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}

	return 0;
}
