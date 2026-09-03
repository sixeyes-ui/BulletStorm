#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>

class SoundManager
{
public:
	static void init();

	static void playWalk();
	static void playShoot();
	static void playEnemyHurt();

	static void playMusic();

private:
	static sf::SoundBuffer _walkBuffer;
	static sf::SoundBuffer _shootBuffer;
	static sf::SoundBuffer _enemyHurtBuffer;

	static sf::Sound _enemyHurtSound;
	static sf::Sound _walkSound;
	static sf::Sound _shootSound;

	static sf::Music _music;
};

#endif // !SOUND_MANAGER_H
