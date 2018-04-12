#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Timer.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

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
	sf::Clock clock;
	// Load texture and push into pack
	sf::Texture skelly_texture;
	std::vector<sf::Texture> texturePack;
	if (!skelly_texture.loadFromFile("images/enemies/skelly.png"))
		std::cout << "Error loading skelly texture" << std::endl;
	else texturePack.push_back(skelly_texture);
	if (!skelly_texture.loadFromFile("images/enemies/skelly_attack.png"))
		std::cout << "Error loading skelly attack texture" << std::endl;
	else texturePack.push_back(skelly_texture);
	if (!skelly_texture.loadFromFile("images/enemies/skelly_death.png"))
		std::cout << "Error loading skelly death texture" << std::endl;
	else texturePack.push_back(skelly_texture);
	if (!skelly_texture.loadFromFile("images/enemies/skelly_special.png"))
		std::cout << "Error loading skelly special texture" << std::endl;
	else texturePack.push_back(skelly_texture);

	// Wave of enemies
	std::vector<std::vector<Enemy>> waveList;
	int waveRound = 0;
	std::vector<Enemy> wave;

	////////////////////////////////  Temporary Timer ////////////////////////////////
	int startTime = 0;
	int currentTime = 0;
	int delay = 10;

	// Custom timer
	Timer timer_attackPulse(500);
	float tempTowerHealth = 1000;
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

		if (clock.getElapsedTime().asSeconds() > 3.0f) {
			Enemy newEnemy(&window, 100, 5, 0.3f, 0.5f, &texturePack);
			newEnemy.setTarget(200, 1000);
			newEnemy.draw();
			wave.push_back(newEnemy);
			clock.restart();
		}

		for (unsigned int i = 0; i < wave.size(); i++) {
			wave[i].moveX();
		}

		// Timer & Cheat code
		++currentTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (currentTime - startTime > delay)) {
			startTime = currentTime;
			currentTime = 0;
			//newEnemy.takeDamage(25);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////


		window.display();
	}

	return 0;
}