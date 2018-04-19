#pragma once
#include "cScreen.hpp"

class StartScreen : public cScreen {
	private:
	sf::Vector2f dimensions;
	sf::Texture menuBack;
	sf::Sprite menuSprite;
	sf::Text startGameText;
	sf::Text fillerText;
	sf::Text exitGameText;
	sf::Font pixeled;
	sf::CircleShape menuCursor;

	public:
	StartScreen(void);
	virtual int Run(sf::RenderWindow &window);

};
