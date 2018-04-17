#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Monster.h"
#include <SFML\Graphics.hpp>
#include <vector>

class Projectile {
	private:
	float maxVel = 1.f;

	public:
	Projectile(float radius);
	sf::Vector2f vel;
	sf::CircleShape bullet;
	void setVel(sf::Vector2f input);
	sf::Vector2f getVel();
	float getMaxVel();

	// Get sprite
	sf::Vector2f getLocation();
	sf::FloatRect getSpriteGlobalBounds();
	bool checkCollision(std::vector<Monster>* m);
};

#endif
