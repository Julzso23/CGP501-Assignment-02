#pragma once

#include "Vector2.hpp"
#include <vector>

namespace Utility
{
    // Split a string into an array of strings by a delimiter
	std::vector<std::string> split(std::string input, char delimiter);

    // Trim the leading and ending whitespace from a string
	std::string trim(std::string input);

    // Clamp a value between two other values
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

    // Return the sign (+/-) of a value
	template <typename T>
	T sign(T value)
	{
		if (value < 0)
		{
			return -1;
		}

		return 1;
	}

    // Return a linear interpolation between two values at time t (0-1)
	Vector2f lerp(const Vector2f& start, const Vector2f& end, float percent);
}