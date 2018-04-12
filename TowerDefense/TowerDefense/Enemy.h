#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>
#pragma once

const int DECAY_TIMER = 20000;

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
	bool alive;
	bool attacking;
	std::string type;
	bool hitbox_visibility;

	// Timer
	int timer;

	// Healthbar
	float healthWidth;

	// Graphic
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::Clock clock;
	sf::IntRect rectSrcSprite;
	float spriteWidth;
	float spriteHeight;
	sf::RectangleShape bar;
	sf::RectangleShape hitbox;
	int currentBound;
	float hitboxWidth;
	float hitboxHeight;
	bool stopDrawing;
	float animationSpeed;

	// Texture paths
	sf::Texture* texturePath_idle;
	sf::Texture texturePath_attack;
	sf::Texture texturePath_death;
	sf::Texture texturePath_special;
	std::vector<sf::Texture> texturePack;

	// Window
	sf::RenderWindow* renWin;
	int windowWidth;
	
public:
	Enemy();
	Enemy(sf::RenderWindow* renWin, float hp, int atk, float spd, std::vector<sf::Texture>* texturePack);
	
	// Graphics
	void assignWindow(sf::RenderWindow* renWin);
	void assignTexture();
	void changeTexture(sf::Texture);
	void draw();
	void setHitboxWidth(float w);
	void setHitBoxHeight(float h);
	void setTexturePathIdle(sf::Texture texture);
	void setTexturePathAttack(sf::Texture texture);
	void setTexturePathDeath(sf::Texture texture);
	void setTexturePathSpecial(sf::Texture texture);
	void testTextures();
	void showHitbox();

	// Attributes
	void moveX();
	float getHealth();
	int getAtkDmg();
	void takeDamage(int dmg);
	void die();
	bool isAlive();

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
	void getAddress();
	~Enemy();
};

