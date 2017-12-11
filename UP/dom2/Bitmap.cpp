#include "Bitmap.h"

#include <iostream>
using namespace std;

int main()
{
	const size_t MAX_SIZE = 100000; // Можете да промените този размер,
									// според това с колко големи
									// изображения искате да работите 

	unsigned int width, height, image[MAX_SIZE];

	int rval;

	// В последните три параметъра, функцията връща изображението и
	// размерите му
	rval = LoadBitmap("test.bmp", image, MAX_SIZE, width, height);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot load image data from test.bmp! Error code " << rval << "\n";
		return 1;
	}
	unsigned int background;
	cin >> background;
	
	int upRow = -1;
	int downRow = -1;
	int leftCol = width + 1;
	int rightCol = -1;

	int i = 0;
	int j = 0;
	for(int k = 0; k < width*height; k++) {
		bool diffPixel = (image[k] != background);
		if (diffPixel && (upRow == -1)) {
			upRow = i;		
		}
		if (diffPixel && (j < leftCol)) {
			leftCol = j;
		}
		if (diffPixel && (j > rightCol)) {
			rightCol = j;
		}
		if (diffPixel && (i > downRow)) {
			downRow = i;
		}
		j++;
		if (!(j%width)) {
			j = 0;
			i++;
		}
	}

	cout << "upRow: " << upRow << endl;
	cout << "downRow: " << downRow << endl;
	cout << "leftCol: " << leftCol << endl;
	cout << "rightCol: " << rightCol << endl;
	int newWidth = rightCol - leftCol + 1;
	int newHeight = downRow - upRow + 1;
	
	for(int i = 0, k = upRow; i < newWidth; i++, k++) {
		for(int j = 0, p = leftCol; j < newHeight; j++, p++) {
			int currPos = i*newWidth + j;
			int prevPos = k*width + p;
			image[currPos] = image[prevPos];
		}
		
	}
	
	// Тук можете да добавите код, който решава задачата
	// Препоръчваме да разбиете решението си в една или повече подходящи функции
	// и тук да направите подходящи обръщения към тях.


	// По-долу предполагаме, че резултата от обработката е записан отново в масива image
	// и че width и height са променени така, че да съдържат размера на изрязаното изображение
	rval = SaveBitmap("test_new.bmp", image, newWidth, newHeight);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot save image data to test_new.bmp! Error code " << rval << "\n";
		return 2;
	}

    return 0;
}

