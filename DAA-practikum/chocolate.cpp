#include<stdio.h>

struct Date {
	int d;
	int m;
	int y;
	int index;
};

bool largestDate(Date& d1, Date& d2) {
	if(d1.y > d2.y) {
		return true;
	} else if(d1.y == d2.y) {
		if(d1.m > d2.m) {
			return true;
		} else if(d1.m == d2.m) {
			if(d1.d > d2.d)	{
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void sort(Date* array, int n) {
	Date key;
	for(int i = 1; i < n; ++i) {
		int j = i - 1;
		key = array[i];
		while(j >= 0 && largestDate(array[j], key)) {
			array[j+1] = array[j];
			--j;
		}
		array[j+1] = key;
	}	
}


#define MAX_N 100

int main () {
	int n;
	scanf("%d", &n);
	Date array[MAX_N];

	for(int i = 0; i < n; ++i) {
		scanf("%d.%d.%d", &array[i].d, &array[i].m, &array[i].y);
		array[i].index = i+1;
	}
	sort(array, n);
	for(int i = 0; i < n; ++i) {
		printf("%d\n", array[i].index);
	}

}
