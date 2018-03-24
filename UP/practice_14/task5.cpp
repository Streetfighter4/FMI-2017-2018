#include <iostream>

using namespace std;

typedef unsigned int u_int;

u_int max_num;

void partition(u_int shift, u_int n, u_int* arr) {
	if(n == 0) return;
	else {
		for(u_int i = shift; i < n; ++i)
			cout << arr[i] << " ";

		cout << endl;
		arr[0] += arr[1];
		partition(shift, n-1, arr);
		partition(shift+1, n-1, arr);	
	}

}

int main() {
	u_int n;
	cin >> n;
	max_num = n;
	u_int* arr = new u_int[n];
	for(u_int i = 0; i < n; ++i)
		arr[i] = 1;

	partition(0, n, arr);	
	delete[] arr;
	return 0;
}
