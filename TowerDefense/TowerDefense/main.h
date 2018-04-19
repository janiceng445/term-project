#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Monster.h"
#include "Enemy.h"
#include "Timer.h"
#include "Projectile.h"
#include "Lancer.h"
#include "Score.h"

// Global constants
const double PI = 3.141592653589793238463;
const float SKELLY_SPWN_TIMER = 5.0f;
const float RHINO_SPWN_TIMER = 8.0f;
const float LANCER_SPWN_TIMER = 10.0f;
//Caleb Demon Tests
const float DEMON_SPWN_TIMER = 10.0f;
const int fireTimer = 300;

// Spawner
int skellyMax = 10;
unsigned int skelly_DMG = 10;
unsigned int skelly_HP = 100;

int rhinoMax = 5;
unsigned int rhino_DMG = 15;
unsigned int rhino_HP = 75;

int lancerMax = 4;
unsigned int lancer_DMG = 25;
unsigned int lancer_HP = 250;

//Caleb Demon Tests
int demonMax = 4;
unsigned int demon_DMG = 25;
unsigned int demon_HP = 175;

unsigned int boundary = 450;

// Declaring functions
void setSpriteAnimations(std::vector<Animation>* skellyAni, sf::Texture* skelly_texture, char size, std::string name);
void runSpawners(int* maxSpawn, sf::Clock* clock, int spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* window, std::vector<Animation>* ani, int dmg, int hp, int boundary, int* targetHP, std::string name, Score* score);