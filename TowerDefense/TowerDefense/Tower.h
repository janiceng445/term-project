#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Audio.hpp>

class Tower
{

private:
	int health;
	int maxHealth;
	int* HP;
	int atk;
	int defense;
	int upgradeLv;
	float posX;
	float posY;
	bool alive;

	sf::Texture towerTexture;

	sf::Sprite sprite;

	sf::RenderWindow* renWin;
	int windowWidth;

	sf::SoundBuffer damageBuffer;
	sf::Sound damageSound;

	// Health bar
	sf::RectangleShape bar;
	float barMaxWidth;
	sf::RectangleShape barOutline;
	int spriteWidth;
	int spriteHeight;
	int x;
	int y;
	sf::Vector2f originSprite;

public:


	Tower(sf::RenderWindow* renWin, int hitpoints, int atk, sf::Sprite sprite, float xPos, float yPos);


	int getXPosition();

	int getHealth();

	int* getHP(); // returns pointer to health

	int getmaxHP();

	void draw();

	int getDmg();

	void upgradeDmg();

	void takeDamage();

	void die();

	bool amIAlive();

	void upgradeHealth();

	void updateSprite(sf::Texture* newTex);

	sf::Sprite getSprite();

	sf::FloatRect getSpriteGlobalBounds();

	/////////////////////////////////////////// Health Bar ///////////////////////////////////////////
	void addHealthBar();
	void updateHealthBar();

	~Tower();


};
