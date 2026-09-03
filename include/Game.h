#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Raycaster.h"
#include "SpriteRenderer.h"
#include <vector>

class Game
{
public:
	Game();

	void shoot();
	void run(int fps = 60);

private:

	void update(float deltaTime);
	void render();

	Player _player;
	Enemy  _enemy;
	Raycaster _caster;

	std::vector<Enemy> _enemies;

	sf::RenderWindow _window;
};

#endif // !GAME_H
