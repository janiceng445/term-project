#include <iostream>
#include "cScreen.hpp"
#include "WinScreen.hpp"

WinScreen::WinScreen() {}

int WinScreen::Run(sf::RenderWindow &window) {
	sf::Event event;
	bool running = true;

	int selected = 0;

	dimensions.x = window.getSize().x;
	dimensions.y = window.getSize().y;

	//loading background
	if (!winBack.loadFromFile("Images/menuback.png"))
	{
		std::cerr << "menuback failed to load" << std::endl;
		return -1;
	}
	winBackSprite.setTexture(winBack);

	//loading menu font
	if (!pixeled.loadFromFile("fonts/Pixeled.ttf"))
	{
		std::cerr << "pixeled failed to load" << std::endl;
		return -1;
	}

	//setting up menu text
	restartGameText.setFont(pixeled);
	exitGameText.setFont(pixeled);

	restartGameText.setCharacterSize(24);
	exitGameText.setCharacterSize(24);

	restartGameText.setFillColor(sf::Color::White);
	exitGameText.setFillColor(sf::Color::White);

	restartGameText.setString("Play Again");
	exitGameText.setString("Exit Game");

	restartGameText.setPosition((dimensions.x / 2) - 72, (dimensions.y / 2) - 35);
	exitGameText.setPosition((dimensions.x / 2) - 72, (dimensions.y / 2) + 35);

	//preparing menu cursor
	menuCursor.setRadius(6.0);
	menuCursor.setFillColor(sf::Color::White);
	menuCursor.setPosition(restartGameText.getPosition().x - 30, restartGameText.getPosition().y);

	while (running)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
						if (selected == 0)
						{
							selected = 1;
							menuCursor.setPosition(restartGameText.getPosition().x - 30, exitGameText.getPosition().y);
						}
						else if (selected == 1)
						{
							selected = 0;
							menuCursor.setPosition(restartGameText.getPosition().x - 30, restartGameText.getPosition().y);
						}
						break;

					case sf::Keyboard::Down:
						if (selected == 0)
						{
							selected = 1;
							menuCursor.setPosition(restartGameText.getPosition().x - 30, exitGameText.getPosition().y);
						}
						else if (selected == 1)
						{
							selected = 0;
							menuCursor.setPosition(restartGameText.getPosition().x - 30, restartGameText.getPosition().y);
						}
						break;

					case sf::Keyboard::Return:
						if (selected == 0)
						{
							window.clear();
							return 1;
						}
						else if (selected == 1) return -1;
						break;

					default:
						break;
				}
			}
		}
		//drawing menu objects
		window.draw(winBackSprite);
		window.draw(restartGameText);
		window.draw(exitGameText);
		window.draw(menuCursor);
		window.display();
		window.clear();
	}

	return -1;
}
