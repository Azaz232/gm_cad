#pragma once

#include "Image.h"

#include <vector>

class KernelFilter
{
public:
	void Apply(Image &image);
	virtual ~KernelFilter() = default;
private:

protected:
	std::vector<std::vector<float>> kernel;
	float scale = 1.0f;
	float offset = 0.0f;
};