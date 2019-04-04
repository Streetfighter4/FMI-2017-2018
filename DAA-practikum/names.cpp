#include <stdio.h>
#include <string.h>
#include <iostream>
#define MAX_N 50000
int main () {
	char array[MAX_N*2];	
	int indexes[MAX_N];
	int N;
	scanf("%d", &N);
	char buff[50];
	int index = 0;
	for(int i = 0; i < N; ++i) {
		scanf("%s", buff);
		strcpy(array+index, buff);
		indexes[i] = index;
		index += strlen(buff)+1;
		memset(buff, 0, 50);
	}
	for(int i = 0; i < N; ++i) {
		printf("%s", array[i]);
	}
/*	
	int minIndex;
	for(int i = 0; i < N-1; ++i) {
		minIndex = i;
		for(int j = i + 1; j < N; ++j) {
			if(strcmp(array[j], array[minIndex]) < 0) {
				minIndex = j;
			}
		}
		std::swap(array[i], array[minIndex]);
	}

	for(int i = 0; i < N; ++i) {
		printf("%s", array[i]);
	}
	
	for(int i = 0; i < N; ++i) {
		delete[] array[i];	
	}
	delete[] array;	
*/
	return 0;
}
