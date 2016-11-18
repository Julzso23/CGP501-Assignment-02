#include "Level.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Level::Level(std::string fileName)
{
	std::ifstream file;
	file.open("resources/levels/" + fileName);
	/*std::stringstream mapData;
	mapData << file.rdbuf();*/

	char tileType;
	while (file >> std::noskipws >> tileType)
	{
		/*if (tileType != 178 && tileType != ' ')
		{
			std::cout << (int)tileType;
		}
		else
		{
			std::cout << tileType;
		}*/
		std::cout << tileType;
	}

	file.close();
	//std::cout << mapData.str() << std::endl;
}
