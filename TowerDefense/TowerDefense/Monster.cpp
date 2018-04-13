#include "Monster.h"

Monster::Monster(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP)
{
	// Random number generator
	int r = rand() % 41 - 20; // For random spawning y coordinate

	// Attributes
	this->AD = AD / 2; // Explanation: attacks ticks twice
	this->HP = HP;
	this->isAlive = true;
	this->isAttacking = false;

	// Location Default
	this->x = 100;
	this->y = 400 + r;

	// Animation
	this->aniPack = aniPack;
	setCurrentAnimation();
	this->aniSprite.setFrameTime(sf::seconds(0.2f));
	this->aniSprite.play();
	this->aniSprite.setLooped(true);
	this->aniSprite.setPosition(this->x, this->y);
	this->spriteWidth = aniPack.at(0).getFrame(0).width;
	this->spriteHeight = aniPack.at(0).getFrame(0).height;
	// Healthbar
	addHealthBar();
	// Hotbox

	// Others
	this->window = win;
	this->targetedHealth = 0;
}

/////////////////////////////////////////// Animation ///////////////////////////////////////////

// Sets current animation
void Monster::setCurrentAnimation() {
	this->currentAnimation = &this->aniPack.at(0);
}
// Plays animation of currently selected status
void Monster::playAnimation() {
	this->aniSprite.play(*currentAnimation);
	this->aniSprite.update(*this->frameTime);
}
// Points frame time to main Frame Time
void Monster::setFrameTime(sf::Time* frameTime) {
	this->frameTime = frameTime;
}
// Changes current animation status
void Monster::changeCurrentAnimation(int n) {
	this->currentAnimation = &this->aniPack.at(n);
}
// Draws the sprite on the window
void Monster::draw() {
	if (isAttacking) changeCurrentAnimation(1);
	else if (!isAlive) changeCurrentAnimation(2);
	else changeCurrentAnimation(0);
	this->window->draw(aniSprite);
}

/////////////////////////////////////////// Health Bar ///////////////////////////////////////////

void Monster::addHealthBar() {
	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f((float) this->spriteWidth, 5));
	this->bar = bar;
}
void Monster::updateHealthBar() {
	float hp = (float) this->HP / 100 * this->spriteWidth;
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


/////////////////////////////////////////// Location ///////////////////////////////////////////

// Set spawn location
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
