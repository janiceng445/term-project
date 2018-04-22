#pragma once
#include "cScreen.hpp"

class WinScreen : public cScreen
{
private:
	sf::Vector2f dimensions;
	sf::Texture winBack;
	sf::Sprite winBackSprite;
	sf::Text restartGameText;
	sf::Text exitGameText;
	sf::Font pixeled;
	sf::CircleShape menuCursor;
	bool hasClicked;

	//Audio
	sf::SoundBuffer menuSelect_buffer;
	sf::Sound menuSelect;

public:
	WinScreen(void);
	int Run(sf::RenderWindow &window);
};
#pragma once
