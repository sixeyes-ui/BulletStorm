#include "include/SoundManager.h"

#include <iostream>

sf::SoundBuffer SoundManager::_walkBuffer;
sf::SoundBuffer SoundManager::_shootBuffer;
sf::SoundBuffer SoundManager::_enemyHurtBuffer;

sf::Sound SoundManager::_walkSound;
sf::Sound SoundManager::_shootSound;
sf::Sound SoundManager::_enemyHurtSound;

sf::Music SoundManager::_music;

void SoundManager::init()
{
	if (!_walkBuffer.loadFromFile("assets/walk.wav"))
	{
		std::cout << "Failed to load walk sound!\n";
	}

	if (!_shootBuffer.loadFromFile("assets/shoot.wav"))
	{
		std::cout << "Failed to load shoot sound!\n";
	}

	if (!_enemyHurtBuffer.loadFromFile("assets/enemy_hurt.wav"))
	{
		std::cout << "Failed to load enemy hurt sound!" << std::endl;
	}

	_enemyHurtSound.setBuffer(_enemyHurtBuffer);
	_walkSound.setBuffer(_walkBuffer);
	_shootSound.setBuffer(_shootBuffer);

	_walkSound.setVolume(40.f);
	_shootSound.setVolume(70.f);

	_music.setVolume(20.f);
}

void SoundManager::playWalk()
{
	_walkSound.play();
}

void SoundManager::playShoot()
{
	_shootSound.play();
}

void SoundManager::playEnemyHurt()
{
	_enemyHurtSound.play();
}

void SoundManager::playMusic()
{
	if (!_music.openFromFile("assets/backGroundSound.ogg"))
	{
		std::cout << "Failed to load music!\n";
		return;
	}

	_music.setLoop(true);
	_music.setVolume(30.f);

	_music.play();
}