#pragma once
#include "Monster.h"

class Lancer : public Monster
{
private:
	bool canSpecial;
	bool usingSpecial;
	int barrierHP;
	int barrierHPMax;
	sf::CircleShape barrier;
	float radius;
	float radiusMax;

	float radar;
	bool radarActivated;

	int barrierDuration;
	int barrierDurationMax;
	int barrierRecharge;

public:
	Lancer();
	Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score, MonsterType monsterType);
	void run() override;
	void useSpecialAbility();
	bool isUsingSpecial() override;

	// Barrier
	void drawBarrier();
	sf::FloatRect virtual getSpriteGlobalBounds() override;
	float virtual getDetectionDistance() override;
	void virtual takeDamage(int dmg);

	// Radar
	void detect();


	bool checkIfSpecial();
	~Lancer();
};
