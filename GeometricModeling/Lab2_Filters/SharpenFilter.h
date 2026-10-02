#pragma once

#include "KernelFilter.h"

class SharpenFilter : public KernelFilter
{
public:
	SharpenFilter()
	{
		scale = 1.0f;
		offset = 0.0f;

		kernel =
		{
			{0, -1, 0},
			{-1, 5, -1},
			{0, -1, 0}
		};
	}
};