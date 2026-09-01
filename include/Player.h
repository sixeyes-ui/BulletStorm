#ifndef PLAYER_H
#define PLAYER_H

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(const Vec2& coord);

	void update(float deltaTime);
	void handleMouse(float mouseDeltaX, float mouseDeltaY);

	float getAngle()                  const { return _angle; }
	const sf::Vector2f& getPosition() const { return _player.getPosition(); }
	float getPitch() const { return _pitch; }

private:
	Vec2  _coord;
	float _angle;
	float _pitch;

	sf::CircleShape _player;
};

#endif // !PLAYER_H