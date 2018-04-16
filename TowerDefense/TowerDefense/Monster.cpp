#include "Monster.h"

Monster::Monster() {}
Monster::Monster(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP)
{
	int r = (rand() % 41 - 20) * 2; // For random spawning y coordinate

									// Attributes
	this->AD = AD / 2; // Explanation: attacks ticks twice
	this->HP = HP;
	this->isAlive = true;
	this->isAttacking = false;

	// Location Default
	this->x = -25;
	this->y = 375 + (float)r;

	// Animation
	this->aniPack = aniPack;
	setCurrentAnimation();
	this->aniSprite.setFrameTime(sf::seconds(0.2f));
	this->aniSprite.play();
	this->aniSprite.setLooped(true);
	this->aniSprite.setPosition(this->x, this->y);
	this->spriteWidth = aniPack.at(0).getFrame(0).width;
	this->spriteHeight = aniPack.at(0).getFrame(0).height;
	sf::Clock frameClock;
	// Healthbar
	addHealthBar();
	// Hitbox
	hitboxVisibility = true;
	this->hitbox_Width = this->spriteWidth * 0.7f;
	this->hitbox_Height = (float)this->spriteHeight;


	// Others
	this->window = win;
	this->targetedHealth = 0;
}

/////////////////////////////////////////// Animation ///////////////////////////////////////////

// Sets current animation
void Monster::setCurrentAnimation() {
	this->currentAnimation = &this->aniPack.at(0);
}
void Monster::setFrameTime(sf::Time* frameTime) {
	//this->frameTime = frameTime;
}
// Plays animation of currently selected status
void Monster::playAnimation() {
	this->aniSprite.play(*currentAnimation);
}
// Updates frame time
void Monster::update(sf::Time frameTime) {
	this->aniSprite.update(frameTime);
}
// Changes current animation status
void Monster::changeCurrentAnimation(int n) {
	this->currentAnimation = &this->aniPack.at(n);
}
// Runs the timers
void Monster::run() {
	sf::Time frameTime = this->frameClock.restart();
	if (isAttacking) {
		changeCurrentAnimation(1);
	}
	else if (!isAlive) {
		changeCurrentAnimation(2);
	}
	else {
		changeCurrentAnimation(0);
	}
	playAnimation();
	update(frameTime);
}
// Draws the sprite on the window
void Monster::draw() {
	this->window->draw(aniSprite);
	this->window->draw(hitbox);
}

/////////////////////////////////////////// Health Bar ///////////////////////////////////////////

void Monster::addHealthBar() {
	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f((float)this->spriteWidth, 5));
	this->bar = bar;
}
void Monster::updateHealthBar() {
	float hp = (float)this->HP / 100 * this->spriteWidth;
	// Changing color of bar if < 50%
	hp > 0.50 * this->spriteWidth ? bar.setFillColor(sf::Color::Green) :
		bar.setFillColor(sf::Color::Red);
	bar.setSize(sf::Vector2f(hp, 5));
	showHealthBar();
}
void Monster::showHealthBar() {
	this->bar.setPosition(this->x, this->y - 10);
	this->window->draw(this->bar);
}

/////////////////////////////////////////// Hitbox ///////////////////////////////////////////

// Draws hitbox
void Monster::drawHitbox() {
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineColor(sf::Color::Red);
	this->hitbox.setOutlineThickness(1);
	this->hitbox.setSize(sf::Vector2f(this->hitbox_Width, this->hitbox_Height));
	this->hitbox.setOrigin(-(this->hitbox.getGlobalBounds().width / 4), 0);
	this->hitbox.setPosition(this->x, this->y);
	this->window->draw(this->hitbox);
}
// Show hitbox
void Monster::showHitbox() {
	this->hitboxVisibility = true;
}
sf::Vector2f Monster::getHitbox_Dim() {
	sf::Vector2f dim(this->hitbox_X + this->hitbox_Width, this->hitbox_Y - this->hitbox_Height);
	return dim;
}

/////////////////////////////////////////// Location ///////////////////////////////////////////

// Set spawn location
void Monster::changeY() {
	// Random number generator
	int r = (rand() % 41 - 20) * 3; // For random spawning y coordinate
	this->y += r;
}

void Monster::setStartingPosition(float x, float y) {
	this->x = x;
	this->y = y;
	this->aniSprite.setPosition(this->x, this->y);
}
// Moves the sprite
void Monster::attackMove() {
	// Updates x and y with current location
	this->x = aniSprite.getPosition().x;
	this->y = aniSprite.getPosition().y;
	// Move
	if (this->isAlive) {
		if (this->x < this->stoppingPoint) {
			this->aniSprite.move(0.05f, 0);
		}
		if (this->x > this->stoppingPoint - 10 && this->aniSprite.getCurrentFrame() == 3) {
			attack();
		}
	}
	updateHealthBar();
	if (hitboxVisibility) drawHitbox();
}

/////////////////////////////////////////// Behavior ///////////////////////////////////////////

// Sets target via x-location and health
void Monster::setTarget(int x, int* targetedHealth) {
	this->stoppingPoint = x;
	this->targetedHealth = *targetedHealth;
}

// Attacks a targeted health
void Monster::attack() {
	if (isAlive) {
		isAttacking = true;
		if (clock.getElapsedTime().asSeconds() > 0.17f) {
			std::cout << "Attacking" << std::endl;
			this->targetedHealth -= this->AD;
			clock.restart();
		}
	}
}

// Take damage
void Monster::takeDamage(int dmg) {
	this->HP -= dmg;
	if (this->HP <= 0) {
		this->HP = 0;
		die();
	}
}

// Dies
void Monster::die() {
	this->isAlive = false;
}

/////////////////////////////////////////// Other ///////////////////////////////////////////



Monster::~Monster()
{
}