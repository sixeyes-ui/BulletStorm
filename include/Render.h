#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>

class Render
{
public:
	static void initialize(int width, int height);

	static void clear();

	static void setPixel(int x, int y, const sf::Color& color);
	static void loadTextures();

	static sf::Image& getScreen() { return _screen; }
	
	static void render(sf::RenderWindow* window);

private:
	static int _width;
	static int _height;

	static std::vector<sf::Uint8> _pixels;

	static sf::Texture _screenTexture;
	static sf::Sprite  _screenSprite;

	static sf::Image _wallTexture;
	static sf::Image _screen;
};

#endif // !RENDER_H
