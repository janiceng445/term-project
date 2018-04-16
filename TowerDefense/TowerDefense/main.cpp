#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Monster.h"
#include "Enemy.h"
#include "Timer.h"
#include "Projectile.h"
#include "Lancer.h"

const double PI = 3.141592653589793238463;
float SKELLY_SPWN_TIMER = 5.0f;
float RHINO_SPWN_TIMER = 7.0f;
float LANCER_SPWN_TIMER = 9.0f;
const int fireTimer = 300;

int main()
{
	// Create window
	sf::Vector2i screenDimensions(720, 480);
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Defend the Joe!");

	// Loading files
	sf::Texture background;
	if (!background.loadFromFile("images/background.png")) {
		std::cerr << "background failed" << std::endl;
		return -1;
	}

	sf::Texture joeTexture;
	if (!joeTexture.loadFromFile("images/revolverJoe.png")) {
		std::cerr << "revolverJoe failed" << std::endl;
		return -1;
	}

	sf::Texture armTexture;
	if (!armTexture.loadFromFile("images/arm.png")) {
		std::cerr << "arm failed" << std::endl;
		return -1;
	}

	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("images/bullet.png")) {
		std::cerr << "bullet failed" << std::endl;
		return -1;
	}

	sf::Texture towerTexture;
	if (!towerTexture.loadFromFile("images/towertest.png")) {
		std::cerr << "tower failed" << std::endl;
		//return -1;
	}


	////////////////////////////// Temporary Placement ///////////////////////////////
	float targetHealth = 200;
	float targets[3] = { 50, 55, 60 };
	int targetX[3] = { 150, 200, 250 };
	int currentTarget = 0;
	// Clocks
	sf::Clock clock_Skelly;
	sf::Clock clock_Rhino;
	sf::Clock clock_Lancer;

	//////////////////////////////// Make idle sprite ////////////////////////////////

	int size_s_x = 40;
	int size_s_y = 49;
	int size_m_x = 60;
	int size_m_y = 74;


	sf::Texture skelly_texture;
	if (!skelly_texture.loadFromFile("images/enemies/skelly.png")) {
		std::cerr << "skelly_spriteSheet failed" << std::endl;
		return -1;
	}
	std::vector<Animation> skellyAni;


	Animation skelly_idle;
	skelly_idle.setSpriteSheet(skelly_texture);
	skelly_idle.addFrame(sf::IntRect(0, 0, size_s_x, size_s_y));
	skelly_idle.addFrame(sf::IntRect(size_s_x, 0, size_s_x, size_s_y));
	skelly_idle.addFrame(sf::IntRect(size_s_x * 2, 0, size_s_x, size_s_y));
	skelly_idle.addFrame(sf::IntRect(size_s_x * 3, 0, size_s_x, size_s_y));
	skelly_idle.addFrame(sf::IntRect(size_s_x * 4, 0, size_s_x, size_s_y));
	skellyAni.push_back(skelly_idle);

	Animation skelly_attack;
	skelly_attack.setSpriteSheet(skelly_texture);
	skelly_attack.addFrame(sf::IntRect(0, size_s_y, size_s_x, size_s_y));
	skelly_attack.addFrame(sf::IntRect(size_s_x, size_s_y, size_s_x, size_s_y));
	skelly_attack.addFrame(sf::IntRect(size_s_x * 2, size_s_y, size_s_x, size_s_y));
	skelly_attack.addFrame(sf::IntRect(size_s_x * 3, size_s_y, size_s_x, size_s_y));
	skelly_attack.addFrame(sf::IntRect(size_s_x * 4, size_s_y, size_s_x, size_s_y));
	skellyAni.push_back(skelly_attack);

	Animation skelly_death;
	skelly_death.setSpriteSheet(skelly_texture);
	skelly_death.addFrame(sf::IntRect(0, size_s_y * 2, size_s_x, size_s_y));
	skelly_death.addFrame(sf::IntRect(size_s_x, size_s_y * 2, size_s_x, size_s_y));
	skelly_death.addFrame(sf::IntRect(size_s_x * 2, size_s_y * 2, size_s_x, size_s_y));
	skelly_death.addFrame(sf::IntRect(size_s_x * 3, size_s_y * 2, size_s_x, size_s_y));
	skelly_death.addFrame(sf::IntRect(size_s_x * 4, size_s_y * 2, size_s_x, size_s_y));
	skellyAni.push_back(skelly_death);

	sf::Texture rhino_texture;
	if (!rhino_texture.loadFromFile("images/enemies/rhino.png")) {
		std::cerr << "rhino_spriteSheet failed" << std::endl;
		return -1;
	}
	std::vector<Animation> rhinoAni;

	Animation rhino_idle;
	rhino_idle.setSpriteSheet(rhino_texture);
	rhino_idle.setSpriteSheet(rhino_texture);
	rhino_idle.addFrame(sf::IntRect(0, 0, size_s_x, size_s_y));
	rhino_idle.addFrame(sf::IntRect(size_s_x, 0, size_s_x, size_s_y));
	rhino_idle.addFrame(sf::IntRect(size_s_x * 2, 0, size_s_x, size_s_y));
	rhino_idle.addFrame(sf::IntRect(size_s_x * 3, 0, size_s_x, size_s_y));
	rhino_idle.addFrame(sf::IntRect(size_s_x * 4, 0, size_s_x, size_s_y));
	rhinoAni.push_back(rhino_idle);

	Animation rhino_attack;
	rhino_attack.setSpriteSheet(rhino_texture);
	rhino_attack.addFrame(sf::IntRect(0, size_s_y, size_s_x, size_s_y));
	rhino_attack.addFrame(sf::IntRect(size_s_x, size_s_y, size_s_x, size_s_y));
	rhino_attack.addFrame(sf::IntRect(size_s_x * 2, size_s_y, size_s_x, size_s_y));
	rhino_attack.addFrame(sf::IntRect(size_s_x * 3, size_s_y, size_s_x, size_s_y));
	rhino_attack.addFrame(sf::IntRect(size_s_x * 4, size_s_y, size_s_x, size_s_y));
	rhinoAni.push_back(rhino_attack);

	Animation rhino_death;
	rhino_death.setSpriteSheet(rhino_texture);
	rhino_death.addFrame(sf::IntRect(0, size_s_y * 2, size_s_x, size_s_y));
	rhino_death.addFrame(sf::IntRect(size_s_x, size_s_y * 2, size_s_x, size_s_y));
	rhino_death.addFrame(sf::IntRect(size_s_x * 2, size_s_y * 2, size_s_x, size_s_y));
	rhino_death.addFrame(sf::IntRect(size_s_x * 3, size_s_y * 2, size_s_x, size_s_y));
	rhino_death.addFrame(sf::IntRect(size_s_x * 4, size_s_y * 2, size_s_x, size_s_y));
	rhinoAni.push_back(rhino_death);

	sf::Texture lancer_texture;
	if (!lancer_texture.loadFromFile("images/enemies/lancer.png")) {
		std::cerr << "lancer_spriteSheet failed" << std::endl;
		return -1;
	}
	std::vector<Animation> lancerAni;

	Animation lancer_idle;
	lancer_idle.setSpriteSheet(lancer_texture);
	lancer_idle.setSpriteSheet(lancer_texture);
	lancer_idle.addFrame(sf::IntRect(0, 0, size_m_x, size_m_y));
	lancer_idle.addFrame(sf::IntRect(size_m_x, 0, size_m_x, size_m_y));
	lancer_idle.addFrame(sf::IntRect(size_m_x * 2, 0, size_m_x, size_m_y));
	lancer_idle.addFrame(sf::IntRect(size_m_x * 3, 0, size_m_x, size_m_y));
	lancer_idle.addFrame(sf::IntRect(size_m_x * 4, 0, size_m_x, size_m_y));
	lancerAni.push_back(lancer_idle);

	Animation lancer_attack;
	lancer_attack.setSpriteSheet(lancer_texture);
	lancer_attack.addFrame(sf::IntRect(0, size_m_y, size_m_x, size_m_y));
	lancer_attack.addFrame(sf::IntRect(size_m_x, size_m_y, size_m_x, size_m_y));
	lancer_attack.addFrame(sf::IntRect(size_m_x * 2, size_m_y, size_m_x * 2, size_m_y));
	lancer_attack.addFrame(sf::IntRect(size_m_x * 2, size_m_y, size_m_x * 2, size_m_y));
	lancer_attack.addFrame(sf::IntRect(size_m_x * 4, size_m_y, size_m_x, size_m_y));
	lancerAni.push_back(lancer_attack);

	Animation lancer_death;
	lancer_death.setSpriteSheet(lancer_texture);
	lancer_death.addFrame(sf::IntRect(0, size_m_y * 2, size_m_x, size_m_y));
	lancer_death.addFrame(sf::IntRect(size_m_x, size_m_y * 2, size_m_x, size_m_y));
	lancer_death.addFrame(sf::IntRect(size_m_x * 2, size_m_y * 2, size_m_x, size_m_y));
	lancer_death.addFrame(sf::IntRect(size_m_x * 3, size_m_y * 2, size_m_x, size_m_y));
	lancer_death.addFrame(sf::IntRect(size_m_x * 4, size_m_y * 2, size_m_x, size_m_y));
	lancerAni.push_back(lancer_death);

	Animation lancer_special;
	lancer_special.setSpriteSheet(lancer_texture);
	lancer_special.addFrame(sf::IntRect(0, size_m_y * 3, size_m_x, size_m_y));
	lancer_special.addFrame(sf::IntRect(size_m_x, size_m_y * 3, size_m_x, size_m_y));
	lancer_special.addFrame(sf::IntRect(size_m_x * 2, size_m_y * 3, size_m_x, size_m_y));
	lancer_special.addFrame(sf::IntRect(size_m_x * 3, size_m_y * 3, size_m_x, size_m_y));
	lancer_special.addFrame(sf::IntRect(size_m_x * 4, size_m_y * 3, size_m_x, size_m_y));
	lancerAni.push_back(lancer_special);


	// Create a new testing monster
	int targetHP = 100;

	//////////////////////////////// Wave of enemies /////////////////////////////////
	int waveRound = 0;
	std::vector<Monster> wave;

	///////////////////////////////// Projectiles ////////////////////////////////////

	sf::Sprite bulletSprite(bulletTexture);
	std::vector<Projectile> currentProj;

	sf::Vector2f center;
	sf::Vector2f mousePos;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	Projectile p1(bulletSprite);
	int timer = fireTimer;
	bool shot = false;

	///////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		sf::Event event;

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

		///////////////////////////////////////////// Samuel /////////////////////////////////////////////

		center = armSprite.getPosition();
		mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		aimDir = mousePos - center;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (timer == fireTimer) {
				shot = true;
				p1.bullet.setPosition(center);

				p1.bullet.setRotation((180.0 / PI) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x) - 90);
				p1.vel = (aimDirNorm * p1.getMaxVel());
				currentProj.push_back(Projectile(p1));
			}
		}
		if (shot == true) {
			timer--;
			if (timer == 0) {
				shot = false;
				timer = fireTimer;
			}
		}

		window.draw(background);
		window.draw(armSprite);
		window.draw(joeSprite);
		window.draw(bulletSprite);

		//window.draw(towerSprite);
		if (!currentProj.empty()) {
			for (unsigned int i = 0; i < currentProj.size(); i++) {
				currentProj[i].bullet.move(currentProj[i].vel);
				//std::cout << currentProj[i].bullet.getPosition().x << ", " << currentProj[i].bullet.getPosition().y << std::endl;
				window.draw(currentProj[i].bullet);

				// Checks collision with enemies from the bullet scope
				if (currentProj[i].checkCollision(&wave)) currentProj.erase(currentProj.begin() + i);

				// Ends the loop if the bullet vector is empty and reading attempt is made to see next element in empty vector
				if (currentProj.empty()) {
					break;
				}
				// Deletes the bullet if it goes off screen
				if (currentProj[i].bullet.getPosition().x < 0 || currentProj[i].bullet.getPosition().x > screenDimensions.x
					|| currentProj[i].bullet.getPosition().y < 0 || currentProj[i].bullet.getPosition().y > screenDimensions.y)
				{
					currentProj.erase(currentProj.begin() + i);
				}
			}
		}

		///////////////////////////////////////////// Janice /////////////////////////////////////////////

		// Skelly Spawner
		int r = (rand() % 6) - 3;
		unsigned int skellyMax = 3;
		unsigned int rhinoMax = 5;
		unsigned int lancerMax = 6;
		if (clock_Skelly.getElapsedTime().asSeconds() > SKELLY_SPWN_TIMER + r && wave.size() <= skellyMax) {
			Monster skelly(&window, skellyAni, 10, 100);
			skelly.setTarget(450, &targetHP);
			wave.push_back(skelly);
			clock_Skelly.restart();
		}

		if (clock_Rhino.getElapsedTime().asSeconds() > RHINO_SPWN_TIMER + r && wave.size() <= rhinoMax) {
			Monster rhino(&window, rhinoAni, 12, 125);
			rhino.setTarget(475, &targetHP);
			wave.push_back(rhino);
			clock_Rhino.restart();
		}

		if (clock_Lancer.getElapsedTime().asSeconds() > LANCER_SPWN_TIMER + r && wave.size() <= lancerMax) {
			Lancer lancer(&window, lancerAni, 25, 250);
			lancer.setTarget(475, &targetHP);
			wave.push_back(lancer);
			clock_Lancer.restart();
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

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
	}

	return 0;
}