#include "Utility.hpp"
#include <sstream>

namespace Utility
{
	std::vector<std::string> split(std::string input, char delimiter)
	{
		std::stringstream stream(input);

		std::string item;
		std::vector<std::string> output;
		while (std::getline(stream, item, delimiter))
		{
			output.push_back(item);
		}
		return output;
	}

	std::string trim(std::string input)
	{
        // Find the first character that wasn't whitespace
		const std::size_t start = input.find_first_not_of(" \t");

        // If the whole string was whitespace
		if (start == std::string::npos)
		{
			return "";
		}

        // Find the last character that wasn't whitespace
		const std::size_t end = input.find_last_not_of(" \t");
		const std::size_t range = end - start + 1;

        // Cut the whitespace from the string
		return input.substr(start, range);
	}

	Vector2f lerp(const Vector2f& start, const Vector2f& end, float percent)
	{
		return start + (end - start) * percent;
	}
}