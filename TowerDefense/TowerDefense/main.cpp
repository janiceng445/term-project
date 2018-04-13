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

const double PI = 3.141592653589793238463;

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
	sf::Clock temp;
	std::vector<sf::Clock> clockList;

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

	//Animation* currentAnimation = &skelly_idle;

	// Set up AnimatedSprite
	//AnimatedSprite animatedSprite(sf::seconds(0.2f), true, false);
	//animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
	
	sf::Clock frameClock;

	// Create a new testing monster
	int targetHP = 100;
	Monster baby(&window, skellyAni, 10, 100);
	baby.setTarget(450, &targetHP);

	Monster baby2(&window, skellyAni, 10, 100);
	baby2.setStartingPosition(150, 340);
	baby2.setTarget(450, &targetHP);

	Monster baby3(&window, skellyAni, 10, 100);
	baby3.setStartingPosition(200, 345);
	baby3.setTarget(450, &targetHP);

	Monster baby4(&window, skellyAni, 10, 100);
	baby4.setStartingPosition(300, 355);
	baby4.setTarget(450, &targetHP);

	Monster baby5(&window, skellyAni, 10, 100);
	baby5.setStartingPosition(400, 352);
	baby5.setTarget(450, &targetHP);

	//////////////////////////////// Wave of enemies /////////////////////////////////
	std::vector<std::vector<Enemy>> waveList;
	int waveRound = 0;
	std::vector<Enemy> wave;
	Enemy* waveEnemies = new Enemy[5];
	unsigned int e = 0;

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


		sf::Time frameTime = frameClock.restart();

		//animatedSprite.play(*currentAnimation);
		//animatedSprite.update(frameTime);

		baby.setFrameTime(&frameTime);
		baby.playAnimation();
		baby.draw();
		baby.attackMove();

		baby2.setFrameTime(&frameTime);
		baby2.playAnimation();
		baby2.draw();
		baby2.attackMove();

		baby3.setFrameTime(&frameTime);
		baby3.playAnimation();
		baby3.draw();
		baby3.attackMove();

		baby4.setFrameTime(&frameTime);
		baby4.playAnimation();
		baby4.draw();
		baby4.attackMove();

		baby5.setFrameTime(&frameTime);
		baby5.playAnimation();
		baby5.draw();
		baby5.attackMove();
		//window.draw(animatedSprite);

		/*if (clock.getElapsedTime().asSeconds() > 1.0f) {
			if (e < 5) {
				Enemy newEnemy(&window, 100, 20, 0.3f, 0.5f, &texturePack, 1);
				newEnemy.setTarget(720, &targets[0]);
				newEnemy.draw();
				wave.push_back(newEnemy);
				waveEnemies[e] = newEnemy;
				e++;
			}
			clock.restart();
		}*/

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

		// Move all entities inside wave to towers
		/*for (unsigned int i = 0; i < wave.size(); i++) {
			wave[i].moveX();
			//wave[i].setTarget(targetX[currentTarget], &targets[currentTarget]);
		}*/
		for (unsigned int i = 0; i < 5; i++) {
			waveEnemies[i].moveX();
			//wave[i].setTarget(targetX[currentTarget], &targets[currentTarget]);
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////


		window.display();
	}

	return 0;
}