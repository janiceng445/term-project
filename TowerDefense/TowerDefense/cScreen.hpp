#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class cScreen
{
public:
	virtual int Run(sf::RenderWindow &app) = 0;
};