#include "include/Enemy.h"
#include "include/Render.h"
#include "include/Config.h"
#include "include/Raycaster.h"
#include "include/Map.h"
#include <iostream>

Enemy::Enemy(const Vec2& coord, float angle) :
	_coord(coord),
	_angle(angle)
{
	if (!_sprite.loadFromFile("assets/DFrame0.png"))
	{
		std::cout << "Failed to load enemy image\n";
	}
}

void Enemy::setPlayerPos(const sf::Vector2f& playerPos, float angle)
{
	_playerPos.x = playerPos.x;
	_playerPos.y = playerPos.y;
	_playerAngle = angle;
}

void Enemy::update(float dt, float horizon)
{
	//float dt = 1.f / 60;

	float enemySpeed = 50.f;
	float chaseDistance = 200.f;

	float dx = _playerPos.x - _coord.x;
	float dy = _playerPos.y - _coord.y;

	float enemyDistance = std::sqrt(dx * dx + dy * dy);
	float enemyToPlayerDistance = std::sqrt(dx * dx + dy * dy);

	if (enemyDistance < chaseDistance &&
		enemyDistance > 20.f)
	{
		float dirX = dx / enemyDistance;
		float dirY = dy / enemyDistance;

		float newEnemyX = _coord.x + dirX * enemySpeed * dt;
		float newEnemyY = _coord.y + dirY * enemySpeed * dt;

		int enemyMapX = static_cast<int>(newEnemyX / 32.f);
		int enemyMapY = static_cast<int>(newEnemyY / 32.f);

		if (enemyMapX >= 0 && enemyMapX < Map::getWidth() &&
			enemyMapY >= 0 && enemyMapY < Map::getHeight() &&
			!Map::isWall(enemyMapX,enemyMapY))
		{
			_coord.x = newEnemyX;
			_coord.y = newEnemyY;
		}
	}

	dx = _coord.x - _playerPos.x;
	dy = _coord.y - _playerPos.y;

	float enemyAngle = std::atan2(dy, dx);
	float angleDifference = enemyAngle - _playerAngle;
	float enemyCorrectedDistance = enemyDistance * std::cos(angleDifference);

	while (angleDifference > PI)
		angleDifference -= 2.f * PI;

	while (angleDifference < -PI)
		angleDifference += 2.f * PI;

	if (std::abs(angleDifference) < FOV / 2.f)
	{
		float normalized = (angleDifference + FOV / 2.f) / FOV;
		float screenX = normalized * SCREEN_WIDTH;

		float enemyHeight = 4000.f / enemyDistance;
		float enemyWidth = enemyHeight * 0.6f;

		int enemyLeft = static_cast<int>(screenX - enemyWidth / 2.f);
		int enemyRight = static_cast<int>(screenX + enemyWidth / 2.f);

		int enemyTop = static_cast<int>(horizon - enemyHeight / 2.f);
		int enemyBottom = static_cast<int>(horizon + enemyHeight / 2.f);

		for (int x = enemyLeft; x < enemyRight; x++)
		{
			if (x < 0 || x >= SCREEN_WIDTH)
				continue;

			int ray = static_cast<int>(static_cast<float>(x) / SCREEN_WIDTH * SCREEN_WIDTH);

			if (enemyCorrectedDistance < Raycaster::getDepthBuffer()[ray])
			{
				for (int y = enemyTop; y < enemyBottom; y++)
				{
					if (y < 0 || y >= SCREEN_HEIGHT)
						continue;

					float textureX = static_cast<float>(x - enemyLeft) / enemyWidth;
					float textureY = static_cast<float>(y - enemyTop) / enemyHeight;

					int texX = static_cast<int>(textureX * _sprite.getSize().x);
					int texY = static_cast<int>(textureY * _sprite.getSize().y);

					if (texX >= 0 &&
						texX < _sprite.getSize().x &&
						texY >= 0 &&
						texY < _sprite.getSize().y)
					{
						sf::Color pixel = _sprite.getPixel(texX, texY);

						if (pixel.a > 0)
						{
							Render::setPixel(x, y, pixel);
						}
					}
				}
			}
		}
	}
}

//void Enemy::setDepthBuffer(int ray, float distance)
//{
//	if (ray >= 0 && ray < static_cast<int>(_depthBuffer.size()))
//	{
//		_depthBuffer[ray] = distance;
//	}
//}

//void Enemy::render(sf::RenderWindow* window)
//{
//	window->draw(_enemy);
//}