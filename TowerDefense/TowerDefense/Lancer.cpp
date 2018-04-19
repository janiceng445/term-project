#include "Lancer.h"

Lancer::Lancer()
{
}

Lancer::Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score) : Monster(win, aniPack, AD, HP, score) {
	special = true;
	canSpecial = true;
	usingSpecial = false;


	// Attribute
	barrierHPMax = 1500;
	barrierHP = barrierHPMax;
	radarActivated = true;

	// Barrier animation
	radiusMax = barrierHPMax;
	radius = barrierHP;
	barrier.setRadius(radius);
	barrierDurationMax = 500;
	barrierDuration = barrierDurationMax;
	barrierRecharge = 0;
}

// Override Monster run
void Lancer::run() {
	// Disables usingSpecial for all conditions
	if (!canSpecial || barrierHP == 0) {
		usingSpecial = false;
	}
	// Recharge barrier
	if (!canSpecial && barrierHP != barrierHPMax) {
		barrierRecharge++;
	}
	// Barrier fully recharged and restored
	if (barrierRecharge >= 3000) {
		canSpecial = true;
		barrierHP = barrierHPMax;
		radius = barrierHPMax;
		barrierRecharge = 0;
	}
	if (!stopRunning) {
		sf::Time frameTime = this->frameClock.restart();
		if (isAttacking && isAlive) {
			canSpecial = false;
			usingSpecial = false;
			changeCurrentAnimation(1);
		}
		else if (!isAlive) {
			animationSpeed = DEFAULT_ANI_SPEED;
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
		else if (isAlive && usingSpecial && barrierHP != 0) {
			changeCurrentAnimation(3);
			barrierDuration--;
			drawBarrier();
			movementSpeed = 0.02f;
			animationSpeed = 0.01f;
			if (barrierDuration <= 0) {
				barrierDuration = barrierDurationMax;
				usingSpecial = false;
			}
		}
		else {
			movementSpeed = DEFAULT_MVMT_SPEED;
			animationSpeed = DEFAULT_ANI_SPEED;
			changeCurrentAnimation(0);
			detect();
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

// Special Ability customization
void Lancer::useSpecialAbility() {
	if (canSpecial) {
		usingSpecial = true;
	}
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
	// Color
	barrier.setFillColor(sf::Color(105, 190, 255, 75));
	// Changing size
	radius = barrierHP / 10;
	barrier.setRadius(radius);
	barrier.setOrigin(barrier.getGlobalBounds().width / 2, barrier.getGlobalBounds().height / 2);

	window->draw(barrier);
}
/////////////////////////////////// Radar ///////////////////////////////////

void Lancer::detect() {
	radar = aniSprite.getPosition().x + 150;
}


/////////////////////////////////// Location ///////////////////////////////////
sf::FloatRect Lancer::getSpriteGlobalBounds() {
	if (usingSpecial)
		return barrier.getGlobalBounds();
	else 
		return aniSprite.getGlobalBounds();
}
float Lancer::getDetectionDistance() {
	return radar;
}
/////////////////////////////////// Behavior ///////////////////////////////////
void Lancer::takeDamage(int dmg) {
	if (usingSpecial && canSpecial) {
		this->barrierHP -= 0.25 * barrierHPMax;
	}
	else {
		this->HP -= dmg;
	}

	// Remove barrier if destroyed
	if (barrierHP <= 0 || barrier.getRadius() < spriteWidth) {
		this->barrierHP = 0;
		canSpecial = false;
	}

	if (this->HP <= 0) {
		this->HP = 0;
		die();
	}
}

Lancer::~Lancer()
{
}
