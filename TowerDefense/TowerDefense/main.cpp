//#include "main.h"
#include "Screens.hpp"

enum screenType { start = 0, game = 1, win = 2, lose = 3 };

int main()
{
	////////////////////////////// Create window //////////////////////////////
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Defend the Joe!");
	//sf::RenderWindow window(sf::VideoMode(dimensions.x, dimensions.y), "Defend the Joe!", sf::Style::Fullscreen);

	int screen = 0;

	//main screens loop
	while (screen >= 0)
	{
		//screen = screens[screen]->Run(window);
		if (screen == screenType::start)
		{
			StartScreen* start = new StartScreen;
			screen = start->Run(window);
			delete start;
		}
		else if (screen == screenType::game)
		{
			GameScreen* game = new GameScreen;
			screen = game->Run(window);
			delete game;
		}
		else if (screen == screenType::win)
		{
			WinScreen* win = new WinScreen;
			screen = win->Run(window);
			delete win;
		}
		else if (screen == screenType::lose)
		{
			LoseScreen* lose = new LoseScreen;
			screen = lose->Run(window);
			delete lose;
		}
	}
	return 0;
}