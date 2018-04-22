#include "Monster.h"
#include <SFML/Window/Mouse.hpp>
class boss : public Monster
{
private:
	bool pushBack;
	int pushBackNum;
public:
	boss(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score, MonsterType monsterType);
	void attackMove();
	void bossPushBack();
};