#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	unsigned int number;
	cout << "Enter your number" << endl;
	cin >> number;
	int fstbit = (number & 1); //fstbit is the first bit from your number
	int bit;
	int oldbit = fstbit;
	int sum = 0;
	int mask = 0;
	mask = 1010101010;
	int mask1 = 0;
	mask1 = 0101010101;
	int pownum = 0;
	int countb = 0;
	int sumwhole = 0;




	while (number > 0)
	{
		number = (number >> 1);
		bit = number & 1;

		if (oldbit == 1 && bit == 1)
		{
			while (number != 0 && oldbit == bit)
			{
				number >> 1;
				//cout << number << endl;
				bit = number & 1;
				sum =+ (bit*pow(10, pownum));
				pownum++;
				countb++;

			}
			sum = (sum & mask);
		}
		else {
			countb++;
		}

		if (oldbit == 0 && bit == 0)
		{
			while (number != 0 && oldbit == bit)
			{
				number >> 1;
				bit = number & 1;
				sum =+ (bit*pow(10, pownum));
				pownum++;
				countb++;
			}
			sum = (sum & mask1);
		}
		sumwhole =+ (sum * pow(10, countb));
		oldbit = bit;
	}

	cout << sumwhole << endl;
	return 0;
}
