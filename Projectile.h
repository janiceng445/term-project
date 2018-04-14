//#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML\Graphics.hpp>

class Projectile {
	private:
	float maxVel = 1.f;

	public:
	Projectile(sf::Sprite sprite);
	sf::Vector2f vel;
	sf::Sprite bullet;
	void setVel(sf::Vector2f input);
	sf::Vector2f getVel();
	float getMaxVel();

};

#endif
