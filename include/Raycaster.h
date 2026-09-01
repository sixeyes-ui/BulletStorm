#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "Player.h"

class Raycaster
{
public:
	Raycaster();

	void castRays(const sf::Vector2f& position, float angle, float horizon);
	void castFloor(const sf::Vector2f& position, float angle, float horizon);
	void castCeiling(float horizon);

	static const std::vector<float>& getDepthBuffer()
	{
		return _depthBuffer;
	}

	int getNumRays() const
	{
		return _numRays;
	}

private:
	float _rayAngle;
	float _angleStep;
	float _rayDistance;

	//std::vector<sf::RectangleShape> _wallColumns;

	int _numRays;

	static std::vector<float> _depthBuffer;
};

#endif // !RAYCASTER_H
