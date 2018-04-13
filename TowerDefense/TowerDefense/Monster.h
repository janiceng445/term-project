#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <cstdlib>

class Monster
{
private:
	// Attributes
	int AD;
	int HP;
	bool isAlive;
	bool isAttacking;
	int stoppingPoint;

	// Graphics/Animations
	Animation* currentAnimation;
	AnimatedSprite aniSprite;
	std::vector<Animation> aniPack;
	sf::Time* frameTime;
	int spriteWidth;
	int spriteHeight;

	// Healthbar
	sf::RectangleShape bar;

	// Location
	float x;
	float y;

	// Others
	sf::RenderWindow* window;
	int targetedHealth;
	int currentFrame;
	sf::Clock clock;

public:
	Monster(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP);
	
	// Animation
	void playAnimation();
	void setFrameTime(sf::Time* frameTime);
	void setCurrentAnimation();
	void changeCurrentAnimation(int n);
	void draw();

	// Healthbar
	void addHealthBar();
	void updateHealthBar();
	void showHealthBar();

	// Location
	void setStartingPosition(float x, float y);
	void attackMove();

	// Behavior
	void setTarget(int x, int* targetedHealth);
	void attack();
	void takeDamage(int dmg);
	void die();
	
	// Other

	~Monster();
};

