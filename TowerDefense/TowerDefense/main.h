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
const float DEMON_SPWN_TIMER = 10.0f;
const int fireTimer = 300;

// Declarations
bool paused = false;
bool shot;
bool reloading;

// Window
sf::RenderWindow window;
Score gameScore;
sf::Text scoreText;
sf::Font pixeled;
sf::RectangleShape menuBar;

// Textures
sf::Texture backgroundTexture;
sf::Texture joeTexture;
sf::Texture armTexture;
sf::Texture bulletTexture;
sf::Texture skelly_texture;
sf::Texture rhino_texture;
sf::Texture lancer_texture;
sf::Texture demon_texture;

sf::Vector2f dimensions;

// Sprites
sf::Sprite background;
sf::Sprite joeSprite;
sf::Sprite armSprite;
sf::Sprite bulletSprite;

// Animations
std::vector<Animation> skellyAni;
std::vector<Animation> rhinoAni;
std::vector<Animation> lancerAni;
std::vector<Animation> demonAni;

// Mobs
float targetHealth;
float targets[3] = { 50, 55, 60 };
int const maxProjTimer = 250;
int targetX[3] = { 150, 200, 250 };
int currentTarget;
int targetHP;
int waveRound;

// Timers
int projTimer;
int scoreTimer;

// Clocks
sf::Clock clock_Skelly;
sf::Clock clock_Rhino;
sf::Clock clock_Lancer;
sf::Clock clock_Demon;
sf::Clock game_clock;

// Projectiles
std::vector<sf::Sprite> ammo;
std::vector<Projectile> currentProj;
sf::Vector2f center;
sf::Vector2f mousePos;
sf::Vector2f mouseAimDir;
sf::Vector2f mouseAimDirNorm;
Projectile p1(3.0);
int reloaded;

// Spawner
std::vector<Monster*> wave;
int skellyMax = 10;
unsigned int skelly_DMG = 10;
unsigned int skelly_HP = 100;

int rhinoMax = 5;
unsigned int rhino_DMG = 15;
unsigned int rhino_HP = 75;

int lancerMax = 4;
unsigned int lancer_DMG = 25;
unsigned int lancer_HP = 250;

int demonMax = 4;
unsigned int demon_DMG = 25;
unsigned int demon_HP = 175;

unsigned int boundary = 450;

// Declaring functions
void setSpriteAnimations(std::vector<Animation>* skellyAni, sf::Texture* skelly_texture, char size, std::string name);
void runSpawners(int* maxSpawn, sf::Clock* clock, int spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* window, std::vector<Animation>* ani, int dmg, int hp, int boundary, int* targetHP, std::string name, Score* score);