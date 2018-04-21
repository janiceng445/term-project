#include "Monster.h"

Monster::Monster()
{
}
Monster::Monster(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score)
{
	if (type == 1) 
	{
		size = 98;
	}


	int r = (rand() % 41 - 20) * 2; // For random spawning y coordinate

									// Attributes
	this->AD = AD / 2; // Explanation: attacks ticks twice
	this->HP = HP;
	this->max_HP = HP;
	float s = rand() / (float)RAND_MAX * 0.15;
	this->movementSpeed = DEFAULT_MVMT_SPEED + s;
	//this->movementSpeed = 1.0f;							// Dev cheat
	this->animationSpeed = DEFAULT_ANI_SPEED;
	this->isAlive = true;
	this->isAttacking = false;
	this->decay_timer = 1000;

	// Location Default
	this->x = -25;
	this->y = 0.84 * win->getSize().y + (float)r + 5;
	sprite_yCounter = 0;

	// Animation
	this->stopRunning = false;
	this->stopDrawing = false;
	this->aniPack = aniPack;
	setCurrentAnimation();
	this->aniSprite.setFrameTime(sf::seconds(0.15f));
	this->aniSprite.play();
	this->aniSprite.setLooped(true);
	this->aniSprite.setPosition(this->x, this->y);
	this->spriteWidth = aniPack.at(0).getFrame(0).width;
	this->spriteHeight = aniPack.at(0).getFrame(0).height;
	sf::Clock frameClock;
	// Healthbar
	addHealthBar();
	// Hitbox
	hitboxVisibility = false;
	this->hitbox_Width = this->spriteWidth * 0.7f;
	this->hitbox_Height = (float)this->spriteHeight;


	// Others
	this->window = win;
	this->targetedHealth = 0;
	this->score = score;
	c = rand() % 3 + 1; // Flip a coin

	// Sprite starting left or right stagger move
	if (c == 1)
	{
		distance_y = -movementSpeed * 0.7;
	}
	else if (c == 2)
	{
		distance_y = movementSpeed * 0.7;
	}
	else
	{
		distance_y = 0;
	}
	distance_y = 0; // <-- remove this to enable stagger movement
}

/////////////////////////////////////////// Animation ///////////////////////////////////////////

// Sets current animation
void Monster::setCurrentAnimation() {
	this->currentAnimation = &this->aniPack.at(0);
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
	if (!stopRunning) {
		sf::Time frameTime = this->frameClock.restart();
		if (isAttacking && isAlive) {
			changeCurrentAnimation(1);
		}
		else if (!isAlive) {
			if (aniSprite.getCurrentFrame() == 4) {
				currentFrame = 0;
			}
			aniSprite.setFrameTime(sf::seconds(animationSpeed));
			changeCurrentAnimation(2);
			if (aniSprite.getCurrentFrame() == 4 && aniSprite.getAnimation()->getFrame(aniSprite.getCurrentFrame()).top == spriteHeight * 2) {
				stopRunning = true;
				isPermaDead = true;
			}
		}
		else {
			isAttacking = false;
			changeCurrentAnimation(0);
		}
		playAnimation();
		update(frameTime);
	}
	if (isPermaDead) {
		decay_timer--;
		if (decay_timer == 0) {
			decay_timer = 0;
			stopDrawing = true;
		}
	}
}
// Draws the sprite on the window
void Monster::draw() {
	if (!stopDrawing) {
		this->window->draw(aniSprite);
		this->window->draw(hitbox);
		this->window->draw(this->bar);
	}
}

/////////////////////////////////////////// Health Bar ///////////////////////////////////////////

void Monster::addHealthBar() {
	bar.setSize(sf::Vector2f((float)this->spriteWidth, 5));
}
void Monster::updateHealthBar() {
	float hp = (float)this->HP / this->max_HP * this->spriteWidth;
	// Changing color of bar if < 50%
	hp > 0.50 * this->spriteWidth ? bar.setFillColor(sf::Color::Green) :
		bar.setFillColor(sf::Color::Red);
	bar.setSize(sf::Vector2f(hp, 5));
	showHealthBar();
}
void Monster::showHealthBar() {
	this->bar.setPosition(this->x, this->y - 10);
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
// Set spawn's starting position
void Monster::setStartingPosition(float x, float y) {
	this->x = x;
	this->y = y;
	this->aniSprite.setPosition(this->x, this->y);
}
// Moves the sprite
void Monster::attackMove() {
	sprite_yCounter++;
	// Moving monster along y axis
	if (y <= window->getSize().y * 0.8 || 
		sprite_yCounter == sprite_yTimer)
	{
		distance_y  = distance_y * -1;
		sprite_yCounter = 0;
	}
	// Updates x and y with current location
	this->x = aniSprite.getPosition().x;
	this->y = aniSprite.getPosition().y;
	// Move
	if (this->isAlive) {
		if (this->x < this->stoppingPoint) {
			isAttacking = false;
			this->aniSprite.move(movementSpeed, distance_y);
		}
		if (this->x > this->stoppingPoint - 10 && this->aniSprite.getCurrentFrame() == 3) {
			attack();
		}
	}
	updateHealthBar();
	if (hitboxVisibility) drawHitbox();
}
// Gets spawn's current location
sf::Vector2f Monster::getCurrentLocation() {
	sf::Vector2f location;
	location.x = aniSprite.getPosition().x + (spriteWidth / 2);
	location.y = aniSprite.getPosition().y + (spriteHeight / 2);
	return location;
}

// Gets hitboxes for projectiles to give results
sf::FloatRect Monster::getSpriteGlobalBounds() {
	return aniSprite.getGlobalBounds();
}
float Monster::getDetectionDistance() {
	return aniSprite.getPosition().x;
}

/////////////////////////////////////////// Behavior ///////////////////////////////////////////

// Sets target via x-location and health
void Monster::setTarget(int x, int* targetedHealth) {
	this->stoppingPoint = x;
	this->targetedHealth = targetedHealth;
}

// Attacks a targeted health
void Monster::attack() {
	if (isAlive) {
		isAttacking = true;
		if (clock.getElapsedTime().asSeconds() > 0.17f) {
			*this->targetedHealth -= this->AD;
			clock.restart();
		}
	}
}
void Monster::useSpecialAbility() {
	// Do nothing as base monster
}

// Take damage
void Monster::takeDamage(int dmg) {
	this->HP -= dmg;
	if (this->HP <= 0) {
		this->HP = 0;
		die();
	}
}
// Gets damage
int Monster::getDamage() {
	return this->AD;
}
// Checks if Monster is attacking
bool Monster::isCurrAttacking() {
	return this->isAttacking;
}
// Dies
void Monster::die() {
	this->isAlive = false;
	score->add(100);
}
// Gets isAlive value
bool Monster::isAliveFunc() {
	if (this->isAlive) {
		return true;
	}
	return false;
}
// Checks if dead
bool Monster::isDead() {
	if (this->isPermaDead) {
		return true;
	}
	return false;
}

/////////////////////////////////////////// Other ///////////////////////////////////////////


Monster::~Monster()
{
}