#define _CRT_SECURE_NO_WARNINGS

#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <windows.h>

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

static void my_stb_write_callback(void* context, void* data, int size)
{
	fwrite(data, 1, size, (FILE*)context);
}

bool Image::SaveToFile(const std::string& filename) const
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), (int)filename.length(), NULL, 0);

	std::wstring wfilename(size_needed, 0);

	MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), (int)filename.length(), wfilename.data(), size_needed);

	FILE* f = _wfopen(wfilename.c_str(), L"wb");
	if (!f)
	{
		return false;
	}

	int result = stbi_write_png_to_func(my_stb_write_callback, f, imageWidth, imageHeight, imageChannels, pixels.data(), imageWidth * imageChannels);

	fclose(f);
	return result != 0;
}

bool Image::loadFromFile(const std::string& filename)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), (int)filename.length(), NULL, 0);
	std::wstring wfilename(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), (int)filename.length(), &wfilename[0], size_needed);

	FILE* f = _wfopen(wfilename.c_str(), L"rb");
	if (!f)
	{
		return false;
	}

	int widthOnDisk = 0;
	int heightOnDisk = 0;
	int channelsOnDisk = 0;

	unsigned char* data = stbi_load_from_file(f, &widthOnDisk, &heightOnDisk, &channelsOnDisk, STBI_rgb_alpha);

	fclose(f);

	if (data == nullptr)
	{
		return false;
	}

	imageWidth = widthOnDisk;
	imageHeight = heightOnDisk;
	imageChannels = 4;

	size_t totalBytes = imageWidth * imageHeight * imageChannels;
	pixels.assign(data, data + totalBytes);
	stbi_image_free(data);

	return true;
}
