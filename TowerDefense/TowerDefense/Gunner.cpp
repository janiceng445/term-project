#include "Gunner.h"

float absVal(float x)
{
	if (x < 0)
	{
		return -x;
	}

	return x;
}

Gunner::~Gunner() {}
Gunner::Gunner() {}

Gunner::Gunner(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score, MonsterType monsterType, std::vector<Monster*>* wave)
	: Monster(win, aniPack, AD, HP, score, monsterType)
{
	this->wave = wave;
}

Monster* Gunner::findLancer()
{
	Monster* lancer = nullptr;
	float dist = 10000.0f;

	for (int i = 0; i < wave->size(); i++)
	{
		Monster* monster = wave->at(i);
		float dist2 = absVal(monster->getCurrentLocation().x - x);
		
		if (monster->monsterType == LANCER && monster->isUsingSpecial() && dist2 < dist)
		{
			lancer = monster;
			dist = dist2;
		}
	}

	return lancer;
}

void Gunner::attackMove()
{
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
	if (this->isAlive) {
		Monster* lancer = findLancer();

		if (lancer != nullptr)
		{
			stoppingPoint = lancer->getCurrentLocation().x;
		}
		else
		{
			stoppingPoint = 10;
		}

		if (this->x < this->stoppingPoint - 50) {
			this->aniSprite.move(movementSpeed, distance_y);
		}
		else if (this->x > this->stoppingPoint + 50) {
			this->aniSprite.move(-movementSpeed, distance_y);
		}
		else if (this->aniSprite.getCurrentFrame() == 3) {
			attack();
		}
	}
	updateHealthBar();
	if (hitboxVisibility) drawHitbox();
}