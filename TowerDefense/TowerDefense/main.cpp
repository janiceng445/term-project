//#include "main.h"
#include "Screens.hpp"

int main()
{
	////////////////////////////// Create window //////////////////////////////
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Defend the Joe!");
	//sf::RenderWindow window(sf::VideoMode(dimensions.x, dimensions.y), "Defend the Joe!", sf::Style::Fullscreen);

	std::vector<cScreen*> screens;
	int screen = 0;

	StartScreen start;
	screens.push_back(&start);
	GameScreen game;
	screens.push_back(&game);

	//Main loop
	while (screen >= 0)
	{
		screen = screens[screen]->Run(window);
		if (screen != -1) screen++;
		if ((unsigned)screen > screens.size()) return 0;
	}
	return 0;
}