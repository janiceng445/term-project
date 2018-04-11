#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <thread>
#include <chrono>
#include <iostream>

const double PI = 3.141592653589793238463;

int main()
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(720, 480), "Defend the Joe!");

	// Loading files
	sf::Texture background;
	if (!background.loadFromFile("images/background.png")) {
		return -1;
	}
	sf::Texture joeTexture;
	if (!joeTexture.loadFromFile("images/revolverJoe.png")) {
		return -1;
	}
	sf::Texture armTexture;
	if (!armTexture.loadFromFile("images/arm.png")) {
		return -1;
	}
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("images/bullet.png")) {
		return -1;
	}

	////////////////////////////// Temporary Placement ///////////////////////////////
	
	Enemy newEnemy(&window, 100, 5, 0.5f);

	////////////////////////////////  Temporary Timer ////////////////////////////////
	int startTime = 0;
	int currentTime = 0;
	int delay = 10;
	//////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		///////////////////////////////////////////// Gerard /////////////////////////////////////////////
		sf::Sprite background(background);
		sf::Sprite joeSprite;
		sf::Sprite armSprite;
		sf::Sprite bulletSprite;
		joeSprite.setTexture(joeTexture);
		joeSprite.setPosition(630, 210);
		armSprite.setTexture(armTexture);
		armSprite.setPosition(650, 248);
		armSprite.setOrigin(20, 4);
		armSprite.setRotation((180.0 / PI) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x));
		//sets rotation of arm based on mouse location (gun points at mouse pointer)
		bulletSprite.setTexture(bulletTexture);

		window.draw(background);
		window.draw(armSprite);
		window.draw(joeSprite);
		window.draw(bulletSprite);

		///////////////////////////////////////////// Janice /////////////////////////////////////////////
		// Enemy Class (Temporary Placement)
		newEnemy.moveX();
		newEnemy.changeBound(300);

		// Timer & Cheat code
		++currentTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (currentTime - startTime > delay)) {
			startTime = currentTime;
			currentTime = 0;
			newEnemy.takeDamage(25);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////


		window.display();
	}

	return 0;
}