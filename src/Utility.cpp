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
		const std::size_t start = input.find_first_not_of(" \t");

		if (start == std::string::npos)
		{
			return "";
		}

		const std::size_t end = input.find_last_not_of(" \t");
		const std::size_t range = end - start + 1;

		return input.substr(start, range);
	}
}