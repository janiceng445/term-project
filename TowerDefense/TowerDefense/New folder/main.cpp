#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Revolver Joe");
	sf::Texture background;
		if (!background.loadFromFile("background.png")){
			return -1;
		}
	sf::Texture joeTexture;
		if (!joeTexture.loadFromFile("revolverJoe.png")) {
			return -1;
		}
	sf::Texture armTexture;
	if (!armTexture.loadFromFile("arm.png")) {
		return -1;
	}
	sf::Texture bulletTexture;
		if (!bulletTexture.loadFromFile("bullet.png")) {
			return -1;
	}
	

	while (window.isOpen()){
		sf::Event event;
		sf::Sprite background(background);
		sf::Sprite joeSprite;
		sf::Sprite armSprite;
		sf::Sprite bulletSprite;
		joeSprite.setTexture(joeTexture);
		joeSprite.setPosition(530, 210);
		armSprite.setTexture(armTexture);
		armSprite.setPosition(550, 248);
		armSprite.setOrigin(19, 4);
		armSprite.setRotation((180.0 / 3.141592653589793238463) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x));
		//sets rotation of arm based on mouse location (gun points at mouse pointer)
		bulletSprite.setTexture(bulletTexture);


		
		window.draw(background);
		window.draw(armSprite);
		window.draw(joeSprite);
		window.draw(bulletSprite);
		
		

		window.display();

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			

		}
		window.clear(sf::Color::Black);
	}

	return 0;
}