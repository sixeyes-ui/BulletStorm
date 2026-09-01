#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>

class SpriteRenderer
{
public:
	static void renderSprite(const sf::Vector2f& cameraPosition, 
		float cameraAngle, 
		float horizon,
		const sf::Vector2f& spritePosition,
		const sf::Image& sprite,
		const std::vector<float>& depthBuffer);
};

#endif // !SPRITE_RENDERER_H
