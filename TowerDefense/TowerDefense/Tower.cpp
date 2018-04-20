#include "Tower.h"

Tower::Tower(sf::RenderWindow* renderWin, int hitpoints, int attack, sf::Sprite towerSprite, float xPos, float yPos)
{
	//changeable attributes
	this->maxHealth = hitpoints;
	this->health = maxHealth;
	this->atk = attack;

	//defaults
	this->renWin = renderWin;
	this->alive = true;
	this->posX = xPos;
	this->posY = yPos;
	this->sprite = towerSprite;
	spriteWidth = sprite.getGlobalBounds().width;
	spriteHeight = sprite.getGlobalBounds().height;

	this->sprite.setPosition(this->posX, this->posY);

	// Setting origin
	originSprite.x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
	originSprite.y = sprite.getPosition().y + sprite.getGlobalBounds().height;
	addHealthBar();
	HP = &health;
}

int Tower::getXPosition()
{
	return this->posX;
}

int Tower::getHealth()
{
	return this->health;
}

int* Tower::getHP()
{
	return HP;
}

void Tower::assignTexture()
{
	this->towerTexture.loadFromFile("images/Towers/BasicBarrier.png");
}

void Tower::draw()
{
	this->renWin->draw(this->sprite);
	// Health bar features
	updateHealthBar();
	this->renWin->draw(bar);
	this->renWin->draw(barOutline);
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
	std::cout << health << " " << *HP << std::endl;
}

/////////////////////////////////////////// Health Bar ///////////////////////////////////////////

void Tower::addHealthBar()
{
	barMaxWidth = spriteWidth * 1.2;
	barOutline.setSize(sf::Vector2f(barMaxWidth, 15));
	barOutline.setOrigin(barOutline.getSize().x / 2, barOutline.getSize().y / 2);
	barOutline.setPosition(originSprite.x, originSprite.y - spriteHeight - 10);
	barOutline.setFillColor(sf::Color::Transparent);
	barOutline.setOutlineColor(sf::Color::Black);
	barOutline.setOutlineThickness(2);

	bar.setSize(sf::Vector2f(barMaxWidth, 15));
	bar.setOrigin(bar.getSize().x / 2, bar.getSize().y / 2);
	bar.setPosition(originSprite.x, originSprite.y - spriteHeight - 10);
	bar.setFillColor(sf::Color::Green);
}
void Tower::updateHealthBar()
{
	float hp = (float)*this->HP / this->maxHealth * barMaxWidth;
	// Changing color of bar if < 50%
	hp > 0.50 * this->spriteWidth ? bar.setFillColor(sf::Color::Green) :
		bar.setFillColor(sf::Color::Red);
	bar.setSize(sf::Vector2f(hp, 15));
}

Tower::~Tower() {}