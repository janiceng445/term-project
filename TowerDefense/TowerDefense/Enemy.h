#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#pragma once

class Enemy
{
private:
	// Attributes
	float health;
	int atk;
	int defense;
	float initX;
	float initY;
	float posX;
	float posY;
	float speed; 
	bool isAlive;

	// Healthbar
	float healthWidth;

	// Graphic
	sf::Sprite sprite;
	sf::Texture texture;
	float spriteWidth;
	sf::RectangleShape bar;
	int currentBound;

	// Window
	sf::RenderWindow* renWin;
	int windowWidth;
	
public:
	Enemy(sf::RenderWindow* renWin, float hp, int atk, float spd);
	
	// Graphics
	void assignWindow(sf::RenderWindow* renWin);
	void assignTexture();
	void draw();

	// Attributes
	void moveX();
	float getHealth();
	int getAtkDmg();
	void takeDamage(int dmg);
	void die();

	// Healthbar
	void drawHealthBar();

	// Positioning
	void setX();
	void setY();
	bool withinBounds();
	void changeBound(int x);
	bool collision();

	// Others
	float getX();
	~Enemy();
};

