#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Tower
{

private:
	int health;
	int maxHealth;
	int atk;
	int defense;
	float posX;
	float posY;
	bool alive;

	sf::Texture towerTexture;

	sf::Sprite sprite;

	sf::RenderWindow* renWin;
	int windowWidth;


public:


	Tower(sf::RenderWindow* renWin, int hitpoints, int atk, sf::Sprite sprite, float xPos, float yPos);

	void assignTexture();

	int getXPosition();

	int getHealth();

	void draw();

	void takeDamage(int dmg);

	void die();

	bool amIAlive();

	sf::Sprite getSprite();

	sf::FloatRect getSpriteGlobalBounds();

	~Tower();


};
