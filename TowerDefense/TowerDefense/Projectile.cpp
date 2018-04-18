#include <SFML\Graphics.hpp>
#include "Projectile.h"

Projectile::Projectile(float radius) {
	bullet.setRadius(radius);
	bullet.setFillColor(sf::Color::Black);
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

bool Projectile::checkCollision(std::vector<Monster*>* m) {
	for (unsigned int i = 0; i < m->size(); i++) {
		if (m->at(i)->isAliveFunc()) {
			if (bullet.getGlobalBounds().intersects(m->at(i)->getSpriteGlobalBounds())) {
				m->at(i)->takeDamage(25);
				return true;
			}
			//if (m->at(i).isDead()) m->erase(m->begin() + i);
		}
	}
	return false;
}