#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#pragma once

const int DECAY_TIMER = 500;

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

	// Timer
	int timer;

	// Healthbar
	float healthWidth;

	// Graphic
	sf::Sprite sprite;
	sf::Texture texture;
	float spriteWidth;
	float spriteHeight;
	sf::RectangleShape bar;
	sf::RectangleShape hitbox;
	int currentBound;
	float hitboxWidth;
	float hitboxHeight;
	bool stopDrawing;

	// Texture paths
	std::string texturePath_idle;
	std::string texturePath_attack;
	std::string texturePath_death;
	std::string texturePath_special;

	// Window
	sf::RenderWindow* renWin;
	int windowWidth;
	
public:
	Enemy(sf::RenderWindow* renWin, float hp, int atk, float spd);
	
	// Graphics
	void assignWindow(sf::RenderWindow* renWin);
	void assignTexture();
	void changeTexture(sf::Texture);
	void draw();
	void setHitboxWidth(float w);
	void setHitBoxHeight(float h);
	void setTexturePathIdle(std::string name);
	void setTexturePathAttack(std::string name);
	void setTexturePathDeath(std::string name);
	void setTexturePathSpecial(std::string name);
	void testTextures();

	// Attributes
	void moveX();
	float getHealth();
	int getAtkDmg();
	void takeDamage(int dmg);
	void die();

	// Healthbar
	void drawHealthBar();
	// Hitbox
	void drawHitbox();

	// Positioning
	void setX();
	void setY();
	bool withinBounds();
	void changeBound(int x);
	void attack(float& targetHealth);

	// Others
	float getX();
	~Enemy();
};

