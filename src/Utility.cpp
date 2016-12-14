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
}