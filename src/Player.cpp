#include "include/Player.h"
#include "include/Config.h"
#include "include/Map.h"
#include "include/Render.h"
#include "include/SoundManager.h"
#include <iostream>

Player::Player(const Vec2& coord) :
	_coord(coord),
	_angle(0),
	_pitch(0.f),
	_isFiring(false),
	_fireTimer(0.f),
	_walkTimer(0.f),
	_isWalking(false),
	_shotThisFrame(false)
{
	_player.setPosition(_coord.x, _coord.y);

	if (!_gunIdleSprite.loadFromFile("assets/gun1.png"))
	{
		std::cout << "Failed to load gun sprite!" << std::endl;
	}

	if (!_gunFireSprite.loadFromFile("assets/gun2.png"))
	{
		std::cout << "Failed to load fire gun!" << std::endl;
	}
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

void Player::shoot()
{
	if (_isFiring)
		return;

	std::cout << "PLAYER SHOOTING!" << std::endl;

	_isFiring = true;
	_shotThisFrame = true;

	_fireTimer = 0.15f;

	SoundManager::playShoot();
}

void Player::update(float deltaTime)
{
	float speed = 100.f;

	bool moving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moving = true;
	}

	if (_isFiring)
	{
		_fireTimer -= deltaTime;

		if (_fireTimer <= 0.f)
		{
			_isFiring = false;
		}
	}

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

	if (moving)
	{
		_walkTimer -= deltaTime;

		if (_walkTimer <= 0.f)
		{
			SoundManager::playWalk();

			_walkTimer = 0.4f;
		}
	}
	else
	{
		_walkTimer = 0.f;
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//_angle += PI * deltaTime;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	_angle -= PI * deltaTime;

	_player.setPosition(_coord.x, _coord.y);
}

void Player::renderWeapon()
{
	const sf::Image& weaponSprite = _isFiring ? _gunFireSprite : _gunIdleSprite;

	constexpr float SCALE = 5.0f;
	int spriteWidth = static_cast<int>(weaponSprite.getSize().x * SCALE);
	int spriteHeight = static_cast<int>(weaponSprite.getSize().y * SCALE);

	int startX = SCREEN_WIDTH / 2 - spriteWidth / 2;
	int startY = SCREEN_HEIGHT - spriteHeight;

	for (int y = 0; y < spriteHeight; y++)
	{
		for (int x = 0; x < spriteWidth; x++)
		{
			int texX = static_cast<int>(x / SCALE);
			int texY = static_cast<int>(y / SCALE);

			if (texX < 0 || texX >= spriteWidth ||
				texY < 0 || texY >= spriteHeight)
			{
				continue;
			}

			sf::Color pixel = weaponSprite.getPixel(texX, texY);

			if (pixel.a == 0)
				continue;

			Render::setPixel(startX + x, startY + y, pixel);
		}
	}
}