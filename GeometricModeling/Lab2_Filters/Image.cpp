#include "Image.h"

Image::Image(int width, int height)
{
	imageWidth = width;
	imageHeight = height;

	pixels.resize(imageHeight * imageWidth * imageChannels);
}

uint8_t* Image::GetPixelData(int x, int y)
{
	if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
	{
		return nullptr;
	}

	int index = (y *  imageWidth + x) * imageChannels;

	return &pixels[index];
}