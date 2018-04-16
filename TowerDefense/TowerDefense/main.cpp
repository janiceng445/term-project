#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Tower.h"
#include "Projectile.h"
#include "Timer.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Monster.h"


const double PI = 3.141592653589793238463;
float SKELLY_SPWN_TIMER = 5.0f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 480), "Revolver Joe");
	sf::Texture background;
	if (!background.loadFromFile("Images/background.png")) {
		std::cerr << "background failed" << std::endl;
		return -1;
	}
	
	sf::Texture joeTexture;
	if (!joeTexture.loadFromFile("Images/revolverJoe.png")) {
		std::cerr << "revolverJoe failed" << std::endl;
		return -1;
	}
	
	sf::Texture armTexture;
	if (!armTexture.loadFromFile("Images/arm.png")) {
		std::cerr << "arm failed" << std::endl;
		return -1;
	}
	
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("Images/bullet.png")) {
		std::cerr << "bullet failed" << std::endl;
		return -1;
	}

	sf::Texture towerTexture;
	if (!towerTexture.loadFromFile("Images/towertest.png")) {
		std::cerr << "tower failed" << std::endl;
		return -1;
	}

	sf::Sprite bulletSprite(bulletTexture);
	std::vector<Projectile> currentProj;
	std::vector<sf::Sprite> ammo;

	for (int i = 0; i < 6; i++) {
		ammo.push_back(bulletSprite);
	}

	sf::Vector2f center;
	sf::Vector2f mousePos;
	sf::Vector2f mouseAimDir;
	sf::Vector2f mouseAimDirNorm;

	Projectile p1(bulletSprite);
	int timer = 333;
	int reloaded = 0;
	bool shot = false;
	bool reloading = false;

	//janice
	////////////////////////////// Temporary Placement ///////////////////////////////
	float targetHealth = 200;
	float targets[3] = { 50, 55, 60 };
	int targetX[3] = { 150, 200, 250 };
	int currentTarget = 0;
	// Clocks
	sf::Clock clock;

	//////////////////////////////// Make idle sprite ////////////////////////////////

	sf::Texture skelly_texture;
	skelly_texture.loadFromFile("Images/enemies/skelly.png");
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
	//janice

	while (window.isOpen()) {
		sf::Event event;
		sf::Sprite background(background);
		sf::Sprite joeSprite;
		sf::Sprite armSprite;

		joeSprite.setTexture(joeTexture);
		joeSprite.setPosition(590, 200);
		armSprite.setTexture(armTexture);
		armSprite.setPosition(610, 238);
		armSprite.setOrigin(20, 4);
		armSprite.setRotation((180.0 / PI) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x));
		//sets rotation of arm based on mouse location (gun points at mouse pointer)
		bulletSprite.setTexture(bulletTexture);
		
		//janice
		// Skelly Spawner
		int r = (rand() % 6) - 3;
		unsigned int skellyMax = 5;
		if (clock.getElapsedTime().asSeconds() > SKELLY_SPWN_TIMER + r && wave.size() <= skellyMax) {
			Monster skelly(&window, skellyAni, 10, 100);
			skelly.setTarget(450, &targetHP);
			wave.push_back(skelly);
			clock.restart();
		}
		//janice

		//mine
		center = armSprite.getPosition();
		mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		mouseAimDir = mousePos - center;
		mouseAimDirNorm = mouseAimDir / sqrt(pow(mouseAimDir.x, 2) + pow(mouseAimDir.y, 2));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer == 333 && reloading == false && !ammo.empty()) {
			shot = true;
			ammo.pop_back();
			if (ammo.empty()) reloading = true;
			p1.bullet.setPosition(center + sf::Vector2f(19,4));
			p1.bullet.setRotation((180.0 / PI) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x) - 90);
			p1.vel = (mouseAimDirNorm * p1.getMaxVel());
			currentProj.push_back(Projectile(p1));
		}
		else if (reloading) {
			if (reloaded == 6) {
				reloaded = 0;
				reloading = false;
			}
		}
		if (shot == true) {
			timer--;
			if (timer == 0) {
				shot = false;
				timer = 333;
			}
		}
		//mine

		//janice
		for (unsigned int i = 0; i < wave.size(); i++) {
			wave[i].run();
			wave[i].draw();
			wave[i].attackMove();
		}
		//janice

		window.draw(background);
		window.draw(armSprite);
		window.draw(joeSprite);
		for (int i = 0; i < ammo.size(); i++) {
			ammo[i].setPosition(sf::Vector2f((i*11)+1, 0));
			window.draw(ammo[i]);
		}

		for (int i = 0; (unsigned)i < currentProj.size(); i++) {
			currentProj[i].bullet.move(currentProj[i].vel);
			//std::cout << currentProj[i].bullet.getPosition().x << ", " << currentProj[i].bullet.getPosition().y << std::endl;
			window.draw(currentProj[i].bullet);
			
			if (currentProj[i].bullet.getPosition().x < 0 || currentProj[i].bullet.getPosition().x > 720
				|| currentProj[i].bullet.getPosition().y < 0 || currentProj[i].bullet.getPosition().y > 480)
			{
				currentProj.erase(currentProj.begin() + i);
			}
		}
		
		window.display();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseWheelMoved) {
				if (reloaded != 6 && reloading == true) {
					reloaded++;
					ammo.push_back(bulletSprite);
					continue;
				}
			}
		}
		window.clear(sf::Color::Black);
	}

	return 0;
}