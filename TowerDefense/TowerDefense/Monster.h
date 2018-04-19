#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Score.h"
#include <cstdlib>

const float DEFAULT_MVMT_SPEED = 0.05f;
const float DEFAULT_ANI_SPEED = 0.1f;

class Monster
{
	protected:
	// Attributes
	int AD;
	int HP;
	int max_HP;
	float movementSpeed;
	float animationSpeed;
	bool isAlive; // State of enemy
	bool isPermaDead; // Decaying process (animation purposes)
	bool isAttacking;
	bool special;
	int stoppingPoint; // Tower locations
	int decay_timer; // Time it takes for sprite to disappear

	// Graphics/Animations
	int type; // small | medium | large enemies
	int size; // Goes hand-in-hand with type
	Animation* currentAnimation;
	AnimatedSprite aniSprite;
	std::vector<Animation> aniPack;
	sf::Time frameTime;
	int spriteWidth;
	int spriteHeight;
	bool stopRunning; // Stop running timers and behavioral animation check
	bool stopDrawing; // Stop drawing sprite

	// Healthbar
	sf::RectangleShape bar;
	// Hitbox
	sf::RectangleShape hitbox;
	bool hitboxVisibility;
	float hitbox_Width;
	float hitbox_Height;
	int hitbox_X;
	int hitbox_Y;

	// Location
	float x;
	float y;

	// Others
	sf::RenderWindow* window;
	int targetedHealth;
	int currentFrame;
	sf::Clock clock;
	sf::Clock frameClock;
	Score* score;

	public:
	Monster();
	Monster(sf::RenderWindow* win, std::vector<Animation> aniPack, int AD, int HP, Score* score);

	// Animation
	void playAnimation();
	void update(sf::Time frameTime);
	void setCurrentAnimation();
	void changeCurrentAnimation(int n);
	void draw();
	void virtual run();

	// Healthbar
	void addHealthBar();
	void updateHealthBar();
	void showHealthBar();
	// Hitbox
	void drawHitbox();
	void showHitbox();
	sf::Vector2f getHitbox_Dim();

	// Location
	void changeY();
	void setStartingPosition(float x, float y);
	void attackMove();
	sf::Vector2f getCurrentLocation();
	sf::FloatRect virtual getSpriteGlobalBounds();
	float virtual getDetectionDistance();

	// Behavior
	void setTarget(int x, int* targetedHealth);
	void attack();
	void virtual useSpecialAbility();
	void virtual takeDamage(int dmg);
	int getDamage();
	bool isCurrAttacking();
	void die();
	bool isAliveFunc();
	bool isDead();

	// Other

	~Monster();
};