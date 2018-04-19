#include <iostream>
#include "StartScreen.hpp"

StartScreen::StartScreen() {}

int StartScreen::Run(sf::RenderWindow &window)
{
	bool running = true;
	int selected = 0;
	sf::Event event;

	dimensions.x = window.getSize().x;
	dimensions.y = window.getSize().y;

	//loading background
	if (!menuBack.loadFromFile("Images/menuback.png"))
	{
		std::cerr << "menuback failed to load" << std::endl;
		return -1;
	}
	menuSprite.setTexture(menuBack);

	//loading menu font
	if (!pixeled.loadFromFile("fonts/Pixeled.ttf"))
	{
		std::cerr << "pixeled failed to load" << std::endl;
		return -1;
	}

	//setting up menu text
	startGameText.setFont(pixeled);
	fillerText.setFont(pixeled);
	exitGameText.setFont(pixeled);

	startGameText.setCharacterSize(24);
	fillerText.setCharacterSize(24);
	exitGameText.setCharacterSize(24);

	startGameText.setFillColor(sf::Color::Magenta);
	fillerText.setFillColor(sf::Color::Magenta);
	exitGameText.setFillColor(sf::Color::Magenta);

	startGameText.setString("Start Game");
	fillerText.setString("Filler Text");
	exitGameText.setString("Exit Game");

	startGameText.setPosition(dimensions.x / 2, (dimensions.y / 2) - 30);
	fillerText.setPosition(dimensions.x / 2, (dimensions.y / 2));
	exitGameText.setPosition(dimensions.x / 2, (dimensions.y / 2) + 30);

	//preparing menu cursor
	menuCursor.setRadius(6.0);
	menuCursor.setFillColor(sf::Color::White);
	menuCursor.setPosition(startGameText.getPosition().x - 30, startGameText.getPosition().y);

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
						selected = 2;
						menuCursor.setPosition(startGameText.getPosition().x - 30, exitGameText.getPosition().y);
					}
					else if (selected == 1)
					{
						selected = 0;
						menuCursor.setPosition(startGameText.getPosition().x - 30, startGameText.getPosition().y);
					}
					else if (selected = 2)
					{
						selected = 1;
						menuCursor.setPosition(startGameText.getPosition().x - 30, fillerText.getPosition().y);
					}
					break;

				case sf::Keyboard::Down:
					if (selected == 0)
					{
						selected = 1;
						menuCursor.setPosition(startGameText.getPosition().x - 30, fillerText.getPosition().y);
					}
					else if (selected == 1)
					{
						selected = 2;
						menuCursor.setPosition(startGameText.getPosition().x - 30, exitGameText.getPosition().y);
					}
					else if (selected = 2)
					{
						selected = 0;
						menuCursor.setPosition(startGameText.getPosition().x - 30, startGameText.getPosition().y);
					}
					break;

				case sf::Keyboard::Return:
					if (selected == 0)
					{
						window.clear();
						return 0;
					}
					else if (selected == 2) return -1;
					break;

				default:
					break;
				}
			}
		}
		//drawing menu objects
		window.draw(menuSprite);
		window.draw(startGameText);
		window.draw(fillerText);
		window.draw(exitGameText);
		window.draw(menuCursor);
		window.display();
		window.clear();
	}

	return -1;
}
