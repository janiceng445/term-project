#include "boss.h"


boss::boss(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score, MonsterType monsterType)
	: Monster(win, aniPack, AD, HP, score, monsterType)
{
	pushBack = false;
	pushBackNum = 0;
}
void boss::attackMove() {
	sprite_yCounter++;
	// Moving monster along y axis
	if (y <= window->getSize().y * 0.8 ||
		sprite_yCounter == sprite_yTimer)
	{
		distance_y = distance_y * -1;
		sprite_yCounter = 0;
	}
	// Updates x and y with current location
	this->x = aniSprite.getPosition().x;
	this->y = aniSprite.getPosition().y;
	// Move
	if (pushBackNum >= 100) {
		pushBackNum = 0;
		pushBack = false;
	}
	if (this->isAlive) {
		if (pushBack && pushBackNum < 100) {
			aniSprite.move(-0.1f, 0);
			++pushBackNum;
		}
		else if (this->y >= 600) { //move boss downwards if boss gets too high up
			this->aniSprite.move((float) ((((0.1 - 0.05) * (500 - this->HP)) / 500) + 0.1), -0.5f);
		}
		else if (this->y <= 150) { //move boss upwards if boss gets too low
			this->aniSprite.move((float) ((((0.1 - 0.01) * (500 - this->HP)) / 500) + 0.1), 0.5f);
		}
		else if (65 + this->y - sf::Mouse::getPosition(*window).y > 0) {
			this->aniSprite.move((float) ((((0.1 - 0.05) * (500 - this->HP)) / 500) + 0.1), (float) (0.1 * (450 - abs(65 + this->y - sf::Mouse::getPosition(*window).y)) / 450));
		}
		else if (65 + this->y - sf::Mouse::getPosition(*window).y < 0) {
			this->aniSprite.move((float) ((((0.1 - 0.05) * (500 - this->HP)) / 500) + 0.1), (float) (-0.1 * (450 - abs(65 + this->y - sf::Mouse::getPosition(*window).y)) / 450));
		}
		updateHealthBar();
		if (hitboxVisibility) drawHitbox();

		if (this->x > this->stoppingPoint - 10 && this->aniSprite.getCurrentFrame() == 3) {
			attack();
		}
	}
}
void boss::bossPushBack() {
	pushBack = true;
}