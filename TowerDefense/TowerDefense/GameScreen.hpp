#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <Windows.h>
#include "cScreen.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Monster.h"
#include "Projectile.h"
#include "Lancer.h"
#include "Score.h"
#include "Tower.h"
#include "Wave.h"
#include "Gunner.h"

class GameScreen : public cScreen {
	private:
	// Global constants
	const double PI = 3.141592653589793238463;
	const float SKELLY_SPWN_TIMER = 5.0f;
	const float RHINO_SPWN_TIMER = 8.0f;
	const float LANCER_SPWN_TIMER = 10.0f;
	const float DEMON_SPWN_TIMER = 7.0f;
	const float GUNNER_SPWN_TIMER = 5.0f;
	const int fireTimer = 300;

	// Spawner
	std::vector<Monster*> wave;
	int skellyMax = 8;
	unsigned int skelly_DMG = 7;
	unsigned int skelly_HP = 100;

	int rhinoMax = 0;
	unsigned int rhino_DMG = 15;
	unsigned int rhino_HP = 75;

	int lancerMax = 3;
	unsigned int lancer_DMG = 30;
	unsigned int lancer_HP = 250;

	int demonMax = 0;
	unsigned int demon_DMG = 25;
	unsigned int demon_HP = 175;

	int gunnerMax = 6;
	unsigned int gunner_DMG = 5;
	unsigned int gunner_HP = 50;

	unsigned int boundary = (int) dimensions.x;

	// Tower Power
	unsigned int barbedWire_HP = 70;
	unsigned int basicTower_HP = 125;
	unsigned int shootyTower_HP = 150;
	unsigned int barbedWire_DMG = 0;
	unsigned int basicTower_DMG = 0;
	unsigned int shootyTower_DMG = 0;

	// Declarations
	bool paused = false;
	bool shot;
	bool towerShot;
	bool reloading;

	// Window
	sf::RenderWindow window;
	Score gameScore;
	sf::Text scoreText;
	sf::Font pixeled;
	sf::RectangleShape menuBar;
	sf::RectangleShape pauseScreen;
	sf::Text pauseText;
	bool pauseScreenVisibility;
	int incomeRateDefault = 5;
	int incomeRate = 10;

	// Upgrades
	int barbedWire_lvl = 1;
	int barricade_lvl = 1;
	int shootingTower_lvl = 1;
	int incomeRate_lvl = 1;
	int moneyDeduction = 100;
	
	// Buttons
	sf::Texture upgrade_01_texture;
	sf::Texture upgrade_02_texture;
	sf::Texture upgrade_03_texture;
	sf::Texture upgrade_04_texture;
	sf::Texture quit_texture;
	sf::Texture mute_texture_on;
	sf::Texture mute_texture_off;
	sf::Sprite upgrade_01_btn;
	sf::Sprite upgrade_02_btn;
	sf::Sprite upgrade_03_btn;
	sf::Sprite upgrade_04_btn;
	sf::Sprite quit_btn;
	sf::Sprite mute_btn;
	bool clicked = false;

	// Textures
	sf::Texture backgroundTexture;
	sf::Texture joeTexture;
	sf::Texture armTexture;
	sf::Texture bulletTexture;
	sf::Texture skelly_texture;
	sf::Texture rhino_texture;
	sf::Texture lancer_texture;
	sf::Texture demon_texture;
	sf::Texture gunner_texture;
	sf::Texture basicTowerTx;
	sf::Texture shootyTowerTx;
	sf::Texture barbedWireTx;

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
	std::vector<Animation> gunnerAni;

	// Towers
	float targetHealth;
	std::vector<int*> towersHP;
	std::vector<int> towersLocation;
	std::vector<Tower> tower;
	int currentTarget = 0;
	int targetHP;

	// Rounds
	std::vector<Wave*> waves;
	const static int numLevels = 10;
	int waveRound = 0;
	int skellyAmount[numLevels] = { 3, 4, 5, 5, 7, 7, 0, 0, 9, 10 };
	int rhinoAmount[numLevels] =  { 0, 2, 3, 5, 3, 3, 10, 9, 5, 4 };
	int lancerAmount[numLevels] = { 0, 0, 1, 2, 2, 3, 4, 7, 3, 3 };
	int demonAmount[numLevels] =  { 0, 0, 0, 3, 4, 3, 7, 5, 5, 5 };
	int gunnerAmount[numLevels] = { 0, 0, 2, 3, 4, 5, 6, 7, 3, 5 };
	int breakCounter = 0;
	int breakTimer = 500;
	sf::Text roundText;
	bool showRound = false;
	int showRoundCounter = 0;
	int showRoundTimer = 1200;

	// Timers
	int projTimer;
	int const maxProjTimer = 250;
	int scoreTimer;
	int btnTimer;
	int const maxBtnTimer = 250;

	// Clocks
	sf::Clock clock_Skelly;
	sf::Clock clock_Rhino;
	sf::Clock clock_Lancer;
	sf::Clock clock_Demon;
	sf::Clock clock_Gunner;
	sf::Clock game_clock;
	sf::Clock barbedTimer;
	sf::Clock shootyTimer;
	sf::Clock enemyAtkTimer;

	// Tower Sprites
	sf::Sprite basicTowerSpr;
	sf::Sprite shootyTowerSpr;
	sf::Sprite barbedWireSpr;

	// Joe Projectiles
	std::vector<sf::Sprite> ammo;
	std::vector<Projectile> currentProj;
	sf::Vector2f center;
	sf::Vector2f mousePos;
	sf::Vector2f mouseAimDir;
	sf::Vector2f mouseAimDirNorm;

	//tower projectiles
	std::vector<Projectile> towerProjectiles;
	sf::Vector2f towerOrigin;
	sf::Vector2f enemyPosition;
	sf::Vector2f towerAimDirection;
	sf::Vector2f towerAimDirNorm;
	int reloaded;

	//Audio
	sf::SoundBuffer gunshot_buffer;
	sf::SoundBuffer reload_buffer;
	sf::SoundBuffer towershot_buffer;
	sf::Sound towershotSound;
	sf::Sound gunshotSound;
	sf::Sound reloadSound;
	sf::Music gameMusic;
	bool sound;

	public:
	// Declaring functions
	GameScreen(void);
	virtual int Run(sf::RenderWindow &window);

	void setSpriteAnimations(std::vector<Animation>* skellyAni, sf::Texture* skelly_texture, char size, std::string name);
	void runSpawners(int* maxSpawn, sf::Clock* clock, float spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* window,
		std::vector<Animation>* ani, int dmg, int hp, int boundary, int* targetHP, MonsterType name, Score* score);
	void createPauseScreen();
	void drawPauseScreen(sf::RenderWindow* win);
	void drawRound(sf::RenderWindow* win);

	// Set up rounds and waves configuration
	void createRounds();

	// Create buttons
	void createButtons();
	bool buttonIsClicked(sf::Sprite* sprite, sf::RenderWindow* win);
};
