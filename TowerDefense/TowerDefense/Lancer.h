#pragma once
#include "Monster.h"

class Lancer : public Monster
{
private:
	bool usingSpecial;
	int barrierHP;
	sf::CircleShape barrier;

public:
	Lancer();
	Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score);

	void run() override;
	void useSpecialAbility();

	// Barrier
	void drawBarrier();
	sf::FloatRect virtual getSpriteGlobalBounds() override;
	void virtual takeDamage(int dmg);

	bool checkIfSpecial();
	~Lancer();
};

