#include <iostream>
using namespace std;

void mySort(int *arr, size_t size){
	int elementToBeSwaped;
	for (int i = 0; i < size-1; ++i) {
		elementToBeSwaped = i;
		for (int j = i+1; j < size; ++j) {
			if (arr[j] < arr[elementToBeSwaped]) {
				elementToBeSwaped = j;	
			}
		}
		std::swap(arr[i], arr[elementToBeSwaped]);
	}
}

	// 3 2 1
	// 8
	// 3 3 2
	// 3 3 1 1
	// 3 2 2 1
	// 3 2 1 1 1
	// 3 1 1 1 1 1
	// 2 2 2 2
	// 2 2 2 1 1
	// 2 2 1 1 1 1
	// 2 1 1 1 1 1 1
	// 1 1 1 1 1 1 1 1

void waysToPayRecursive(int *arr, size_t size, size_t rest, int& counter, int pos, int depth) {
		

		if(rest == 0) {
			++counter;
			
			std::cout << std::endl;
			return;
		}
	/*

*/
		if(rest < arr[size-1]) {
			return;
		}

		while (rest >= arr[pos]) {
			std::cout << arr[pos] << ' ';
			rest -= arr[pos];
		}
		std::cout << "depth: " << depth << std::endl;
		std::cout << "rest: " << rest << std::endl;
		waysToPayRecursive(arr, size, rest, counter, pos+1, depth+1);
		
		if(!(depth == 1 && arr[pos] == arr[size-1])) {
			waysToPayRecursive(arr, size, rest, counter, pos+1, depth+1);
		}
}
int waysToPay(int *arr, size_t size, size_t rest) {
	int counter = 0;
	int tempSum = 0;	
	int sum = 0;
	for(int i = 0; i < size; ++i) {
		tempSum = 0;
		while(tempSum < rest) {
		
			while (sum <= rest)
				sum += arr[i];

			if(sum == rest)	{
				++counter;
			}

			while(sum >= rest-arr[i+1]) {
				tempSum += arr[i+1];
				sum -= arr[i];
			}

		}
	}
	return counter;
}

int main() {
	unsigned int m;
	unsigned int n;
	cin >> m >> n;
	int *arr = new(nothrow) int[n];
	if (arr != NULL) {
		for (int i = 0; i < n; ++i) {
			cin >> arr[i];
		}
		mySort(arr, n);
		for(int i = 0; i < n; ++i) {
			std::cout << arr[i] << ' ';
		}
		std::cout << std::endl;

		cout << waysToPay(arr, n, m) << endl;;
	}



	delete[] arr;
	return 0;
}
