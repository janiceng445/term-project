#pragma once
#include "Monster.h"

class Lancer : public Monster
{
private:
	bool usingSpecial;
	int detectionRadius;
	sf::CircleShape detectbubble;

public:
	Lancer();
	Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score);

	virtual void run();
	void useSpecialAbility();
	bool detectRadius();
	void drawDetectionBubble();
	//virtual sf::FloatRect getSpriteGlobalBounds();

	bool checkIfSpecial();
	~Lancer();
};

