#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>

class Texture
{
public:
	Texture() = delete;

	static bool init();

	static bool loadWallTexture(const std::string& filename);
	static bool loadFloorTexture(const std::string& filename);

	static void setWallPixel(int wallHeight, int wallWidth, int wallTop, float wallX, int ray);
	static void setFloorPixel(int x, int y, int texX, int texY);

	//static void createWallTexture();
	//static void createFloorTexture();

	//static void setWallPixel(int wallHeight, int wallWidth, int wallTop, float wallX, int ray);
	static void setCeilingPixel(int x, int y, const sf::Color& color);
	//static void setFloorPixel(int x, int y, int texX, int texY);

private:
	static sf::Image _wallTexture;
	static sf::Image _floorTexture;

};

#endif // !TEXTURE_H
