#include <SFML\Graphics.hpp>
#include "Projectile.h"

Projectile::Projectile(float radius, bool joe)
{
	bullet.setRadius(radius);

	if (joe)
	{
		bullet.setFillColor(sf::Color(250, 255, 165, 255));
	}
	else
	{
		bullet.setFillColor(sf::Color(255, 165, 250, 255));
	}
}

void Projectile::setVel(sf::Vector2f input)
{
	vel = input;
}

sf::Vector2f Projectile::getVel()
{
	return vel;
}

float Projectile::getMaxVel()
{
	return maxVel;
}

sf::Vector2f Projectile::getLocation()
{
	return this->bullet.getPosition();
}

sf::FloatRect Projectile::getSpriteGlobalBounds()
{
	return bullet.getGlobalBounds();
}

bool Projectile::checkCollision(std::vector<Monster*>* m, int dmg)
{
	for (unsigned int i = 0; i < m->size(); i++)
	{
		if (m->at(i)->isAliveFunc())
		{
			if (bullet.getPosition().x < m->at(i)->getDetectionDistance())
			{
				m->at(i)->useSpecialAbility();
			}
			if (bullet.getGlobalBounds().intersects(m->at(i)->getSpriteGlobalBounds()))
			{
				m->at(i)->takeDamage(dmg);
				return true;
			}
			//if (m->at(i).isDead()) m->erase(m->begin() + i);
		}
	}
	return false;
}