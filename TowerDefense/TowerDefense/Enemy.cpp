#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* renWin, float hp, int atk, float spd)
{
	// Changeable Attributes
	this->health = hp;
	this->atk = atk / 2; // explanation: the timer ticks causes 2x amount of dmg
	this->speed = spd;

	// Default
	this->isAlive = true;
	this->initX = 100;
	this->initY = 100;
	this->posX = initX;
	this->posY = initY;

	// Texture paths
	this->texturePath_idle = "images/enemies/duck.png";
	this->texturePath_attack = "images/enemies/duck_attack.png";
	this->texturePath_death = "images/enemies/duck_death.png";
	this->texturePath_special = "images/enemies/duck_special.png";
	testTextures();

	// Graphic
	assignTexture();
	assignWindow(renWin);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(posX, posY);
	this->spriteWidth = this->sprite.getGlobalBounds().width;
	this->spriteHeight = this->sprite.getGlobalBounds().height;
	this->hitboxWidth = this->spriteWidth * 0.7f;
	this->hitboxHeight = this->spriteHeight;
	this->stopDrawing = false;

	// Healthbar
	healthWidth = spriteWidth;

	// Timer

	draw();
}
Enemy::~Enemy()
{


}
/////////////////////////// Graphics ///////////////////////////
// Textures
void Enemy::setTexturePathIdle(std::string name) {
	this->texturePath_idle = name;
}
void Enemy::setTexturePathAttack(std::string name) {
	this->texturePath_attack = name;
}
void Enemy::setTexturePathDeath(std::string name) {
	this->texturePath_death = name;
}
void Enemy::setTexturePathSpecial(std::string name) {
	this->texturePath_special = name;
}
void Enemy::testTextures() {
	sf::Texture temp;
	if (!temp.loadFromFile(this->texturePath_idle)) {
		std::cout << "Idle_texture missing." << std::endl;
	}
	if (!temp.loadFromFile(this->texturePath_attack)) {
		std::cout << "Attack_texture missing." << std::endl;
	}
	if (!temp.loadFromFile(this->texturePath_death)) {
		std::cout << "Death_texture missing." << std::endl;
	}
	if (!temp.loadFromFile(this->texturePath_special)) {
		std::cout << "Special_texture missing." << std::endl;
	}
}
// Sets window
void Enemy::assignWindow(sf::RenderWindow* renWin) {
	this->renWin = renWin;
	this->windowWidth = renWin->getSize().x;
}
// Sets texture
void Enemy::assignTexture() {
	sf::Texture t;
	t.loadFromFile(this->texturePath_idle);
	
	this->texture = t;
}
// Changes texture/animation
void Enemy::changeTexture(sf::Texture t) {
	this->texture = t;
}
// Draw everything
void Enemy::draw() {
	if (!this->stopDrawing) {
		// Updating x and y coords
		setX();
		setY();
		// Draw elements
		this->renWin->draw(this->sprite);
		drawHealthBar();
		drawHitbox();
	}

	if (!this->isAlive) {
		timer++;
		if (timer == DECAY_TIMER) {
			timer = 0;
			this->stopDrawing = true;
		}
	}
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
// Set hitbox width
void Enemy::setHitboxWidth(float w) {
	this->hitboxWidth = w;
}
// Set hitbox Height
void Enemy::setHitBoxHeight(float h) {
	this->hitboxHeight = h;
}
// Hitbox
void Enemy::drawHitbox() {
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineColor(sf::Color::Red);
	this->hitbox.setOutlineThickness(1);
	this->hitbox.setSize(sf::Vector2f(this->hitboxWidth, this->hitboxHeight));
	this->hitbox.setPosition(this->posX + 0.1f * this->spriteWidth, this->posY);
	this->renWin->draw(hitbox);
}

/////////////////////////// Location ///////////////////////////
// Set sprite's x and y coordinates
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

// Know if enemy reached boundary line (width of sprite itself)
bool Enemy::withinBounds() { // Lines that divide the screen
	if (this->posX + this->spriteWidth > this->currentBound - 5) {	 // and stops enemy from moving further
		return true;
	}
	return false;
}
void Enemy::changeBound(int x) {
	this->currentBound = x;
}

///////////////////////////// Data //////////////////////////////
// Main Functions
void Enemy::attack(float& targetHealth) {
	targetHealth -= getAtkDmg();
}
float Enemy::getHealth() {
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
	sf::Texture t;
	t.loadFromFile(this->texturePath_death);
	changeTexture(t);
	this->isAlive = false;
}
void Enemy::moveX() {
	// Stop at boundary
	if (this->posX + this->spriteWidth < this->currentBound) {
		this->sprite.move(0.1f, 0);
	}
	draw();
}


