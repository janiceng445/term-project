#include "Lancer.h"

Lancer::Lancer()
{
}

Lancer::Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score) : Monster(win, aniPack, AD, HP, score) {
	special = true;
	usingSpecial = false;
	detectionRadius = this->spriteWidth * 2;
	detectbubble.setRadius(detectionRadius);
	detectbubble.setOrigin(detectbubble.getGlobalBounds().width / 2, detectbubble.getGlobalBounds().height / 2);
	detectbubble.setFillColor(sf::Color(124, 183, 255, 100));
	detectbubble.setOutlineColor(sf::Color::Blue);
	detectbubble.setOutlineThickness(1);
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
			aniSprite.setFrameTime(sf::seconds(0.1f));
			changeCurrentAnimation(2);
			if (aniSprite.getCurrentFrame() == 4 && aniSprite.getAnimation()->getFrame(aniSprite.getCurrentFrame()).top == spriteHeight * 2) {
				stopRunning = true;
				isPermaDead = true;
			}
		}
		else if (isAlive && usingSpecial) {
			if (aniSprite.getCurrentFrame() == 4) {
				currentFrame = 0;
			}
			changeCurrentAnimation(3);
			if (aniSprite.getCurrentFrame() == 4 && aniSprite.getAnimation()->getFrame(aniSprite.getCurrentFrame()).top == spriteHeight * 3) {
				useSpecialAbility();
			}
		}
		else {
			changeCurrentAnimation(0);
			drawDetectionBubble();
		}
		playAnimation();
		update(frameTime);

		// Check if condition met for special ability
		//detectionRadius();


	}
	if (isPermaDead) {
		decay_timer--;
		if (decay_timer == 0) {
			decay_timer = 0;
			stopDrawing = true;
		}
	}
}

// Draws the detection bubble
void Lancer::drawDetectionBubble() {
	sf::Vector2f position;
	position.x = x + (spriteWidth / 2);
	position.y = y + (spriteHeight / 2);
	detectbubble.setPosition(position);
	window->draw(detectbubble);
}


// Special Ability customization
void Lancer::useSpecialAbility() {

}

// Checks if it has special ability
bool Lancer::checkIfSpecial() {
	return special;
}

// Detect radius
bool Lancer::detectRadius() {
	return false;
}

/*sf::FloatRect Lancer::getSpriteGlobalBounds() {
	if (usingSpecial) {
		//return detectbubble.getGlobalBounds();
	}
	return aniSprite.getGlobalBounds();
}*/

Lancer::~Lancer()
{
}
