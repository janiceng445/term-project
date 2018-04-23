#include <iostream>
#include "cScreen.hpp"
#include "LoseScreen.hpp"

LoseScreen::LoseScreen() {}

int LoseScreen::Run(sf::RenderWindow &window)
{
	sf::Event event;
	bool running = true;
	hasClicked = false;

	int selected = 0;

	dimensions.x = (float) window.getSize().x;
	dimensions.y = (float) window.getSize().y;

	//loading background
	if (!loseBack.loadFromFile("Images/menuback.png"))
	{
		std::cerr << "menuback failed to load" << std::endl;
		return -1;
	}
	loseBackSprite.setTexture(loseBack);

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

	// setting up black transparent box
	sf::RectangleShape box;
	box.setFillColor(sf::Color(0, 0, 0, 175));
	box.setSize(sf::Vector2f(350, 150));
	box.setOrigin(box.getSize().x / 2, box.getSize().y / 2);
	box.setPosition(dimensions.x / 2, dimensions.y / 2 - 35);

	//setting up menu text
	restartGameText.setFont(pixeled);
	exitGameText.setFont(pixeled);

	restartGameText.setCharacterSize(24);
	exitGameText.setCharacterSize(24);

	restartGameText.setFillColor(sf::Color::White);
	exitGameText.setFillColor(sf::Color::White);

	restartGameText.setString("Restart Game");
	exitGameText.setString("Exit Game");

	int rg_width = (int) restartGameText.getGlobalBounds().width;
	int rg_height = (int)restartGameText.getGlobalBounds().height;
	int eg_width = (int) exitGameText.getGlobalBounds().width;
	int eg_height = (int) exitGameText.getGlobalBounds().height;

	int x_offset = rg_width / 2;
	int y_offset = 60;

	restartGameText.setPosition((dimensions.x / 2) - x_offset, (dimensions.y / 2) - y_offset);
	exitGameText.setPosition((dimensions.x / 2) - x_offset, (dimensions.y / 2) + rg_height + eg_height / 2 - y_offset);

	//preparing menu cursor
	menuCursor.setRadius(6.0);
	menuCursor.setFillColor(sf::Color::White);
	menuCursor.setPosition(restartGameText.getPosition().x - 30, restartGameText.getPosition().y);

	while (running)
	{
		window.setMouseCursorVisible(true);
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
						menuSelect.play();
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
						menuSelect.play();
						selected = 1;
						menuCursor.setPosition(restartGameText.getPosition().x - 30, exitGameText.getPosition().y);
					}
					else if (selected == 1)
					{
						menuSelect.play();
						selected = 0;
						menuCursor.setPosition(restartGameText.getPosition().x - 30, restartGameText.getPosition().y);
					}
					break;

				case sf::Keyboard::Return:
					if (selected == 0)
					{
						menuSelect.play();
						window.clear();
						return 1;
					}
					else if (selected == 1) return -1;
					break;

				default:
					break;
				}
			}

			else if (event.type == sf::Event::MouseMoved)
			{
				if (sf::Mouse::getPosition(window).y < restartGameText.getPosition().y + rg_height)
				{
					menuSelect.play();
					selected = 0;
					menuCursor.setPosition(restartGameText.getPosition().x - 30, restartGameText.getPosition().y);
				}
				else
				{
					menuSelect.play();
					selected = 1;
					menuCursor.setPosition(exitGameText.getPosition().x - 30, exitGameText.getPosition().y);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased && hasClicked)
			{
				if (selected == 0)
				{
					menuSelect.play();
					window.clear();
					return 1;
				}
				else if (selected == 1) return -1;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				menuSelect.play();
				hasClicked = true;
			}
		}
		//drawing menu objects
		window.draw(loseBackSprite);
		window.draw(box);
		window.draw(restartGameText);
		window.draw(exitGameText);
		window.draw(menuCursor);
		window.display();
		window.clear();
	}

	return -1;
}
