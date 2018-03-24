#include <iostream>

using namespace std;

int num;

void function(int n, int* arr) {
	if(n == 0) return;
	for(int i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	arr[0] += arr[1];
	function(n-1, arr);
	int* arr2 = new int[num - n];
	for(int i = 0; i < num - n; ++i)
		arr2[i] = 1;
	function(n, arr2);
}

int main() {
	int *arr = new int[5];	
	num = 5;
	for(int i = 0; i < 5; ++i) {
		arr[i] = 1;
	}
	function(5, arr);


	return 0;
}
