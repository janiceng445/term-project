#include "Tower.h"

Tower::Tower(sf::RenderWindow* renderWin, int hitpoints, int attack, sf::Sprite towerSprite, float xPos, float yPos)
{
	//changeable attributes
	this->health = hitpoints;
	this->atk = attack;

	//defaults
	this->renWin = renderWin;
	this->alive = true;
	this->posX = xPos;
	this->posY = yPos;
	this->sprite = towerSprite;

	this->sprite.setPosition(this->posX, this->posY);
}

int Tower::getXPosition()
{
	return this->posX;
}

int Tower::getHealth()
{
	return this->health;
}

void Tower::assignTexture()
{
	this->towerTexture.loadFromFile("images/Towers/BasicBarrier.png");
}

void Tower::draw()
{
	this->renWin->draw(this->sprite);
}

void Tower::die()
{
	this->alive = false;
}

bool Tower::amIAlive()
{
	return this->alive;
}

sf::Sprite Tower::getSprite()
{
	return this->sprite;
}

sf::FloatRect Tower::getSpriteGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

void Tower::takeDamage(int dmg)
{
	this->health -= dmg;
	if (this->health <= 0)
	{
		this->health = 0;
		die();
	}
}


Tower::~Tower() {}