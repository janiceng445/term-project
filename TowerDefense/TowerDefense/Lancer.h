#pragma once
#include "Monster.h"

class Lancer : public Monster
{
	private:
	bool usingSpecial;
	public:
	Lancer();
	Lancer(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score);

	void run() override;
	void useSpecialAbility();


	bool checkIfSpecial();
	~Lancer();
};
