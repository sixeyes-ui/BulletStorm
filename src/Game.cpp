#include "include/Game.h"
#include "include/Config.h"
#include "include/Texture.h"
#include "include/Render.h"
#include "include/SoundManager.h"
#include "include/random.h"
#include <iostream>
#include <cmath>

Game::Game() :
	_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "PixelCast"),
	_player(Vec2(400.f, 300.f)),
	_enemy(Vec2(300.f, 300.f), 0)
{
	Render::initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!Texture::init())
	{
		std::cout << "ERROR: Could not load textures!" << std::endl;
	}

	SoundManager::init();
	SoundManager::playMusic();

	for (int i = 0; i < 50; i++)
	{
		_enemies.emplace_back(Vec2(random(0.f,(float)SCREEN_WIDTH), random(0.f, (float)SCREEN_HEIGHT)), 0);
	}
}

void Game::shoot()
{
	const sf::Vector2f& playerPos =
		_player.getPosition();

	float playerAngle =
		_player.getAngle();

	// =============================
	// GET WALL DISTANCE
	// =============================

	const std::vector<float>& depthBuffer =
		Raycaster::getDepthBuffer();

	int centerRay =
		SCREEN_WIDTH / 2;

	if (centerRay < 0 ||
		centerRay >= static_cast<int>(depthBuffer.size()))
	{
		return;
	}

	float wallDistance =
		depthBuffer[centerRay];

	// =============================
	// FIND ENEMY IN CROSSHAIR
	// =============================

	Enemy* closestEnemy = nullptr;

	float closestDistance = wallDistance;

	for (Enemy& enemy : _enemies)
	{
		if (!enemy.isAlive())
			continue;

		const sf::Vector2f& enemyPos =
			enemy.getPosition();

		float dx =
			enemyPos.x - playerPos.x;

		float dy =
			enemyPos.y - playerPos.y;

		float distance =
			std::sqrt(dx * dx + dy * dy);

		float enemyAngle =
			std::atan2(dy, dx);

		float angleDifference =
			enemyAngle - playerAngle;

		// Normalize angle
		while (angleDifference > PI)
			angleDifference -= 2.f * PI;

		while (angleDifference < -PI)
			angleDifference += 2.f * PI;

		// =============================
		// IS ENEMY NEAR CROSSHAIR?
		// =============================

		constexpr float HIT_ANGLE = 0.08f;

		if (std::abs(angleDifference) < HIT_ANGLE)
		{
			// Fix fisheye distance
			float correctedDistance =
				distance *
				std::cos(angleDifference);

			// Enemy must be BEFORE wall
			if (correctedDistance < wallDistance)
			{
				if (correctedDistance < closestDistance)
				{
					closestDistance =
						correctedDistance;

					closestEnemy =
						&enemy;
				}
			}
		}
	}

	// =============================
	// DAMAGE ENEMY
	// =============================

	if (closestEnemy != nullptr)
	{
		closestEnemy->takeDamage(50);

		std::cout
			<< "Enemy HIT!"
			<< std::endl;
	}
	else
	{
		std::cout
			<< "Miss!"
			<< std::endl;
	}
}

void Game::run(int fps)
{
	sf::Clock clock;
	sf::Time accumulator;
	sf::Time frameTime = sf::seconds(1.f / fps);
	sf::Event event;

	int frames = 0;
	int updates = 0;

	sf::Clock fpsClock;

	_window.setMouseCursorVisible(false);

	sf::Vector2i windowCenter(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2
	);

	sf::Mouse::setPosition(windowCenter, _window);

	while (_window.isOpen())
	{

		Render::clear();

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					_window.close();
			}
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);

		int mouseDeltaX = mousePosition.x - windowCenter.x;
		int mouseDeltaY = mousePosition.y - windowCenter.y;

		_player.handleMouse(static_cast<float>(mouseDeltaX), static_cast<float>(mouseDeltaY));

		sf::Mouse::setPosition(windowCenter, _window);

		accumulator += clock.restart();
		while (accumulator >= frameTime)
		{
			update(frameTime.asSeconds());
			updates++;
			accumulator -= frameTime;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_player.shoot();
		}

		float horizon = SCREEN_HEIGHT / 2.f + _player.getPitch();

		_caster.castCeiling(horizon);

		_caster.castFloor(
			_player.getPosition(),
			_player.getAngle(),
			horizon
		);

		_caster.castRays(
			_player.getPosition(),
			_player.getAngle(),
			horizon
		);

		if (_player.consumeShot())
		{
			shoot();
		}

		for (Enemy& enemy : _enemies)
		{
			enemy.setPlayerPos(_player.getPosition(), _player.getAngle());
			enemy.update(frameTime.asSeconds(), horizon);
		}

		_player.renderWeapon();

		Render::drawCrosshair();

		render();
		frames++;

		if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
		{
			std::cout << "Frames  : " << frames << std::endl;
			std::cout << "Updates : " << updates << std::endl;
			frames = 0;
			updates = 0;
			fpsClock.restart();
		}
	}
}

void Game::update(float deltaTime)
{
	_player.update(deltaTime);
}

void Game::render()
{
	//Render::clear();

	//_caster.castCeiling();

	//_caster.castFloor(
	//	_player.getPosition(), 
	//	_player.getAngle()
	//);

	//_caster.castRays(
	//	_player.getPosition(), 
	//	_player.getAngle()
	//);

	Render::loadTextures();

	_window.clear();

	Render::render(&_window);
	//_enemy.render(&_window);

	_window.display();
}