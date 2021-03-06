#pragma once
#include "cScreen.hpp"


class StartScreen : public cScreen
{
private:
	sf::Vector2f dimensions;
	sf::Texture menuBack;
	sf::Sprite menuSprite;
	sf::Text startGameText;
	sf::Text fillerText;
	sf::Text exitGameText;
	sf::Text creditsTxt;
	sf::Font pixeled;
	sf::CircleShape menuCursor;

	//Audio
	sf::SoundBuffer menuSelect_buffer;
	sf::Sound menuSelect;

public:
	StartScreen(void);
	virtual int Run(sf::RenderWindow &window);

};
