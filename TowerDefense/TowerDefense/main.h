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
const float RHINO_SPWN_TIMER = 7.0f;
const float LANCER_SPWN_TIMER = 1.0f;
const int fireTimer = 300;

// Declaring functions
void setSpriteAnimations(std::vector<Animation>* skellyAni, sf::Texture* skelly_texture, char size, std::string name);
void runSpawners(int maxSpawn, sf::Clock* clock, int spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* window, std::vector<Animation> ani, int dmg, int hp, int boundary, int* targetHP, std::string name);