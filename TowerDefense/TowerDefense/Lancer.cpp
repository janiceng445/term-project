#include "Lancer.h"

Lancer::Lancer()
{
}

Lancer::Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score) : Monster(win, aniPack, AD, HP, score) {
	special = true;
	usingSpecial = true;


	// Attribute
	barrierHP = 150;

	// Barrier animation
	float radius = spriteWidth * 2;
	barrier.setRadius(radius);
	barrier.setOutlineColor(sf::Color::Blue);
	barrier.setOutlineThickness(1);
	barrier.setOrigin(barrier.getGlobalBounds().width / 2, barrier.getGlobalBounds().height / 2);
}

// Override Monster run
void Lancer::run() {
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
		else if (isAlive && usingSpecial) {

			useSpecialAbility();
			movementSpeed = 0.02f;
			animationSpeed = 0.01f;

			if (aniSprite.getCurrentFrame() == 4) {
				currentFrame = 0;
			}
			changeCurrentAnimation(3);
			if (aniSprite.getCurrentFrame() == 4 && aniSprite.getAnimation()->getFrame(aniSprite.getCurrentFrame()).top == spriteHeight * 3) {
				
			}
		}
		else {
			movementSpeed = DEFAULT_MVMT_SPEED;
			animationSpeed = DEFAULT_ANI_SPEED;
			changeCurrentAnimation(0);
		}
		playAnimation();
		update(frameTime);

		// Check if condition met for special ability



	}
	if (isPermaDead) {
		decay_timer--;
		if (decay_timer == 0) {
			decay_timer = 0;
			stopDrawing = true;
		}
	}
}

// Special Ability customization
void Lancer::useSpecialAbility() {
	drawBarrier();
}

// Checks if it has special ability
bool Lancer::checkIfSpecial() {
	return special;
}


/////////////////////////////////// Barrier ///////////////////////////////////

void Lancer::drawBarrier() {
	sf::Vector2f position;
	position.x = x + spriteWidth / 2;
	position.y = y + spriteHeight / 2;
	barrier.setPosition(position);

	// Default color
	barrier.setFillColor(sf::Color(105, 190, 255, 100));


	window->draw(barrier);
}
sf::FloatRect Lancer::getSpriteGlobalBounds() {
	if (usingSpecial) 
		return barrier.getGlobalBounds();
	else 
		return aniSprite.getGlobalBounds();
}
void Lancer::takeDamage(int dmg) {
	if (usingSpecial) {
		this->barrierHP -= dmg;
	}
	else {
		this->HP -= dmg;
	}

	// Remove barrier if destroyed
	if (barrierHP <= 0) {
		this->barrierHP = 0;
		usingSpecial = false;
	}

	if (this->HP <= 0) {
		this->HP = 0;
		die();
	}
}

Lancer::~Lancer()
{
}
