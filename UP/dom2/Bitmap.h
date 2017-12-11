#pragma once

#include <fstream>
#include <cerrno>

#define ALL_OK						0
#define ERR_CANNOT_OPEN_FILE		1
#define ERR_WRONG_FILE_TYPE			2
#define ERR_BUFFER_TOO_SMALL		3
#define ERR_FILE_READ_ERROR			4
#define ERR_CANNOT_ALLOCATE_MEMORY	5
#define ERR_ZERO_SIZE				6

inline int LoadBitmap(const char* Path, unsigned int ImageData[], size_t MaxSize, unsigned int& Width, unsigned int& Height)
{
	std::ifstream in(Path, std::ios::binary | std::ios::in);

	if (!in.is_open())
		return ERR_CANNOT_OPEN_FILE;

	uint16_t buffer16;
	uint32_t buffer32;

	// Verify that the file begins with a BM signature
	in.read(reinterpret_cast<char*>(&buffer16), 2);

	if (!in || buffer16 != 0x4D42)
		return ERR_WRONG_FILE_TYPE;

	// Find the offset to the image data
	uint32_t imageDataOffset;

	in.seekg(10, std::ios::beg);
	in.read(reinterpret_cast<char*>(&imageDataOffset), 4);

	// Retrieve the dimensions of the image
	uint32_t imageWidth, imageHeight;

	in.seekg(18, std::ios::beg);
	in.read(reinterpret_cast<char*>(&imageWidth), 4);
	in.read(reinterpret_cast<char*>(&imageHeight), 4);

	// Verify the image data will fit into the buffer
	if (imageWidth * imageHeight > MaxSize)
		return ERR_BUFFER_TOO_SMALL;

	// Verify the image contains just one plane
	in.seekg(26, std::ios::beg);
	in.read(reinterpret_cast<char*>(&buffer16), 2);

	if (buffer16 != 1)
		return ERR_WRONG_FILE_TYPE;

	// Verify the image is 24-bit bitmap
	in.read(reinterpret_cast<char*>(&buffer16), 2);

	if (buffer16 != 24)
		return ERR_WRONG_FILE_TYPE;

	// Verify the image is not compressed
	in.read(reinterpret_cast<char*>(&buffer32), 4);

	if (buffer32 != 0)
		return ERR_WRONG_FILE_TYPE;

	// Go to the image data and load it in the array
	in.seekg(imageDataOffset, std::ios::beg);

	uint8_t red, green, blue;
	int padding = (4 - (imageWidth * 3) % 4) % 4; // rows are aligned on a 4-byte boundary

	for (uint32_t row = 0; row < imageHeight; ++row)
	{
		uint32_t rowOffset = (imageHeight - row - 1) * imageWidth;

		for (uint32_t column = 0; column < imageWidth; ++column)
		{
			in.read(reinterpret_cast<char*>(&blue), 1);
			in.read(reinterpret_cast<char*>(&green), 1);
			in.read(reinterpret_cast<char*>(&red), 1);

			if (!in.good())
				return ERR_FILE_READ_ERROR;

			ImageData[rowOffset + column] = 0xFF << 24 | red << 16 | green << 8 | blue;
		}

		// jump over the padding (if any)
		in.seekg(padding, std::ios::cur);
	}	

	// Return the dimensions of the image
	Width = imageWidth;
	Height = imageHeight;

	return ALL_OK;
}

inline int SaveBitmap(const char* Path, unsigned int ImageData[], unsigned int Width, unsigned int Height)
{
	if (Width == 0 || Height == 0)
		return ERR_ZERO_SIZE;

	// Allocate a buffer to store the data of one row in the bitmap
	int rowPadding = (4 - (Width * 3) % 4) % 4; // rows are aligned on a 4-byte boundary
	int rowSizeWithPadding = Width * 3 + rowPadding;
	uint8_t *pRowData = NULL;

	try
	{
		pRowData = new uint8_t[rowSizeWithPadding];
	}
	catch (std::bad_alloc&)
	{
		return ERR_CANNOT_ALLOCATE_MEMORY;
	}

	// Open the output file for writing and truncate its contents if it already exists
	std::ofstream out(Path, std::ios::binary | std::ios::out | std::ios::trunc);

	if (!out.is_open())
		return ERR_CANNOT_OPEN_FILE;


	// Output the bitmap file header information
	uint16_t bitmapFileHeader[] = {
		0x4D42, // bitmap signature (type). Should be BM
		0x0000, 0x0000, // size in bytes of the file (32-bit), unreliable, can be set to 0
		0x0000, // reserved, should be 0
		0x0000, // reserved, should be 0
		0x0036, 0x0000 // offset to image data as a 32-bit integer. will be filled later, before writing to file
	};

	uint32_t bitmapInfoHeader[] = {
		0x00000028, // size of the BITMAPINFOHEADER structure
		Width, // width of the image, will be filled later
		Height, // height of the image, will be filled later
		0x00180001, // planes count (1) and bitcount (24) of the image, two 16-bit values
		0x00000000, // compression type, 0 for none
		0x00000000, // size in bytes of the image, can be set to 0, as we are not using compression
		0x00000000, 0x00000000, // pixels per meter on the X and Y axes, respectively
		0x00000000, // number of color indexes in the color table
		0x00000000  // number of important color indexes
	};

	out.write(reinterpret_cast<const char*>(bitmapFileHeader), 14);
	out.write(reinterpret_cast<const char*>(bitmapInfoHeader), 40);


	// Otput the image data
	for (uint32_t row = 0; row < Height; ++row)
	{
		int rowDataIndex = 0;
		int imageDataIndex = (Height - row - 1) * Width;

		for (uint32_t column = 0; column < Width; ++column)
		{
			pRowData[rowDataIndex++] = ImageData[imageDataIndex] & 0xFF;
			pRowData[rowDataIndex++] = (ImageData[imageDataIndex] >> 8) & 0xFF;
			pRowData[rowDataIndex++] = (ImageData[imageDataIndex] >> 16) & 0xFF;
			++imageDataIndex;
		}

		while (rowDataIndex < rowSizeWithPadding)
			pRowData[rowDataIndex++] = 0;

		out.write(reinterpret_cast<const char*>(pRowData), rowSizeWithPadding);
	}

	return ALL_OK;
}
