#ifndef ENEMY_H
#define ENEMY_H

#include "include/Vec2.h"
#include "include/Player.h"
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(const Vec2& coord, float angle);

	float getAngle()                  const { return _angle; }
	const sf::Vector2f& getPosition() const { return _spritePosition; }
	const sf::Image& getSprite()      const { return _sprite; }

	void  setPlayerPos(const sf::Vector2f& playerPos, float angle);
	void  update(float dt, float horizon);
	//void render(sf::RenderWindow* window);

private:
	Vec2  _playerPos;
	float _playerAngle;
	Vec2  _coord;
	float _angle;

	sf::Vector2f _spritePosition;
	sf::Image          _sprite;
};

#endif // !ENEMY_H
