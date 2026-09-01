#ifndef U2DCOORD_H
#define U2DCOORD_H

class Vec2
{
public:
	Vec2();
	Vec2(const Vec2&, const Vec2&);
	Vec2(float cx, float cy);

	void move(const Vec2& vec);
	float getNorm()  const;
	float getNorm2() const;

	float x, y;
};

#endif // !VEC2_H
