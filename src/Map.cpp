#include "include/Map.h"

std::vector<std::string> Map::_map;

Map::Map() 
{

}

void Map::init()
{
	_map =
	{
		"#################",
		"#...............#",
		"#.....##.....####",
		"#...............#",
		"#...............#",
		"#.........##....#",
		"#...............#",
		"#....#####......#",
		"#...............#",
		"#...............#",
		"#...............#",
		"#....###....#####",
		"#...............#",
		"#...............#",
		"#...............#",
		"#################"
	};
}

bool Map::isFloor(int mapX, int mapY)
{
	bool res = false;
	if (_map[mapY][mapX] == '.')
		res = true;
	else
		res = false;

	return res;
}

bool Map::isWall(int mapX, int mapY)
{
	bool res = false;
	if (_map[mapY][mapX] == '#')
		res = true;
	else
		res = false;

	return res;
}