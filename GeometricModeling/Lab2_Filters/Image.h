#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

class Image
{
private:
	int imageWidth = 0;
	int imageHeight = 0;
	int imageChannels = 4;
	
	std::vector<uint8_t> pixels;

public:
	Image() = default;
	Image(int width, int height);

	int GetHeight() const { return imageHeight; }
	int GetWidth() const { return imageWidth; }

	uint8_t* GetPixelData(int x, int y);
	const uint8_t* getRawData() const { return pixels.data(); }
	int getChannels() const { return imageChannels; }

	bool SaveToFile(const std::string &filename) const;
	bool loadFromFile(const std::string& filename);
};