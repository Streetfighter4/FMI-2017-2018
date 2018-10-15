#include <stdio.h>

const size_t maxSize = 5;

void rotation(int arr[], int movement) {
		
}

int main() {
	int arr[maxSize];
	for(size_t i = 0; i < maxSize; ++i) {
		cin >> arr[i];
	}

	int movement;
	cin >> movement;
	rotation(arr, movement);

	return 0;
}
