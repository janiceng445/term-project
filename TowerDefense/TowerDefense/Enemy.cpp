#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* renWin, float hp, int atk, float spd, float as, std::vector<sf::Texture>* texturePack)
{
	// Changeable Attributes
	this->health = hp;
	this->atk = atk / 2; // explanation: the timer ticks causes 2x amount of dmg
	this->speed = spd;
	this->as = as;

	// Default
	this->alive = true;
	this->initX = -10;
	this->initY = 350;
	this->posX = initX;
	this->posY = initY;
	this->hitbox_visibility = false;
	this->animationSpeed = 0.17f;
	
	// Texture paths
	this->texturePack = texturePack;
	this->texturePath_idle = this->texturePack->at(0);
	this->texturePath_attack = this->texturePack->at(1);
	this->texturePath_death = this->texturePack->at(2);
	//this->texturePath_special = "images/enemies/" + type + "_special.png";

	// Graphic
	assignTexture();
	assignWindow(renWin);

	// Animation idle as default
	this->sprite.setTexture(texture);
	this->rectSrcSprite.left = 40;
	this->rectSrcSprite.top = 0;
	this->rectSrcSprite.width = 40;
	this->rectSrcSprite.height = 49;
	this->sprite.setTextureRect(rectSrcSprite);

	// Sprite settings and dimensions
	this->sprite.setPosition(posX, posY);
	this->spriteWidth = this->sprite.getGlobalBounds().width;
	this->spriteHeight = this->sprite.getGlobalBounds().height;
	// Hitbox
	this->hitboxWidth = this->spriteWidth * 0.7f;
	this->hitboxHeight = this->spriteHeight;
	this->stopDrawing = false;

	// Healthbar
	healthWidth = spriteWidth;

	draw();
}
Enemy::~Enemy()
{


}
/////////////////////////// Graphics ///////////////////////////
// Textures
void Enemy::setTexturePathIdle(sf::Texture texture) {
	//this->texturePath_idle = texture;
}
void Enemy::setTexturePathAttack(sf::Texture texture) {
	this->texturePath_attack = texture;
}
void Enemy::setTexturePathDeath(sf::Texture texture) {
	this->texturePath_death = texture;
}
void Enemy::setTexturePathSpecial(sf::Texture texture) {
	this->texturePath_special = texture;
}
// Sets window
void Enemy::assignWindow(sf::RenderWindow* renWin) {
	this->renWin = renWin;
	this->windowWidth = renWin->getSize().x;
}
// Sets texture
void Enemy::assignTexture() {
	sf::Texture t;
	t = this->texturePath_idle;
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
		if (!this->attacking) {
			this->animationSpeed = 0.17f;
		}

		// Draw animation
		if (clock.getElapsedTime().asSeconds() > this->animationSpeed) {
			if (isAlive() && !this->attacking) {
				if (rectSrcSprite.left == 160) rectSrcSprite.left = 0;
				else rectSrcSprite.left += 40;
			}
			else if (isAlive() && this->attacking) {
				if (rectSrcSprite.left == 80) {
					attack(this->targetHealth);
				}
				if (rectSrcSprite.left == 160) {
					rectSrcSprite.left = 0;
				}
				else {
					rectSrcSprite.left += 40;
				}
			}
			else {
				if (rectSrcSprite.left < 160) rectSrcSprite.left += 40;
			}
			this->sprite.setTextureRect(rectSrcSprite);
			clock.restart();
		}

		// Draw sprite
		this->sprite.setTexture(this->texture);
		this->renWin->draw(this->sprite);

		// Draw others
		drawHealthBar();
		if(hitbox_visibility) drawHitbox();
	}

	if (!this->alive) {
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
	//this->bar.setOutlineThickness(1);
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
	this->hitbox.setOrigin(-(this->hitbox.getGlobalBounds().width / 4), 0);
	this->hitbox.setPosition(this->posX, this->posY);
	this->renWin->draw(hitbox);
}
// Hide hitbox
void Enemy::showHitbox() {
	this->hitbox_visibility = true;
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
// Offense
void Enemy::attack(float* targetHealth) {
	*targetHealth -= getAtkDmg();
}
void Enemy::setTarget(int boundary, float* targetHealth) {
	changeBound(boundary);
	this->targetHealth = targetHealth;
}
// Self Status
void Enemy::takeDamage(int dmg) {
	std::cout << "Taking dmg" << std::endl;
	if (this->health != 0) {
		this->health -= dmg;
		if (this->health <= 0)
			die();
	}
}
void Enemy::die() {
	this->health = 0;
	this->attacking = false;
	this->rectSrcSprite.left = 0;
	sf::Texture t;
	t = texturePath_death;
	changeTexture(t);
	this->alive = false;
}
void Enemy::moveX() {
	sf::Texture t;
	if (this->alive) {
		// Move
		if (this->posX + this->spriteWidth < this->currentBound && isAlive()) {
			this->sprite.move(0.05f, 0);
		}
		// Stop at bounds and change texture to attack
		if (withinBounds()) {
			this->attacking = true;
			t = texturePath_attack;
			changeTexture(t);
		}
		// Change texture back to walk
		else {
			this->attacking = false;
			t = texturePath_idle;
			changeTexture(t);
		}
	}
	draw();
}
bool Enemy::isAlive() {
	return this->alive;
}
// Get methods
float Enemy::getHealth() {
	return this->health;
}
int Enemy::getAtkDmg() {
	return this->atk;
}
float Enemy::getAtkSpeed() {
	return this->as;
}
float Enemy::getTargetHealth() {
	return *this->targetHealth;
}

// Temps
void Enemy::getFrame() {
	std::cout << "speed: " << this->rectSrcSprite.left << std::endl;
}