#include "main.h"
#include "Screens.hpp"

int main()
{
	////////////////////////////// Create window //////////////////////////////
	dimensions.x = backgroundTexture.getSize().x;
	dimensions.y = backgroundTexture.getSize().y;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Defend the Joe!");
	//sf::RenderWindow window(sf::VideoMode(dimensions.x, dimensions.y), "Defend the Joe!", sf::Style::Fullscreen);

	std::vector<cScreen*> Screens;
	int screen = 0;

	//StartScreen start;
	//Screens.push_back(&start);
	GameScreen game;
	Screens.push_back(&game);

	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}
}