#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Map
{
public:
	Map();
	static void init();
	//static void render(sf::RenderWindow* window);

	static bool isFloor(int mapX, int mapY);
	static bool isWall(int mapX, int mapY);
	static int  getWidth()  { return _map[0].size(); }
	static int  getHeight() { return _map.size(); }

private:
	static std::vector<std::string> _map;
};

#endif // !MAP_H
