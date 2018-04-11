#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* renWin)
{
	// Changeable Attributes
	this->speed = 0.5f;
	this->health = 100;
	this->atk = 5;

	// Default
	this->isAlive = true;
	this->initX = 100;
	this->initY = 100;
	this->posX = initX;
	this->posY = initY;

	// Graphic
	assignTexture();
	assignWindow(renWin);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(posX, posY);
	this->spriteWidth = this->sprite.getGlobalBounds().width;

	// Healthbar
	healthWidth = spriteWidth;

	draw();
}


Enemy::~Enemy()
{


}
// Sets window
void Enemy::assignWindow(sf::RenderWindow* renWin) {
	this->renWin = renWin;
	this->windowWidth = renWin->getSize().x;
}
// Sets texture
void Enemy::assignTexture() {
	sf::Texture t;
	t.loadFromFile("images/enemies/duck.png");
	this->texture = t;
}
// Draw graphic
void Enemy::draw() {
	if (this->isAlive) {
		// Updating x and y coords
		setX();
		setY();
		// Draw elements
		this->renWin->draw(this->sprite);
		drawHealthBar();
	}
}
// Moves Enemy p amount of pixels
void Enemy::moveX() {
	if (this->posX < windowWidth - spriteWidth) {
		this->sprite.move(0.1f, 0);
	}
	draw();
}

// Fighting functions
int Enemy::getHealth() {
	return this->health;
}
int Enemy::getAtkDmg() {
	return this->atk;
}
void Enemy::takeDamage(int dmg) {
	this->health -= dmg;
	if (this->health <= 0) {
		die();
	}
}
void Enemy::die() {
	this->isAlive = false;
}

// Healthbar
void Enemy::drawHealthBar() {
	// Formula for calculating % health
	float hp = this->health / 100 * this->healthWidth;

	// Changing color of bar if < 50%
	sf::Color color;
	hp > 0.50 * this->healthWidth ?
		this->bar.setFillColor(sf::Color::Green) : 
		this->bar.setFillColor(sf::Color::Red);

	// Updates healthbar according to amount of hp
	this->bar.setSize(sf::Vector2f(hp, 5));
	
	// Appearance of health bar
	this->bar.setOutlineColor(sf::Color::Black);
	this->bar.setOutlineThickness(1);
	this->bar.setPosition(this->posX, this->posY - 10);

	// Draws healthbar
	this->renWin->draw(bar);
}

// Set sprite's x and y
void Enemy::setX() {
	this->posX = this->sprite.getPosition().x;
}
void Enemy::setY() {
	this->posY = this->sprite.getPosition().y;
}

// Get sprite's x coordinate
float Enemy::getX() {
	return posX;
}
