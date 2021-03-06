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

	//loading audio
	if (!menuSelect_buffer.loadFromFile("Audio/menuSelect.wav"))
	{
		std::cerr << "menuSelect sound failed to load" << std::endl;
		return -1;
	}
	menuSelect.setBuffer(menuSelect_buffer);

	//start screen music
	sf::Music startscreenMusic;
	if (!startscreenMusic.openFromFile("Audio/startscreenMusic.wav"))
	{
		std::cerr << "start screen music failed to load" << std::endl;
		return -1;
	}
	startscreenMusic.setLoop(true);
	startscreenMusic.setVolume(40);
	startscreenMusic.play();

	// setting up black transparent box
	sf::RectangleShape box;
	box.setFillColor(sf::Color(0, 0, 0, 175));
	box.setSize(sf::Vector2f(325, 190));
	box.setOrigin(box.getSize().x / 2, box.getSize().y / 2);
	box.setPosition(dimensions.x / 2, dimensions.y / 2 - 35);

	sf::RectangleShape boxCredits;
	boxCredits.setFillColor(sf::Color(0, 0, 0, 175));
	boxCredits.setSize(sf::Vector2f(180, 200));
	boxCredits.setOrigin(boxCredits.getSize().x / 2, box.getSize().y / 2);
	boxCredits.setPosition(dimensions.x / 2, dimensions.y * 0.75f);

	//setting up menu text
	startGameText.setFont(pixeled);
	fillerText.setFont(pixeled);
	exitGameText.setFont(pixeled);
	creditsTxt.setFont(pixeled);

	startGameText.setCharacterSize(24);
	fillerText.setCharacterSize(24);
	exitGameText.setCharacterSize(24);
	creditsTxt.setCharacterSize(10);

	startGameText.setFillColor(sf::Color::White);
	fillerText.setFillColor(sf::Color::White);
	exitGameText.setFillColor(sf::Color::White);
	creditsTxt.setFillColor(sf::Color::White);

	startGameText.setString("Start Game");
	fillerText.setString("Credits");
	exitGameText.setString("Exit Game");
	creditsTxt.setString("Ben Anouge\nGerard Avecilla\nTom Ennis\nJanice Ng\nRicky Posada\nCaleb Reed\nSam Whittenberger");

	int sg_width = startGameText.getGlobalBounds().width;
	int sg_height = startGameText.getGlobalBounds().height;
	int ft_width = fillerText.getGlobalBounds().width;
	int ft_height = fillerText.getGlobalBounds().height;
	int eg_width = exitGameText.getGlobalBounds().width;
	int eg_height = exitGameText.getGlobalBounds().height;

	int x_offset = sg_width / 2;
	int y_offset = 50;

	startGameText.setPosition((dimensions.x / 2) - x_offset, (dimensions.y / 2) - sg_height - 10 - y_offset);
	fillerText.setPosition((dimensions.x / 2) - x_offset, (dimensions.y / 2) - y_offset);
	exitGameText.setPosition((dimensions.x / 2) - x_offset, (dimensions.y / 2) + ft_height + eg_height / 2 - y_offset);
	creditsTxt.setPosition(boxCredits.getPosition().x - boxCredits.getSize().x / 2 + 10, boxCredits.getPosition().y - boxCredits.getSize().y / 2 + 15);

	// Copyright
	sf::Text copyright;
	copyright.setCharacterSize(7);
	copyright.setFont(pixeled);
	copyright.setString("� 2018 Spring Team 50 COP3503 University of Florida All Rights Reserved");
	copyright.setPosition(dimensions.x - copyright.getGlobalBounds().width - 5, dimensions.y - copyright.getGlobalBounds().height - 6);
	copyright.setFillColor(sf::Color::White);


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
				return -1;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menuSelect.play();
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
					menuSelect.play();
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
					menuSelect.play();
					if (selected == 0)
					{
						window.clear();
						return 1;
					}
					else if (selected == 2) return -1;
					break;

				default:
					break;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (sf::Mouse::getPosition(window).y < startGameText.getPosition().y + sg_height)
				{
					menuSelect.play();
					selected = 0;
					menuCursor.setPosition(startGameText.getPosition().x - 30, startGameText.getPosition().y);
				}
				else if (sf::Mouse::getPosition(window).y < fillerText.getPosition().y + ft_height)
				{
					menuSelect.play();
					selected = 1;
					menuCursor.setPosition(startGameText.getPosition().x - 30, fillerText.getPosition().y);
				}
				else
				{
					menuSelect.play();
					selected = 2;
					menuCursor.setPosition(startGameText.getPosition().x - 30, exitGameText.getPosition().y);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				menuSelect.play();
				if (selected == 0)
				{
					window.clear();
					return 1;
				}
				else if (selected == 2) return -1;
			}
		}
		//drawing menu objects
		window.draw(menuSprite);
		window.draw(box);
		window.draw(startGameText);
		window.draw(fillerText);
		window.draw(exitGameText);
		window.draw(menuCursor);
		window.draw(copyright);

		if (selected == 1)
		{
			window.draw(boxCredits);
			window.draw(creditsTxt);
		}

		window.display();
		window.clear();
	}



	return -1;
}
