#pragma once

#include "KernelFilter.h"

class EmbossFilter : public KernelFilter
{
public:
	EmbossFilter()
	{
		scale = 1.0f;
		offset = 128.0f;

		kernel =
		{
			{-1, -1, 0},
			{-1, 1, 1},
			{0, 1, 1}
		};
	}
};