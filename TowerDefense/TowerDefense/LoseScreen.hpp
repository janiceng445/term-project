#pragma once
#include "cScreen.hpp"

class LoseScreen : public cScreen
{
private:
	sf::Vector2f dimensions;
	sf::Texture loseBack;
	sf::Sprite loseBackSprite;
	sf::Text restartGameText;
	sf::Text exitGameText;
	sf::Font pixeled;
	sf::CircleShape menuCursor;
	bool hasClicked;

	//Audio
	sf::SoundBuffer menuSelect_buffer;
	sf::Sound menuSelect;

public:
	LoseScreen(void);
	int Run(sf::RenderWindow &window);
};
