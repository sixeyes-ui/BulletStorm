#include "include/Render.h"

int Render::_width;
int Render::_height;

std::vector<sf::Uint8> Render::_pixels;

sf::Texture Render::_screenTexture;
sf::Sprite  Render::_screenSprite;

sf::Image Render::_wallTexture;
sf::Image Render::_screen;

void Render::initialize(int width, int height)
{
	_width = width;
	_height = height;

	_pixels.resize(width * height * 4);

	_screenTexture.create(width, height);

	_screenTexture.setSmooth(false);

	_screenSprite.setTexture(_screenTexture);
}

void Render::loadTextures()
{
	_screenTexture.update(_pixels.data());
}

void Render::clear()
{
	std::fill(_pixels.begin(), _pixels.end(), 0);

	for (int i = 3; i < _width * _height * 4; i += 4)
	{
		_pixels[i] = 255;
	}
}

void Render::setPixel(int x, int y, const sf::Color& color)
{
	if (x < 0 || x >= _width ||
		y < 0 || y >= _height)
		return;

	int index = (y * _width + x) * 4;

	_pixels[index] = color.r;
	_pixels[index + 1] = color.g;
	_pixels[index + 2] = color.b;
	_pixels[index + 3] = color.a;
}

void Render::render(sf::RenderWindow* window)
{
	window->draw(_screenSprite);
}