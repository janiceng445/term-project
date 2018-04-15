#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Timer.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Monster.h"
#include <cstdlib>

const double PI = 3.141592653589793238463;
float SKELLY_SPWN_TIMER = 5.0f;

int main()
{
	// Create window
	sf::Vector2i screenDimensions(720, 480);
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Defend the Joe!");

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
	float targetHealth = 200;
	float targets[3] = {50, 55, 60};
	int targetX[3] = { 150, 200, 250 };
	int currentTarget = 0;
	// Clocks
	sf::Clock clock;

	//////////////////////////////// Make idle sprite ////////////////////////////////
	
	sf::Texture skelly_texture;
	skelly_texture.loadFromFile("images/enemies/skelly.png");
	std::vector<Animation> skellyAni;

	Animation skelly_idle;
	skelly_idle.setSpriteSheet(skelly_texture);
	skelly_idle.addFrame(sf::IntRect(0, 0, 40, 49));
	skelly_idle.addFrame(sf::IntRect(40, 0, 40, 49));
	skelly_idle.addFrame(sf::IntRect(80, 0, 40, 49));
	skelly_idle.addFrame(sf::IntRect(120, 0, 40, 49));
	skelly_idle.addFrame(sf::IntRect(160, 0, 40, 49));
	skellyAni.push_back(skelly_idle);

	Animation skelly_attack;
	skelly_attack.setSpriteSheet(skelly_texture);
	skelly_attack.addFrame(sf::IntRect(0, 49, 40, 49));
	skelly_attack.addFrame(sf::IntRect(40, 49, 40, 49));
	skelly_attack.addFrame(sf::IntRect(80, 49, 40, 49));
	skelly_attack.addFrame(sf::IntRect(120, 49, 40, 49));
	skelly_attack.addFrame(sf::IntRect(160, 49, 40, 49));
	skellyAni.push_back(skelly_attack);

	Animation skelly_death;
	skelly_death.setSpriteSheet(skelly_texture);
	skelly_death.addFrame(sf::IntRect(0, 49, 40, 49));
	skelly_death.addFrame(sf::IntRect(40, 49, 40, 49));
	skelly_death.addFrame(sf::IntRect(80, 49, 40, 49));
	skelly_death.addFrame(sf::IntRect(120, 49, 40, 49));
	skelly_death.addFrame(sf::IntRect(160, 49, 40, 49));
	skellyAni.push_back(skelly_death);

	// Create a new testing monster
	int targetHP = 100;	

	//////////////////////////////// Wave of enemies /////////////////////////////////
	int waveRound = 0;
	std::vector<Monster> wave;

	

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
		
		// Skelly Spawner
		int r = (rand() % 6) - 3;
		unsigned int skellyMax = 5;
		if (clock.getElapsedTime().asSeconds() > SKELLY_SPWN_TIMER + r && wave.size() <= skellyMax) {
			Monster skelly(&window, skellyAni, 10, 100);
			skelly.setTarget(450, &targetHP);
			wave.push_back(skelly);
			clock.restart();
		}

		// Targets and health
		/*if (targets[0] <= 0) {
			targets[0] = 0;
			currentTarget = 1;
		}
		if (targets[1] <= 0) {
			targets[1] = 0;
			currentTarget = 2;
		}
		if (targets[2] <= 0) { // Game should be over after this
			targets[2] = 0;
			for (unsigned int i = 0; i < wave.size(); i++) {
				wave[i].setTarget(720, 0);
			}
		}*/

		//////////////////////// TEST TAKE DAMAGE CODE ////////////////////////
		/*if (!wave.empty() && wave.back().getX() >= 100 && temp.getElapsedTime().asSeconds() > 1.5f) {
			wave.back().takeDamage(25);
			if (wave.back().getHealth() == 0) {
				wave.pop_back();
			}
			temp.restart();
		}*/
		///////////////////////////////////////////////////////////////////////

		for (unsigned int i = 0; i < wave.size(); i++) {
			wave[i].run();
			wave[i].draw();
			wave[i].attackMove();
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////


		window.display();
	}

	return 0;
}