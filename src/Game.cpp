#include "include/Game.h"
#include "include/Config.h"
#include "include/Texture.h"
#include "include/Render.h"
#include <iostream>

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

	_enemies.emplace_back(Vec2(600.f, 300.f), 0);
	_enemies.emplace_back(Vec2(500.f, 400.f), 0);
	_enemies.emplace_back(Vec2(700.f, 200.f), 0);
	_enemies.emplace_back(Vec2(300.f, 400.f), 0);
	_enemies.emplace_back(Vec2(200.f, 200.f), 0);
	_enemies.emplace_back(Vec2(450.f, 500.f), 0);
	_enemies.emplace_back(Vec2(600.f, 450.f), 0);
	_enemies.emplace_back(Vec2(700.f, 350.f), 0);
	_enemies.emplace_back(Vec2(250.f, 450.f), 0);
	_enemies.emplace_back(Vec2(550.f, 150.f), 0);
	_enemies.emplace_back(Vec2(520.f, 150.f), 0);
	_enemies.emplace_back(Vec2(620.f, 150.f), 0);
	_enemies.emplace_back(Vec2(150.f, 150.f), 0);
	_enemies.emplace_back(Vec2(350.f, 250.f), 0);
	_enemies.emplace_back(Vec2(250.f, 750.f), 0);
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
		//int mouseDeltaY = mousePosition.y - windowCenter.y;

		_player.handleMouse(static_cast<float>(mouseDeltaX), 0);

		sf::Mouse::setPosition(windowCenter, _window);

		accumulator += clock.restart();
		while (accumulator >= frameTime)
		{
			update(frameTime.asSeconds());
			updates++;
			accumulator -= frameTime;
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

		for (Enemy& enemy : _enemies)
		{
			enemy.setPlayerPos(_player.getPosition(), _player.getAngle());
			enemy.update(frameTime.asSeconds(), horizon);
		}

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