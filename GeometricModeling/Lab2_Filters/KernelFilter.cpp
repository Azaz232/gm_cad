#include <algorithm>

#include "KernelFilter.h"

void KernelFilter::Apply(Image &image)
{
	int height = image.GetHeight();
	int width = image.GetWidth();

	Image sourseImage = image;

	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height -1 ; y++)
		{
			float sumR = 0.0f;
			float sumG = 0.0f;
			float sumB = 0.0f;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					uint8_t *p = sourseImage.GetPixelData(x + i, y + j);
					sumR += p[0] * kernel[i + 1][j + 1];
					sumG += p[1] * kernel[i + 1][j + 1];
					sumB += p[2] * kernel[i + 1][j + 1];
				}
			}

			sumR = (sumR / scale) + offset;
			sumG = (sumG / scale) + offset;
			sumB = (sumB / scale) + offset;

			sumR = std::clamp(sumR, 0.0f, 255.0f);
			sumG = std::clamp(sumG, 0.0f, 255.0f);
			sumB = std::clamp(sumB, 0.0f, 255.0f);

			uint8_t* resultPixel = image.GetPixelData(x, y);

			resultPixel[0] = static_cast<uint8_t>(sumR);
			resultPixel[1] = static_cast<uint8_t>(sumG);
			resultPixel[2] = static_cast<uint8_t>(sumB);
		}
	}
}