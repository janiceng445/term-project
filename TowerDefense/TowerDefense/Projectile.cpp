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

sf::Vector2f Projectile::getLocation() {
	return this->bullet.getPosition();
}

sf::FloatRect Projectile::getSpriteGlobalBounds() {
	return bullet.getGlobalBounds();
}

bool Projectile::checkCollision(std::vector<Monster>* m) {
	for (unsigned int i = 0; i < m->size(); i++) {
		if (bullet.getGlobalBounds().intersects(m->at(i).getSpriteGlobalBounds())) {
			m->at(i).takeDamage(25);
			if (!m->at(i).isAliveFunc()) m->erase(m->begin() + i);
			return true;
		}
	}
	return false;
}