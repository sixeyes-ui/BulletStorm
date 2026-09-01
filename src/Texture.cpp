#include "include/Texture.h"
#include "include/Config.h"
#include "include/Render.h"
#include <cmath>
#include <iostream>

sf::Image Texture::_wallTexture;
sf::Image Texture::_floorTexture;

bool Texture::init()
{
	bool wallLoaded = loadWallTexture("assets/wall.png");
	bool floorLoaded = loadFloorTexture("assets/ground.png");

	return wallLoaded && floorLoaded;
	//createFloorTexture();
	//createWallTexture();
}

bool Texture::loadWallTexture(const std::string& filename)
{
	if (!_wallTexture.loadFromFile(filename))
	{
		std::cout << "Failed to load wall texture : " << filename << std::endl;

		return false;
	}

	return true;
}

bool Texture::loadFloorTexture(const std::string& filename)
{
	if (!_floorTexture.loadFromFile(filename))
	{
		std::cout << "Failed to load floor texture : " << filename << std::endl;

		return false;
	}

	return true;
}

void Texture::setFloorPixel(int x, int y, int texX, int texY)
{
	sf::Vector2u size = _floorTexture.getSize();

	if (size.x == 0 || size.y == 0)
		return;

	texX %= static_cast<int>(size.x);
	texY %= static_cast<int>(size.y);

	if (texX < 0)
		texX += size.x;

	if (texY < 0)
		texY += size.y;

	Render::setPixel(x, y, _floorTexture.getPixel(texX, texY));
}

void Texture::setWallPixel(int wallHeight, int wallWidth, int wallTop, float wallX, int ray)
{
	sf::Vector2u textureSize = _wallTexture.getSize();

	if (textureSize.x == 0 ||
		textureSize.y == 0)
	{
		return;
	}

	int texX = static_cast<int>(wallX * textureSize.x);

	if (texX >= static_cast<int>(textureSize.x))
		texX = textureSize.x - 1;

	if (texX < 0)
		texX = 0;

	//int startX = static_cast<int>(ray * wallWidth);
	int startX = static_cast<int>(ray * wallWidth);
	int endX = static_cast<int>(ray + 1) * wallWidth;

	for (int y = 0; y < wallHeight; y++)
	{
		int screenY =
			wallTop + y;

		if (screenY < 0 ||
			screenY >= SCREEN_HEIGHT)
		{
			continue;
		}


		float texturePosition =
			static_cast<float>(y) /
			static_cast<float>(wallHeight);

		int texY =
			static_cast<int>(
				texturePosition *
				textureSize.y
				);

		if (texY >= static_cast<int>(textureSize.y))
			texY = textureSize.y - 1;


		sf::Color pixel =
			_wallTexture.getPixel(texX, texY);


		for (int x = startX; x < endX; x++)
		{
			Render::setPixel(
				x,
				screenY,
				pixel
			);
		}
	}
}

//void Texture::createWallTexture()
//{
//	_wallTexture.create(32, 32);
//
//	for (unsigned int y = 0; y < _wallTexture.getSize().y; y++)
//	{
//		for (unsigned int x = 0; x < _wallTexture.getSize().x; x++)
//		{
//			if ((x / 4 + y / 4) % 2 == 0)
//				_wallTexture.setPixel(x, y, sf::Color::White);
//			else
//				_wallTexture.setPixel(x, y, sf::Color(100, 100, 100));
//		}
//	}
//}

//void Texture::createFloorTexture()
//{
//	_floorTexture.create(32, 32);
//
//	for (unsigned int y = 0; y < _floorTexture.getSize().y; y++)
//	{
//		for (unsigned int x = 0; x < _floorTexture.getSize().x; x++)
//		{
//			if ((x / 4 + y / 4) % 2 == 0)
//				_floorTexture.setPixel(x, y, sf::Color(80, 120, 80));
//			else
//				_floorTexture.setPixel(x, y, sf::Color(60, 90, 60));
//		}
//	}
//}

//void Texture::setFloorPixel(int x, int y, int texX, int texY)
//{
//	sf::Color pixel = _floorTexture.getPixel(texX, texY);
//	Render::setPixel(x, y, pixel);
//}

void Texture::setCeilingPixel(int x, int y, const sf::Color& color)
{
	Render::setPixel(x, y, color);
}

//void Texture::setWallPixel(int wallHeight, int wallWidth, int wallTop, float wallX, int ray)
//{
//	int textureX = static_cast<int>(wallX * 32);
//
//	for (int y = 0; y < wallHeight; y++)
//	{
//		int screenY = static_cast<int>(wallTop + y);
//
//		if (screenY < 0 || screenY >= SCREEN_HEIGHT)
//			continue;
//
//		float textureY = static_cast<float>(y) / wallHeight;
//
//		int texY = static_cast<int>(textureY * 32);

//		if (texY < 0)
//			texY = 0;

//		if (texY >= 32)
//			texY = 31;

//		sf::Color pixel = _wallTexture.getPixel(textureX, texY);
//
//		int startX = static_cast<int>(ray * wallWidth);
//		int endX = static_cast<int> ((ray + 1) * wallWidth);

//		for (int x = startX; x < endX; x++)
//		{
//			if (x >= 0 && x < SCREEN_WIDTH)
//			{
//				Render::setPixel(x, screenY, pixel);
//			}
//		}
//	}
//}