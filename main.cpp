#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Tower.h"
#include "Projectile.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Revolver Joe");
	sf::Texture background;
	if (!background.loadFromFile("background.png")) {
		std::cerr << "background failed" << std::endl;
		return -1;
	}
	
	sf::Texture joeTexture;
	if (!joeTexture.loadFromFile("revolverJoe.png")) {
		std::cerr << "revolverJoe failed" << std::endl;
		return -1;
	}
	
	sf::Texture armTexture;
	if (!armTexture.loadFromFile("arm.png")) {
		std::cerr << "arm failed" << std::endl;
		return -1;
	}
	
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("bullet.png")) {
		std::cerr << "bullet failed" << std::endl;
		return -1;
	}

	sf::Texture towerTexture;
	if (!towerTexture.loadFromFile("towertest.png")) {
		std::cerr << "tower failed" << std::endl;
		return -1;
	}

	sf::Sprite bulletSprite(bulletTexture);
	std::vector<Projectile> currentProj;

	sf::Vector2f center;
	sf::Vector2f mousePos;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	Projectile p1(bulletSprite);
	int timer = 300;
	bool shot = false;

	while (window.isOpen()) {
		sf::Event event;
		sf::Sprite background(background);
		sf::Sprite joeSprite;
		sf::Sprite armSprite;

		joeSprite.setTexture(joeTexture);
		joeSprite.setPosition(530, 210);
		armSprite.setTexture(armTexture);
		armSprite.setPosition(550, 248);
		armSprite.setOrigin(19, 4);
		armSprite.setRotation((180.0 / 3.141592653589793238463) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x));
		//sets rotation of arm based on mouse location (gun points at mouse pointer)
		bulletSprite.setTexture(bulletTexture);

		//mine
		center = armSprite.getPosition();
		mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		aimDir = mousePos - center;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (timer == 300) {
				shot = true;
				p1.bullet.setPosition(center);
				p1.bullet.setRotation((180.0 / 3.141592653589793238463) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x) - 90);
				p1.vel = (aimDirNorm * p1.getMaxVel());
				currentProj.push_back(Projectile(p1));
			}
		}
		if (shot == true) {
			timer--;
			if (timer == 0) {
				shot = false;
				timer = 300;
			}
		}
		//mine

		window.draw(background);
		window.draw(armSprite);
		window.draw(joeSprite);
		window.draw(bulletSprite);

		//window.draw(towerSprite);

		for (int i = 0; (unsigned)i < currentProj.size(); i++) {
			currentProj[i].bullet.move(currentProj[i].vel);
			//std::cout << currentProj[i].bullet.getPosition().x << ", " << currentProj[i].bullet.getPosition().y << std::endl;
			window.draw(currentProj[i].bullet);
			
			if (currentProj[i].bullet.getPosition().x < 0 || currentProj[i].bullet.getPosition().x > 640
				|| currentProj[i].bullet.getPosition().y < 0 || currentProj[i].bullet.getPosition().y > 480)
			{
				currentProj.erase(currentProj.begin() + i);
			}
		}
		

		window.display();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
	}

	return 0;
}