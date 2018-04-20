#pragma once
#include "cScreen.hpp"

class LoseScreen : public cScreen {
	private:
	sf::Vector2f dimensions;
	sf::Texture loseBack;
	sf::Sprite loseBackSprite;
	sf::Text restartGameText;
	sf::Text exitGameText;
	sf::Font pixeled;
	sf::CircleShape menuCursor;

	public:
	LoseScreen(void);
	int Run(sf::RenderWindow &window);
};
