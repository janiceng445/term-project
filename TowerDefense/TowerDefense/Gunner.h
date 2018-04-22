#pragma once
#include "Monster.h"
#include "Lancer.h"

class Gunner : public Monster
{
private:
	Monster * findLancer();
	std::vector<Monster*>* wave;
	int randomPoint;
	int targetedPoint;
	int shootingPoint;
	int newStoppingPoint;
	int r;

public:
	Gunner();
	Gunner(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score, MonsterType monsterType, std::vector<Monster*>* wave);
	void attackMove();
	~Gunner();
};