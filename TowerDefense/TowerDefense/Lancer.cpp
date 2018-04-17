#include "Lancer.h"

Lancer::Lancer()
{
}

Lancer::Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP) : Monster(win, aniPack, AD, HP, score) {
	special = true;
	usingSpecial = false;
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
		else if (special) {
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

}

// Checks if it has special ability
bool Lancer::checkIfSpecial() {
	return special;
}


Lancer::~Lancer()
{
}
