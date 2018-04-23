#include "Tower.h"

Tower::Tower(sf::RenderWindow* renderWin, int hitpoints, int attack, sf::Sprite towerSprite, float xPos, float yPos, sf::Sound* damageSound)
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
	this->upgradeLv = 1;
	spriteWidth = (int)(sprite.getGlobalBounds().width);
	spriteHeight = (int)(sprite.getGlobalBounds().height);

	this->sprite.setPosition(this->posX, this->posY);

	// Setting origin
	originSprite.x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
	originSprite.y = sprite.getPosition().y + sprite.getGlobalBounds().height;
	addHealthBar();
	HP = &health;

	// Sound
	this->damageSound = damageSound;
}

int Tower::getXPosition()
{
	return (int)(this->posX);
}

int Tower::getHealth()
{
	return this->health;
}

int* Tower::getHP()
{
	return HP;
}

int Tower::getmaxHP()
{
	return this->maxHealth;
}


void Tower::draw()
{
	// Draws the tower
	this->renWin->draw(this->sprite);

	// Health bar features
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

void Tower::takeDamage()
{
	if (damageSound->getStatus() != sf::SoundSource::Playing && *HP < health)
	{
		damageSound->play();
	}

	health = *HP;

	if (this->health <= 0)
	{
		*HP = 0;
		this->health = 0;
		die();
	}
}

int Tower::getDmg()
{
	return this->atk;
}

void Tower::upgradeDmg()
{
	this->atk += 10;
}

void Tower::upgradeHealth()
{
	this->maxHealth += 10;
	*HP += 10;
}

void Tower::updateSprite(sf::Texture* newTex)
{
	this->sprite.setTexture(*newTex);
}

/////////////////////////////////////////// Health Bar ///////////////////////////////////////////

void Tower::addHealthBar()
{
	barMaxWidth = spriteWidth * 1.2f;
	barOutline.setSize(sf::Vector2f(barMaxWidth, 15));
	barOutline.setOrigin(barOutline.getSize().x / 2, barOutline.getSize().y / 2);
	barOutline.setPosition(originSprite.x, originSprite.y - spriteHeight - 20);
	barOutline.setFillColor(sf::Color::Transparent);
	barOutline.setOutlineColor(sf::Color::Black);
	barOutline.setOutlineThickness(2);

	bar.setSize(sf::Vector2f(barMaxWidth, 15));
	bar.setOrigin(bar.getSize().x / 2, bar.getSize().y / 2);
	bar.setPosition(originSprite.x, originSprite.y - spriteHeight - 20);
	bar.setFillColor(sf::Color::Green);
}
void Tower::updateHealthBar()
{
	float hp = ((float)*HP / (float)maxHealth) * barMaxWidth;
	// Changing color of bar if < 50%
	hp > 0.50 * this->spriteWidth ? bar.setFillColor(sf::Color::Green) :
		bar.setFillColor(sf::Color::Red);
	bar.setSize(sf::Vector2f(hp, 15));
	takeDamage();
}

Tower::~Tower() {}