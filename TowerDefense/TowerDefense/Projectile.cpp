#include <SFML\Graphics.hpp>
#include "Projectile.h"

Projectile::Projectile(sf::Sprite sprite) {
	bullet = sprite;
}

void Projectile::setVel(sf::Vector2f input) {
	vel = input;
}

sf::Vector2f Projectile::getVel() {
	return vel;
}

float Projectile::getMaxVel() {
	return maxVel;
}
