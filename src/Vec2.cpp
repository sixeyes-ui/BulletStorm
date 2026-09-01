#include "include/Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(const Vec2& coord1, const Vec2& coord2)
{
	x = coord2.x - coord1.x;
	y = coord2.y - coord1.y;
}

Vec2::Vec2(float cx, float cy) : x(cx), y(cy)
{}

void Vec2::move(const Vec2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
}

float Vec2::getNorm() const
{
	return std::sqrt(x*x+y*y);
}

float Vec2::getNorm2() const
{
	return x*x+y*y;
}