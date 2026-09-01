#include "include/Raycaster.h"
#include "include/Map.h"
#include "include/Config.h"
#include "include/Texture.h"
#include "include/Render.h"
#include "include/Enemy.h"
#include <iostream>
#include <algorithm>

std::vector<float> Raycaster::_depthBuffer;

Raycaster::Raycaster() :
	_rayDistance(0),
	_numRays(SCREEN_WIDTH),
	_angleStep(0),
	_rayAngle(0)
{
	Map::init();
	_depthBuffer.resize(_numRays);
}

void Raycaster::castRays(const sf::Vector2f& position, float angle, float horizon)
{
	_angleStep = FOV / (_numRays - 1);
	_rayAngle = angle - FOV / 2.f;

	for (int ray = 0; ray < _numRays; ray++)
	{
		float rayDirX = std::cos(_rayAngle);
		float rayDirY = std::sin(_rayAngle);

		int mapX = static_cast<int>(position.x / 32);
		int mapY = static_cast<int>(position.y / 32);

		float deltaDistX = std::abs(32.f / rayDirX);
		float deltaDistY = std::abs(32.f / rayDirY);

		int stepX;
		int stepY;

		if (rayDirX < 0)
			stepX = -1;
		else
			stepX = 1;

		if (rayDirY < 0)
			stepY = -1;
		else
			stepY = 1;

		float sideDistX;
		
		if (stepX < 0)
			sideDistX = (position.x - mapX * 32) / std::abs(rayDirX);
		else
			sideDistX = ((mapX + stepX) * 32 - position.x) / std::abs(rayDirX);

		float sideDistY;
		
		if (stepY < 0)
			sideDistY = (position.y - mapY * 32) / std::abs(rayDirY);
		else
			sideDistY = ((mapY + stepY) * 32 - position.y) / std::abs(rayDirY);

		bool hitWall = false;
		int side;

		while (!hitWall)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (mapX < 0 || mapX >= Map::getWidth() ||
				mapY < 0 || mapY >= Map::getHeight())
			{
				break;
			}

			if (Map::isWall(mapX, mapY))
			{
				hitWall = true;
			}
		}

		if (hitWall)
		{
			if (side == 0)
			{
				_rayDistance = sideDistX - deltaDistX;
			}
			else
			{
				_rayDistance = sideDistY - deltaDistY;
			}
		}

		if (_rayDistance > 0)
		{
			float angleDifference = _rayAngle - angle;
			float correctedDistance = _rayDistance * std::cos(angleDifference);

			//Enemy::setDepthBuffer(ray, correctedDistance);
			_depthBuffer[ray] = correctedDistance;

			float brightness = 255.f - correctedDistance * 2.f;

			if (brightness < 20.f)
				brightness = 20.f;

			if (brightness > 255.f)
				brightness = 255.f;

			if (side == 1)
			{
				brightness *= 0.7f;
			}

			//_wallColumns[ray].setFillColor(
			//	sf::Color(
			//		static_cast<sf::Uint8>(brightness),
			//		static_cast<sf::Uint8>(brightness),
			//		static_cast<sf::Uint8>(brightness)
			//	)
			//);

			float projectionScale = 9000.f;
			float wallHeight = projectionScale / correctedDistance;
			float wallWidth = SCREEN_WIDTH / _numRays;

			//float horizon = SCREEN_WIDTH / 2.f;
			float wallTop = horizon - wallHeight / 2.f;

			//_wallColumns[ray].setSize(sf::Vector2f(wallWidth, wallHeight));
			//_wallColumns[ray].setPosition(sf::Vector2f(ray * wallWidth, wallTop));

			float hitX = position.x + rayDirX * _rayDistance;
			float hitY = position.y + rayDirY * _rayDistance;

			float wallX;

			if (side == 0)
				wallX = hitY;
			else
				wallX = hitX;

			wallX /= 32.f;
			wallX -= std::floor(wallX);

			Texture::setWallPixel(wallHeight, wallWidth, wallTop, wallX, ray);
		}

		_rayAngle += _angleStep;
		_rayDistance = 0.f;
	}
}

void Raycaster::castCeiling(float horizon)
{
	int endY = static_cast<int>(horizon);

	if (endY < 0)
		endY = 0;

	if (endY > SCREEN_HEIGHT)
		endY = SCREEN_HEIGHT;

	for (int y = 0; y < endY; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			Render::setPixel(
				x,
				y,
				sf::Color(80, 80, 120)
			);
		}
	}
}

void Raycaster::castFloor(const sf::Vector2f& position, float angle, float horizon)
{
	const float cameraHeight = 100.f;

	const float leftAngle = angle - FOV / 2.f;
	const float rightAngle = angle + FOV / 2.f;

	const float leftRayX = std::cos(leftAngle);
	const float leftRayY = std::sin(leftAngle);

	const float rightRayX = std::cos(rightAngle);
	const float rightRayY = std::sin(rightAngle);

	for (int y = static_cast<int>(horizon) + 1; y < SCREEN_HEIGHT; y++)
	{
		const float rowDistance =
			cameraHeight / (y - horizon);

		const float leftWorldX =
			position.x + leftRayX * rowDistance;

		const float leftWorldY =
			position.y + leftRayY * rowDistance;

		const float rightWorldX =
			position.x + rightRayX * rowDistance;

		const float rightWorldY =
			position.y + rightRayY * rowDistance;

		// Calculate ONCE per row
		const float stepX =
			(rightWorldX - leftWorldX) /
			static_cast<float>(SCREEN_WIDTH);

		const float stepY =
			(rightWorldY - leftWorldY) /
			static_cast<float>(SCREEN_WIDTH);

		float worldX = leftWorldX;
		float worldY = leftWorldY;

		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			int texX = static_cast<int>(worldX) & 31;
			int texY = static_cast<int>(worldY) & 31;

			Texture::setFloorPixel(x, y, texX, texY);

			worldX += stepX;
			worldY += stepY;
		}
	}
}