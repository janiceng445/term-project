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

	sf::CircleShape radar;
	float radiusRadar;
	bool radarActivated;

	int barrierDuration;
	int barrierDurationMax;
	int barrierRecharge;

public:
	Lancer();
	Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score);

	void run() override;
	void useSpecialAbility();

	// Barrier
	void drawBarrier();
	sf::FloatRect virtual getSpriteGlobalBounds() override;
	sf::FloatRect virtual getDetectionRadius() override;
	void virtual takeDamage(int dmg);

	// Radar
	void drawRadar();


	bool checkIfSpecial();
	~Lancer();
};

