#include "include/Player.h"
#include "include/Config.h"
#include "include/Map.h"
#include "include/Render.h"
#include <iostream>

Player::Player(const Vec2& coord) :
	_coord(coord),
	_angle(0),
	_pitch(0.f)
{
	_player.setPosition(_coord.x, _coord.y);
}

void Player::handleMouse(float mouseDeltaX, float mouseDeltaY)
{
	const float mouseSensitivity = 0.003f;

	_angle += mouseDeltaX * mouseSensitivity;
	_pitch -= mouseDeltaY * mouseSensitivity * 100.f;

	const float maxPitch = 500.f;

	if (_pitch > maxPitch)
		_pitch = maxPitch;

	if (_pitch < -maxPitch)
		_pitch = -maxPitch;
}

void Player::update(float deltaTime)
{
	float speed = 200.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//_coord.x += std::cos(_angle) * speed * deltaTime;
		//_coord.y += std::sin(_angle) * speed * deltaTime;

		float newX = _coord.x + std::cos(_angle) * speed * deltaTime;
		float newY = _coord.y + std::sin(_angle) * speed * deltaTime;

		int mapX = static_cast<int>(newX / 32);
		int mapY = static_cast<int>(newY / 32);

		if (mapX >= 0 && mapX < Map::getWidth() &&
			mapY >= 0 && mapY < Map::getHeight() &&
			!Map::isWall(mapX, mapY))
		{
			_coord.x = newX;
			_coord.y = newY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//_coord.x -= std::cos(_angle) * speed * deltaTime;
		//_coord.y -= std::sin(_angle) * speed * deltaTime;

		float newX = _coord.x - std::cos(_angle) * speed * deltaTime;
		float newY = _coord.y - std::sin(_angle) * speed * deltaTime;

		int mapX = static_cast<int>(newX / 32);
		int mapY = static_cast<int>(newY / 32);

		if (mapX >= 0 && mapX < Map::getWidth() &&
			mapY >= 0 && mapY < Map::getHeight() &&
			!Map::isWall(mapX, mapY))
		{
			_coord.x = newX;
			_coord.y = newY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		float newX = _coord.x + std::cos(_angle + PI / 2.f);
		float newY = _coord.y + std::sin(_angle + PI / 2.f);

		int mapX = static_cast<int>(newX / 32);
		int mapY = static_cast<int>(newY / 32);

		if (mapX >= 0 && mapX < Map::getWidth() &&
			mapY >= 0 && mapY < Map::getHeight() &&
			!Map::isWall(mapX, mapY))
		{
			_coord.x = newX;
			_coord.y = newY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		float newX = _coord.x + std::cos(_angle - PI / 2.f);
		float newY = _coord.y + std::sin(_angle - PI / 2.f);

		int mapX = static_cast<int>(newX / 32);
		int mapY = static_cast<int>(newY / 32);

		if (mapX >= 0 && mapX < Map::getWidth() &&
			mapY >= 0 && mapY < Map::getHeight() &&
			!Map::isWall(mapX, mapY))
		{
			_coord.x = newX;
			_coord.y = newY;
		}
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//_angle += PI * deltaTime;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	_angle -= PI * deltaTime;

	_player.setPosition(_coord.x, _coord.y);
}