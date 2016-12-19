#pragma once

#include "Vector2.hpp"
#include <vector>

namespace Utility
{
	std::vector<std::string> split(std::string input, char delimiter);
	std::string trim(std::string input);

	template <typename T>
	T clamp(T value, T minimum, T maximum)
	{
		if (value < minimum)
		{
			return minimum;
		}

		if (value > maximum)
		{
			return maximum;
		}

		return value;
	}

	template <typename T>
	T sign(T value)
	{
		if (value < 0)
		{
			return -1;
		}

		return 1;
	}

	Vector2f lerp(const Vector2f& start, const Vector2f& end, float percent);
}