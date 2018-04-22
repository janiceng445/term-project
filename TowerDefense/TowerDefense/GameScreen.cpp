#include "cScreen.hpp"
#include "GameScreen.hpp"

GameScreen::GameScreen(void) {}

int GameScreen::Run(sf::RenderWindow &window)
{
	sf::Event event;
	bool running = true;

	// Loading files
	if (!backgroundTexture.loadFromFile("images/background.png"))
	{
		std::cerr << "background failed" << std::endl;
		return -1;
	}
	if (!joeTexture.loadFromFile("images/revolverJoe.png"))
	{
		std::cerr << "revolverJoe failed" << std::endl;
		return -1;
	}
	if (!armTexture.loadFromFile("images/arm.png"))
	{
		std::cerr << "arm failed" << std::endl;
		return -1;
	}
	if (!bulletTexture.loadFromFile("images/bullet.png"))
	{
		std::cerr << "bullet failed" << std::endl;
		return -1;
	}

	//////////////////////////////// Load enemy textures ////////////////////////////////

	if (!skelly_texture.loadFromFile("images/enemies/skelly.png"))
	{
		std::cerr << "skelly_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!rhino_texture.loadFromFile("images/enemies/rhino.png"))
	{
		std::cerr << "rhino_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!lancer_texture.loadFromFile("images/enemies/lancer.png"))
	{
		std::cerr << "lancer_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!demon_texture.loadFromFile("images/enemies/demon.png"))
	{
		std::cerr << "demon_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!gunner_texture.loadFromFile("images/enemies/gunner.png"))
	{
		std::cerr << "gunner_spriteSheet failed" << std::endl;
		return -1;
	}

	//////////////////////////////// Load tower textures ////////////////////////////////

	if (!basicTowerTx.loadFromFile("images/Towers/BoxesLvl1.png"))
	{
		std::cout << "Basic tower could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!basicTowerlv2Tx.loadFromFile("images/Towers/BoxesLvl2.png"))
	{
		std::cout << "Basic tower could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	/*if (!basicTowerlv3Tx.loadFromFile("images/Towers/BoxesLvl3.png"))
	{
		std::cout << "Basic tower could not be loaded. Check filepath" << std::endl;
		return -1;
	}*/
	if (!shootyTowerTx.loadFromFile("images/Towers/ShootyTowerLvl1.png"))
	{
		std::cout << "Shooty tower could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!shootyTowerlv2Tx.loadFromFile("images/Towers/ShootyTowerLvl2.png"))
	{
		std::cout << "Shooty tower lvl 2 could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!shootyTowerlv3Tx.loadFromFile("images/Towers/ShootyTowerLvl3.png"))
	{
		std::cout << "Shooty tower lvl 3 could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!barbedWireTx.loadFromFile("images/Towers/ZapperLvl1.png"))
	{
		std::cout << "Barbed Wire could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!barbedWirelv2Tx.loadFromFile("images/Towers/ZapperLvl2.png"))
	{
		std::cout << "Barbed Wire  lvl 2 could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!barbedWirelv3Tx.loadFromFile("images/Towers/ZapperLvl3.png"))
	{
		std::cout << "Barbed Wire  lvl 3 could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	//////////////////////////////// Load audio files ////////////////////////////////
	if (!gameMusic.openFromFile("Audio/gameMusic.wav"))
	{
		std::cout << "Music could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	gameMusic.setLoop(true);
	gameMusic.setVolume(50);
	gameMusic.play();

	if (!gunshot_buffer.loadFromFile("Audio/gunshotSound.wav"))
	{
		std::cout << "Gunshot sound could not be loaded. Check filepath" << std::endl;
	}
	gunshotSound.setBuffer(gunshot_buffer);
	gunshotSound.setVolume(30);

	if (!reload_buffer.loadFromFile("Audio/reloadSound.wav"))
	{
		std::cout << "Reload sound could not be loaded. Check filepath" << std::endl;
	}
	reloadSound.setBuffer(reload_buffer);
	reloadSound.setVolume(50);

	if (!towershot_buffer.loadFromFile("Audio/towershotSound.wav"))
	{
		std::cout << "Gunshot sound could not be loaded. Check filepath" << std::endl;
	}
	towershotSound.setBuffer(towershot_buffer);
	towershotSound.setVolume(20);

	if (!upgrade_buffer.loadFromFile("Audio/upgradeSound.wav"))
	{
		std::cout << "Upgrade sound could not be loaded. Check filepath" << std::endl;
	}
	upgradeSound.setBuffer(upgrade_buffer);
	upgradeSound.setVolume(50);
	////////////////////////////// Create window //////////////////////////////

	dimensions.x = 1080;
	dimensions.y = 720;
	menuBar.setSize(sf::Vector2f(dimensions.x, 70));
	menuBar.setFillColor(sf::Color(0, 0, 0, 255));

	// Create buttons
	createButtons();

	// Create pause screen overlay
	createPauseScreen();

	///////////////////////////////// Mouse Cursor ////////////////////////////////////

	sf::View fixed = window.getView();
	sf::Texture mouseTexture_target;
	if (!mouseTexture_target.loadFromFile("images/target.png"))
	{
		std::cout << "Mouse cursor01 file not found. Check filepath" << std::endl;
	}
	sf::Texture mouseTexture_wrench;
	if (!mouseTexture_wrench.loadFromFile("images/wrench.png"))
	{
		std::cout << "Mouse cursor02 file not found. Check filepath" << std::endl;
	}
	sf::Sprite mouse;

	///////////////////////////////// Projectiles ////////////////////////////////////

	//projectile initialization
	Projectile p1(3.0, true);
	Projectile p2(3.0, false);

	sf::Sprite bulletSprite(bulletTexture);

	for (int i = 0; i < 6; i++)
	{
		ammo.push_back(bulletSprite);
	}

	int projTimer = maxProjTimer;
	int reloaded = 0;
	int timer = fireTimer;
	bool shot = false;
	bool towerShot = false;
	bool reloading = false;

	//////////////////////////////// Tower Initialization ////////////////////////////////

	basicTowerSpr.setTexture(basicTowerTx);
	shootyTowerSpr.setTexture(shootyTowerTx);
	barbedWireSpr.setTexture(barbedWireTx);

	Tower barbedWire(&window, barbedWire_HP, barbedWire_DMG, barbedWireSpr, dimensions.x * 0.5f, dimensions.y * 0.8f);				//deals damage to enemies who are walking through it
	Tower basicTower(&window, basicTower_HP, basicTower_DMG, basicTowerSpr, dimensions.x * 0.6f, dimensions.y * 0.8f);				//a simple barricade
	Tower shootyTower(&window, shootyTower_HP, shootyTower_DMG, shootyTowerSpr, dimensions.x * 0.7f, dimensions.y * 0.72f);			//shoots the enemies

	towersHP.push_back(barbedWire.getHP());
	towersHP.push_back(basicTower.getHP());
	towersHP.push_back(shootyTower.getHP());
	towersLocation.push_back((int)(barbedWire.getXPosition() - basicTower.getSpriteGlobalBounds().width / 2));
	towersLocation.push_back((int)(basicTower.getXPosition() - basicTower.getSpriteGlobalBounds().width / 2));
	towersLocation.push_back((int)(shootyTower.getXPosition() - shootyTower.getSpriteGlobalBounds().width / 2 + 10));
	tower.push_back(barbedWire);
	tower.push_back(basicTower);
	tower.push_back(shootyTower);

	////////////////////////////// Add animations //////////////////////////////

	setSpriteAnimations(&skellyAni, &skelly_texture, 's', "Skelly");
	setSpriteAnimations(&rhinoAni, &rhino_texture, 's', "Rhino");
	setSpriteAnimations(&lancerAni, &lancer_texture, 'm', "Lancer");
	setSpriteAnimations(&demonAni, &demon_texture, 'd', "Demon");
	setSpriteAnimations(&gunnerAni, &gunner_texture, 's', "Gunner");

	//////////////////////////////// Wave of enemies /////////////////////////////////
	createRounds();

	//////////////////////////////// Scoreboard ////////////////////////////////

	int scoreTimer = 1000;

	if (!pixeled.loadFromFile("fonts/Pixeled.ttf"))
	{
		std::cerr << "Font failed to load." << std::endl;
		return -1;
	}

	scoreText.setFont(pixeled);
	scoreText.setString(std::to_string(gameScore.getTotal()));
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10);

	// Joe
	sf::Sprite background(backgroundTexture);
	background.setScale((float)(dimensions.x / background.getGlobalBounds().width), (float)(dimensions.y / background.getGlobalBounds().height));
	joeSprite.setTexture(joeTexture);
	joeSprite.setPosition(0.92f * dimensions.x, 0.62f * dimensions.y);
	armSprite.setTexture(armTexture);
	armSprite.setPosition(joeSprite.getPosition().x + joeSprite.getGlobalBounds().width / 2 - 3,
		joeSprite.getPosition().y + joeSprite.getGlobalBounds().height / 2 + 5);
	armSprite.setOrigin(armSprite.getGlobalBounds().width, armSprite.getGlobalBounds().height / 2);
	bulletSprite.setTexture(bulletTexture);

	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////MAIN GAME LOOP/////////////////////////
	while (running)
	{
		// Mouse cursor change
		if (sf::Mouse::getPosition(window).y > menuBar.getGlobalBounds().height)
		{
			mouse.setTexture(mouseTexture_target);
			mouse.setOrigin(mouse.getGlobalBounds().width / 2, mouse.getGlobalBounds().height / 2);
		}
		else
		{
			mouse.setTexture(mouseTexture_wrench);
			mouse.setOrigin(0, 0);
		}

		//////////////////// BACKGROUND : Draw background image beneath all other images ////////////////////
		window.draw(background);

		if (!paused)
		{
			window.setMouseCursorVisible(false);
			//sets rotation of arm based on mouse location (gun points at mouse pointer)
			armSprite.setRotation((float)((180.0 / PI) * atan2(0.52 * dimensions.y - sf::Mouse::getPosition(window).y, 0.76f * dimensions.x - sf::Mouse::getPosition(window).x)));

			// Score
			scoreTimer--;
			if (scoreTimer == 0)
			{
				gameScore.add(incomeRate);
				scoreTimer = 1000;
			}

			//==================================================// SHOOTING //==================================================//
			// Shooting mechanic
			center = armSprite.getPosition();
			mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			mouseAimDir = mousePos - center;
			mouseAimDirNorm = mouseAimDir / sqrt(pow(mouseAimDir.x, 2) + pow(mouseAimDir.y, 2));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
				&& sf::Mouse::getPosition(window).y > menuBar.getGlobalBounds().height
				&& projTimer == maxProjTimer && reloading == false
				&& !ammo.empty())
			{
				gunshotSound.play();
				shot = true;
				ammo.pop_back();
				if (ammo.empty()) reloading = true;
				p1.bullet.setPosition(center + sf::Vector2f(-5, 0));
				p1.vel = (mouseAimDirNorm * p1.getMaxVel());
				currentProj.push_back(Projectile(p1));
			}
			else if (reloading)
			{
				if (reloaded == 6)
				{
					reloaded = 0;
					reloading = false;
				}
			}
			if (shot == true)
			{
				projTimer--;
				if (projTimer == 0)
				{
					shot = false;
					projTimer = maxProjTimer;
				}
			}

			// Deleting bullets off screen or collisions
			if (!currentProj.empty())
			{
				for (unsigned int i = 0; i < currentProj.size(); i++)
				{
					currentProj[i].bullet.move(currentProj[i].vel);

					// Checks collision with enemies from the bullet scope
					if (currentProj[i].checkCollision(&wave, 25)) currentProj.erase(currentProj.begin() + i);

					// Ends the loop if the bullet vector is empty and reading attempt is made to see next element in empty vector
					if (currentProj.empty())
					{
						break;
					}
					// Deletes the bullet if it goes off screen
					if (currentProj[i].bullet.getPosition().x < 0 || currentProj[i].bullet.getPosition().x > dimensions.x
						|| currentProj[i].bullet.getPosition().y < 0 || currentProj[i].bullet.getPosition().y > dimensions.y)
					{
						currentProj.erase(currentProj.begin() + i);
					}
				}
			}

			//==================================================// ENEMY SPAWNING //==================================================//

			std::vector<MonsterType> name;
			name.push_back(SKELLY);
			name.push_back(RHINO);
			name.push_back(LANCER);
			name.push_back(DEMON);
			name.push_back(GUNNER);
			// Parameters: maximum spawns, clock, spawn timer, wave vector, window, animation vector, dmg, hp, boundary, target's hp, name, score
			runSpawners(&skellyAmount[waveRound], &clock_Skelly, SKELLY_SPWN_TIMER, &wave, &window, &skellyAni, skelly_DMG, skelly_HP, boundary, &targetHP, name.at(0), &gameScore);
			runSpawners(&rhinoAmount[waveRound], &clock_Rhino, RHINO_SPWN_TIMER, &wave, &window, &rhinoAni, rhino_DMG, rhino_HP, boundary, &targetHP, name.at(1), &gameScore);
			runSpawners(&lancerAmount[waveRound], &clock_Lancer, LANCER_SPWN_TIMER, &wave, &window, &lancerAni, lancer_DMG, lancer_HP, boundary, &targetHP, name.at(2), &gameScore);
			runSpawners(&demonAmount[waveRound], &clock_Demon, DEMON_SPWN_TIMER, &wave, &window, &demonAni, demon_DMG, demon_HP, boundary, &targetHP, name.at(3), &gameScore);
			runSpawners(&gunnerAmount[waveRound], &clock_Gunner, GUNNER_SPWN_TIMER, &wave, &window, &gunnerAni, gunner_DMG, gunner_HP, boundary, &targetHP, name.at(4), &gameScore);

			if (!waves.empty() && waves.at(waveRound)->getNumMobs() == 0)
			{
				breakCounter++;
				if (breakCounter == breakTimer)
				{
					breakCounter = 0;
					breakTimer += 250;
					if (waveRound < numLevels - 1)
					{
						waveRound++;
					}
				}
			}
			// Targets of mobs and targeted health
			if (!tower.at(currentTarget).amIAlive())
			{
				if (currentTarget < 2)
				{
					currentTarget++;
				}
			}

			// Controlling waves of mobs, updating animations, and moving
			for (unsigned int i = 0; i < wave.size(); i++)
			{
				wave[i]->setTarget(towersLocation.at(currentTarget), towersHP.at(currentTarget));
				if (currentTarget == 2 && !tower.at(currentTarget).amIAlive())
				{
					wave[i]->setTarget((int)(dimensions.x - 175), new int(1));
				}
				wave[i]->run();
				wave[i]->attackMove();
				if (wave[i]->isDead())
				{
					if (waves.at(waveRound)->getNumMobs() > 0) waves.at(waveRound)->deductMob();
					wave.erase(wave.begin() + i);
				}
			}

			//==================================================// TOWERS //==================================================//
			// Sets towers' targets
			for (unsigned int i = 0; i < wave.size(); i++)
			{
				//checks to see if the enemy is attacking. The clock keeps the attack from having every game tick
				if (wave.at(i)->isCurrAttacking())
				{
					tower.at(currentTarget).updateHealthBar();
				}
				//checks to see if any enemies should take damage from the barbed wire
				if (tower.at(0).amIAlive() && wave.at(i)->getSpriteGlobalBounds().intersects(tower.at(0).getSpriteGlobalBounds()))
				{
					if (wave.at(i)->isAliveFunc())
					{
						if (barbedTimer.getElapsedTime().asSeconds() > 0.5f)
						{
							wave.at(i)->takeDamage(barbedWire_DMG);
							barbedTimer.restart();
						}
					}
				}
			}

			unsigned int enemyCounter = 0;
			int targetValue = 0;
			// Shoot only when wave is not empty
			if (tower.at(2).amIAlive() && !wave.empty())
			{
				for (unsigned int m = 0; m < wave.size(); m++)
				{
					Monster* targetTemp = wave.at(m);
					int targetValueTemp = (int)(targetTemp->getCurrentLocation().x * TOWER_POS_WEIGHT + targetTemp->getHealth() * TOWER_HP_WEIGHT
						+ targetTemp->getDamage() * TOWER_DMG_WEIGHT);

					if (targetValueTemp > targetValue && targetTemp->isAliveFunc())
					{
						enemyCounter = m;
						targetValue = targetValueTemp;
					}
				}

				// Initializes aiming mechanics
				if (enemyCounter < wave.size())
				{
					towerOrigin.x = shootyTower.getSprite().getPosition().x + 30;
					towerOrigin.y = shootyTower.getSprite().getPosition().y + 35;
					enemyPosition = sf::Vector2f(wave.at(enemyCounter)->getCurrentLocation());
					towerAimDirection = enemyPosition - towerOrigin;
					towerAimDirNorm = towerAimDirection / sqrt(pow(towerAimDirection.x, 2) + pow(towerAimDirection.y, 2));
				}
				// Timer for shooting
				if (shootyTimer.getElapsedTime().asSeconds() > 1.0f)
				{
					if (timer == fireTimer)
					{
						towershotSound.play();
						towerShot = true;
						p2.bullet.setPosition(towerOrigin);
						p2.vel = (towerAimDirNorm * p2.getMaxVel());
						towerProjectiles.push_back(Projectile(p2));
					}
					shootyTimer.restart();
				}
				// Resetting the timer and allowing tower to shoot again
				if (towerShot == true)
				{
					timer--;
					if (timer <= 0)
					{
						timer = 0;
						towerShot = false;
						timer = fireTimer;
					}
				}
				if (!towerProjectiles.empty())
				{
					for (unsigned int i = 0; i < towerProjectiles.size(); i++)
					{
						towerProjectiles[i].bullet.move(towerProjectiles[i].vel);
						window.draw(towerProjectiles[i].bullet);

						// Checks collision with enemies from the bullet scope
						if (towerProjectiles[i].checkCollision(&wave, tower.at(2).getDmg()))
						{
							towerProjectiles.erase(towerProjectiles.begin() + i);
						}

						// Ends the loop if the bullet vector is empty and reading attempt is made to see next element in empty vector
						if (towerProjectiles.empty())
						{
							break;
						}
						// Deletes the bullet if it goes off screen
						if (towerProjectiles[i].bullet.getPosition().x < 0 || towerProjectiles[i].bullet.getPosition().x > dimensions.x
							|| towerProjectiles[i].bullet.getPosition().y < 0 || towerProjectiles[i].bullet.getPosition().y > dimensions.y)
						{
							towerProjectiles.erase(towerProjectiles.begin() + i);
						}
					}
				}
			}
			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
		}


		//--//--//--//--//--//--//--//--//--//--//--/ DRAW /--//--//--//--//--//--//--//--//--//--//--//--//

		// Score
		scoreText.setString("$ " + std::to_string(gameScore.getTotal()));
		// Displays Round # text
		drawRound(&window);

		//////////////////// MIDGROUND : Drawing the main sprites on screen ////////////////////
		window.draw(armSprite);
		window.draw(joeSprite);

		if (!currentProj.empty())
		{
			for (unsigned int i = 0; i < currentProj.size(); i++)
			{
				window.draw(currentProj[i].bullet);
			}
		}
		// Draws enemies
		for (unsigned int i = 0; i < wave.size(); i++)
		{
			wave[i]->draw();
			if (wave[i]->getCurrentLocation().x >= dimensions.x - 175)
			{
				return 3;
			}
		}

		// Draws towers
		for (unsigned int i = 0; i < tower.size(); i++)
		{
			if (tower.at(i).amIAlive()) tower[i].draw();
		}

		//////////////////// FOREGROUND : Draw menu bar on top of all other images ////////////////////

		//************// Bar //************//
		window.draw(menuBar);
		window.draw(scoreText);

		//************// Buttons //************//
		window.draw(upgrade_01_btn);
		window.draw(upgrade_02_btn);
		window.draw(upgrade_03_btn);
		window.draw(upgrade_04_btn);
		window.draw(quit_btn);
		window.draw(mute_btn);
		//************// Buttons' Text //************//
		window.draw(upgrade_01_cost);
		window.draw(upgrade_02_cost);
		window.draw(upgrade_03_cost);
		window.draw(upgrade_04_cost);

		// Update cost display on buttons
		updateCostButtons();

		// Draws the pause screen
		if (paused)
		{
			drawPauseScreen(&window);
		}

		// Draws exit box
		if (exitBoxVisible)
		{
			paused = true;
			drawExitScreen(&window);
		}

		//************// Bullet Reload Images //************//
		for (unsigned int i = 0; i < ammo.size(); i++)
		{
			ammo[i].setPosition(sf::Vector2f((float)(i * 11) + 1 + 10, 15 + scoreText.getGlobalBounds().height));
			window.draw(ammo[i]);
		}

		//************// Mouse cursor //************//
		mouse.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		window.setView(fixed);
		window.draw(mouse);

		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return -1;
			}
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				if (reloaded != 6 && reloading == true)
				{
					reloadSound.play();
					reloaded++;
					ammo.push_back(bulletSprite);
					continue;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					paused = !paused;
					exitBoxVisible = false;
				}
				/////////test commands for win and lose screens delete after win/lose conditions implemented
				else if (event.key.code == sf::Keyboard::W)
				{
					return 2;
				}
				else if (event.key.code == sf::Keyboard::L)
				{
					return 3;
				}
				else if (event.key.code == sf::Keyboard::C) // Increase monster AD
				{
					gameScore.setTotal(10000);
				}
				////////////////////////////////////////////////////////////////////////////////////////////
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (buttonIsClicked(&upgrade_01_btn, &window)
					&& gameScore.getTotal() - upgrade_01_cost_amount >= 0
					&& barbedWire_lvl < 10)			// Upgrades barbed wire
				{
					gameScore.setTotal(gameScore.getTotal() - upgrade_01_cost_amount);
					barbedWire_lvl++;
					tower.at(0).upgradeHealth();
					if (barbedWire_lvl > 3)
					{
						tower.at(0).updateSprite(&barbedWirelv2Tx);
					}
					if (barbedWire_lvl > 6)
					{
						tower.at(0).updateSprite(&barbedWirelv3Tx);
					}
					tower.at(0).updateHealthBar();
					clicked = true;
					upgradeSound.play();
				}
				else if (buttonIsClicked(&upgrade_02_btn, &window)
					&& gameScore.getTotal() - upgrade_02_cost_amount >= 0
					&& barricade_lvl < 10)			// Upgrades barricade
				{
					gameScore.setTotal(gameScore.getTotal() - upgrade_02_cost_amount);
					barricade_lvl++;
					tower.at(1).upgradeHealth();
					if (barricade_lvl > 3)
					{
						tower.at(1).updateSprite(&basicTowerlv2Tx);

					}
					if (barricade_lvl > 6)
					{
						tower.at(1).updateSprite(&basicTowerlv3Tx);

					}
					tower.at(1).updateHealthBar();
					clicked = true;
					upgradeSound.play();
				}
				else if (buttonIsClicked(&upgrade_03_btn, &window)
					&& gameScore.getTotal() - upgrade_03_cost_amount >= 0
					&& shootingTower_lvl < 10)			// Upgrades shooty tower
				{
					gameScore.setTotal(gameScore.getTotal() - upgrade_03_cost_amount);
					shootingTower_lvl++;
					tower.at(2).upgradeHealth();
					if (shootingTower_lvl > 3)
					{
						tower.at(2).updateSprite(&shootyTowerlv2Tx);

					}
					if (shootingTower_lvl > 6)
					{
						tower.at(2).updateSprite(&shootyTowerlv3Tx);

					}
					tower.at(2).updateHealthBar();
					tower.at(2).upgradeDmg();
					clicked = true;
					upgradeSound.play();
				}
				else if (buttonIsClicked(&upgrade_04_btn, &window)
					&& gameScore.getTotal() - upgrade_04_cost_amount >= 0
					&& incomeRate_lvl < 10)			// Upgrades income rate
				{
					incomeRate = incomeRateDefault * incomeRate_lvl;
					gameScore.setTotal(gameScore.getTotal() - upgrade_04_cost_amount);
					incomeRate_lvl++;
					clicked = true;
					upgradeSound.play();
				}
				else if (buttonIsClicked(&quit_btn, &window))				// Exits game
				{
					exitBoxVisible = true;
				}
				else if (buttonIsClicked(&mute_btn, &window))				// Mutes sound
				{
					if (gameMusic.getStatus() == sf::SoundSource::Playing)
					{
						gameMusic.pause();
						gunshotSound.setVolume(0);
						reloadSound.setVolume(0);
						towershotSound.setVolume(0);
						upgradeSound.setVolume(0);
					}
					else
					{
						gameMusic.play();
						gunshotSound.setVolume(30);
						reloadSound.setVolume(50);
						towershotSound.setVolume(20);
						upgradeSound.setVolume(50);
					}

					std::swap(mute_texture_on, mute_texture_off);
					clicked = true;
				}
				else if (buttonIsClicked(&yes_btn, &window) && exitBoxVisible) // Yes
				{
					return -1;
				}
				else if (buttonIsClicked(&no_btn, &window) && exitBoxVisible) // No
				{
					paused = false;
					exitBoxVisible = false;
				}
			}
		}

		window.clear();
	}

	return -1;
}

void GameScreen::setSpriteAnimations(std::vector<Animation>* ani, sf::Texture* texture, char size, std::string name)
{
	int size_x;
	int size_y;
	switch (size)
	{
	case 's':
		size_x = 40;
		size_y = 49;
		break;
	case 'm':
		size_x = 60;
		size_y = 74;
		break;
	case 'l':
		break;
	case 'd':
		size_x = 68;
		size_y = 60;
		break;
	}
	Animation idle;
	idle.setSpriteSheet(*texture);
	idle.addFrame(sf::IntRect(0, 0, size_x, size_y));
	idle.addFrame(sf::IntRect(size_x, 0, size_x, size_y));
	idle.addFrame(sf::IntRect(size_x * 2, 0, size_x, size_y));
	idle.addFrame(sf::IntRect(size_x * 3, 0, size_x, size_y));
	idle.addFrame(sf::IntRect(size_x * 4, 0, size_x, size_y));
	ani->push_back(idle);

	Animation attack;
	attack.setSpriteSheet(*texture);
	if (name == "Lancer")
	{
		attack.addFrame(sf::IntRect(0, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x * 2, size_y, size_x * 2, size_y));
		attack.addFrame(sf::IntRect(size_x * 2, size_y, size_x * 2, size_y));
		attack.addFrame(sf::IntRect(size_x * 4, size_y, size_x, size_y));
	}
	else
	{
		attack.addFrame(sf::IntRect(0, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x * 2, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x * 3, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x * 4, size_y, size_x, size_y));
	}
	ani->push_back(attack);

	Animation death;
	death.setSpriteSheet(*texture);
	death.addFrame(sf::IntRect(0, size_y * 2, size_x, size_y));
	death.addFrame(sf::IntRect(size_x, size_y * 2, size_x, size_y));
	death.addFrame(sf::IntRect(size_x * 2, size_y * 2, size_x, size_y));
	death.addFrame(sf::IntRect(size_x * 3, size_y * 2, size_x, size_y));
	death.addFrame(sf::IntRect(size_x * 4, size_y * 2, size_x, size_y));
	ani->push_back(death);

	if (size == 'm' || size == 'l')
	{
		Animation special;
		special.setSpriteSheet(*texture);
		special.addFrame(sf::IntRect(0, size_y * 3, size_x, size_y));
		special.addFrame(sf::IntRect(size_x, size_y * 3, size_x, size_y));
		special.addFrame(sf::IntRect(size_x * 2, size_y * 3, size_x, size_y));
		special.addFrame(sf::IntRect(size_x * 3, size_y * 3, size_x, size_y));
		special.addFrame(sf::IntRect(size_x * 4, size_y * 3, size_x, size_y));
		ani->push_back(special);
	}
}
void GameScreen::runSpawners(int* maxSpawn, sf::Clock* clock, float spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* win, std::vector<Animation>* ani, int dmg, int hp, int boundary, int* targetHP, MonsterType name, Score* score)
{
	int r = (rand() % 6) - 3;
	if (clock->getElapsedTime().asSeconds() > spwn_timer + r && *maxSpawn != 0)
	{
		if (name == LANCER)
		{
			Lancer* spawn = new Lancer(win, *ani, dmg, hp, score, name);
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		else if (name == DEMON)
		{
			int ran = rand() % 200 + 1;
			Monster* spawn = new Monster(win, *ani, dmg, hp, score, name);
			spawn->setStartingPosition((float)-25, (float)(300 + ran));
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		else if (name == GUNNER)
		{
			Gunner* spawn = new Gunner(win, *ani, dmg, hp, score, name, wave);
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		else
		{
			Monster* spawn = new Monster(win, *ani, dmg, hp, score, name);
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		*maxSpawn -= 1;
		clock->restart();
	}
}
void GameScreen::createPauseScreen()
{
	int width = 174; // taken from running program
	int height = 36; // taken from running program
	// Gray overlay
	pauseScreen.setSize(dimensions);
	pauseScreen.setFillColor(sf::Color(0, 0, 0, 150));
	pauseScreen.setPosition(sf::Vector2f(0, 0));

	// Pause text
	pauseText.setFont(pixeled);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setString("PAUSED");
	pauseText.setPosition(dimensions.x / 2 - width / 2, dimensions.y / 2 + height / 2);

}
void GameScreen::drawPauseScreen(sf::RenderWindow* win)
{
	win->draw(pauseScreen);
	win->draw(pauseText);
}
void GameScreen::drawExitScreen(sf::RenderWindow* win)
{
	// Load textures
	if (!exit_texture.loadFromFile("images/menu/exit.png"))
	{
		std::cout << "Unable to load exit_texture. Check file path." << std::endl;
	}
	if (!yes_texture.loadFromFile("images/menu/yes.png"))
	{
		std::cout << "Unable to load yes_texture. Check file path." << std::endl;
	}
	if (!no_texture.loadFromFile("images/menu/no.png"))
	{
		std::cout << "Unable to load no_texture. Check file path." << std::endl;
	}

	// Setting texture for sprite
	exit_box.setTexture(exit_texture);
	yes_btn.setTexture(yes_texture);
	no_btn.setTexture(no_texture);

	// Setting text
	exit_question.setString("Are you sure you want to quit?");
	exit_question.setCharacterSize(14);
	exit_question.setFont(pixeled);
	exit_question.setOrigin(exit_question.getGlobalBounds().width / 2, exit_question.getGlobalBounds().height / 2);

	// Setting Origins
	exit_box.setOrigin(exit_box.getGlobalBounds().width / 2, exit_box.getGlobalBounds().height / 2);
	yes_btn.setOrigin(yes_btn.getGlobalBounds().width / 2, yes_btn.getGlobalBounds().height / 2);
	no_btn.setOrigin(no_btn.getGlobalBounds().width / 2, no_btn.getGlobalBounds().height / 2);

	// Setting positions
	int distance = 40;
	exit_box.setPosition(dimensions.x / 2, dimensions.y / 2);
	yes_btn.setPosition(exit_box.getPosition().x - distance * 2, exit_box.getPosition().y + distance);
	no_btn.setPosition(exit_box.getPosition().x + distance * 2, exit_box.getPosition().y + distance);
	exit_question.setPosition(exit_box.getPosition().x, exit_box.getPosition().y - distance);

	win->draw(exit_box);
	win->draw(yes_btn);
	win->draw(no_btn);
	win->draw(exit_question);
}
void GameScreen::drawRound(sf::RenderWindow* win)
{
	//win->draw(pauseText);
	roundText.setFont(pixeled);
	roundText.setCharacterSize(20);
	roundText.setFillColor(sf::Color::White);
	roundText.setString("Round " + std::to_string(waveRound + 1));
	roundText.setPosition(dimensions.x / 2 - roundText.getGlobalBounds().width / 2, 90);
	win->draw(roundText);
}

void GameScreen::createRounds()
{
	// Format Order: Round #, # of skelly, # of rhino, # of lancer, # of demon, # of gunner
	waves.push_back(new Wave(1, skellyAmount[0], rhinoAmount[0], lancerAmount[0], demonAmount[0], gunnerAmount[0])); // Round 1
	waves.push_back(new Wave(2, skellyAmount[1], rhinoAmount[1], lancerAmount[1], demonAmount[1], gunnerAmount[1])); // Round 2
	waves.push_back(new Wave(3, skellyAmount[2], rhinoAmount[2], lancerAmount[2], demonAmount[2], gunnerAmount[2])); // Round 3
	waves.push_back(new Wave(4, skellyAmount[3], rhinoAmount[3], lancerAmount[3], demonAmount[3], gunnerAmount[3])); // Round 4
	waves.push_back(new Wave(5, skellyAmount[4], rhinoAmount[4], lancerAmount[4], demonAmount[4], gunnerAmount[4])); // Round 5
	waves.push_back(new Wave(6, skellyAmount[5], rhinoAmount[5], lancerAmount[5], demonAmount[5], gunnerAmount[5])); // Round 6
	waves.push_back(new Wave(7, skellyAmount[6], rhinoAmount[6], lancerAmount[6], demonAmount[6], gunnerAmount[6])); // Round 7
	waves.push_back(new Wave(8, skellyAmount[7], rhinoAmount[7], lancerAmount[7], demonAmount[7], gunnerAmount[7])); // Round 8
	waves.push_back(new Wave(9, skellyAmount[8], rhinoAmount[8], lancerAmount[8], demonAmount[8], gunnerAmount[8])); // Round 9
	waves.push_back(new Wave(10, skellyAmount[9], rhinoAmount[9], lancerAmount[9], demonAmount[9], gunnerAmount[9])); // Round 10
}

// Create buttons
void GameScreen::createButtons()
{
	// Load textures
	if (!upgrade_01_texture.loadFromFile("images/buttons/btn_01.png"))
	{
		std::cout << "Unable to load upgrade_01_texture. Check file path." << std::endl;
	}
	if (!upgrade_02_texture.loadFromFile("images/buttons/btn_02.png"))
	{
		std::cout << "Unable to load upgrade_02_texture. Check file path." << std::endl;
	}
	if (!upgrade_03_texture.loadFromFile("images/buttons/btn_03.png"))
	{
		std::cout << "Unable to load upgrade_03_texture. Check file path." << std::endl;
	}
	if (!upgrade_04_texture.loadFromFile("images/buttons/btn_04.png"))
	{
		std::cout << "Unable to load upgrade_04_texture. Check file path." << std::endl;
	}
	if (!quit_texture.loadFromFile("images/buttons/btn_05.png"))
	{
		std::cout << "Unable to load quit_texture. Check file path." << std::endl;
	}
	if (!mute_texture_on.loadFromFile("images/buttons/mute_01.png"))
	{
		std::cout << "Unable to load mute_texture_01. Check file path." << std::endl;
	}
	if (!mute_texture_off.loadFromFile("images/buttons/mute_02.png"))
	{
		std::cout << "Unable to load mute_texture_02. Check file path." << std::endl;
	}

	float center_y_menuBar = (float)(menuBar.getGlobalBounds().height / 2);
	int width = 60;
	int height = 60;
	float center_x_btn = (float)width / 2;
	float center_y_btn = (float)height / 2;
	int offset_x = 100;
	int gap = 100;

	// Set textures for sprites
	upgrade_01_btn.setTexture(upgrade_01_texture);
	upgrade_02_btn.setTexture(upgrade_02_texture);
	upgrade_03_btn.setTexture(upgrade_03_texture);
	upgrade_04_btn.setTexture(upgrade_04_texture);
	quit_btn.setTexture(quit_texture);
	mute_btn.setTexture(mute_texture_on);

	// Set origin for sprites
	upgrade_01_btn.setOrigin(center_x_btn, center_y_btn);
	upgrade_02_btn.setOrigin(center_x_btn, center_y_btn);
	upgrade_03_btn.setOrigin(center_x_btn, center_y_btn);
	upgrade_04_btn.setOrigin(center_x_btn, center_y_btn);
	quit_btn.setOrigin(center_x_btn, center_y_btn);
	mute_btn.setOrigin(center_x_btn, center_y_btn);

	// Set positions of sprites
	upgrade_01_btn.setPosition((float)gap + (float)width, center_y_menuBar);
	upgrade_02_btn.setPosition((float)gap + (float)width * 2 + 10, center_y_menuBar);
	upgrade_03_btn.setPosition((float)gap + (float)width * 3 + 20, center_y_menuBar);
	upgrade_04_btn.setPosition((float)gap + (float)width * 4 + 30, center_y_menuBar);
	quit_btn.setPosition((float)gap + (float)width * 5 + 40, center_y_menuBar);
	mute_btn.setPosition((float)gap + (float)width * 6 + 50, center_y_menuBar);

	// Set font
	upgrade_01_cost.setFont(pixeled);
	upgrade_02_cost.setFont(pixeled);
	upgrade_03_cost.setFont(pixeled);
	upgrade_04_cost.setFont(pixeled);
	upgrade_01_cost.setCharacterSize(10);
	upgrade_02_cost.setCharacterSize(10);
	upgrade_03_cost.setCharacterSize(10);
	upgrade_04_cost.setCharacterSize(10);
	upgrade_01_cost.setFillColor(sf::Color(196, 39, 39, 255));
	upgrade_02_cost.setFillColor(sf::Color(196, 39, 39, 255));
	upgrade_03_cost.setFillColor(sf::Color(196, 39, 39, 255));
	upgrade_04_cost.setFillColor(sf::Color(196, 39, 39, 255));

	// Set costs
	upgrade_01_cost.setString("$" + std::to_string(upgrade_01_cost_amount));
	upgrade_02_cost.setString("$" + std::to_string(upgrade_02_cost_amount));
	upgrade_03_cost.setString("$" + std::to_string(upgrade_03_cost_amount));
	upgrade_04_cost.setString("$" + std::to_string(upgrade_04_cost_amount));
	// Set position
	upgrade_01_cost.setPosition(upgrade_01_btn.getPosition().x - 5 - upgrade_01_btn.getGlobalBounds().width / 2 + 13, upgrade_01_btn.getPosition().y + 15);
	upgrade_02_cost.setPosition(upgrade_02_btn.getPosition().x - 5 - upgrade_02_btn.getGlobalBounds().width / 2 + 13, upgrade_02_btn.getPosition().y + 15);
	upgrade_03_cost.setPosition(upgrade_03_btn.getPosition().x - 5 - upgrade_03_btn.getGlobalBounds().width / 2 + 13, upgrade_03_btn.getPosition().y + 15);
	upgrade_04_cost.setPosition(upgrade_04_btn.getPosition().x - 5 - upgrade_04_btn.getGlobalBounds().width / 2 + 13, upgrade_04_btn.getPosition().y + 15);
}

void GameScreen::updateCostButtons()
{
	// Updating the variables
	upgrade_01_cost_amount = moneyDeduction * barbedWire_lvl;
	upgrade_02_cost_amount = moneyDeduction * barricade_lvl;
	upgrade_03_cost_amount = (int)(moneyDeduction * 1.5 * shootingTower_lvl);
	upgrade_04_cost_amount = moneyDeduction * 2 * incomeRate_lvl;

	// Updating the text
	upgrade_01_cost.setString("$" + std::to_string(upgrade_01_cost_amount));
	upgrade_02_cost.setString("$" + std::to_string(upgrade_02_cost_amount));
	upgrade_03_cost.setString("$" + std::to_string(upgrade_03_cost_amount));
	upgrade_04_cost.setString("$" + std::to_string(upgrade_04_cost_amount));

	// Set color
	if (gameScore.getTotal() < upgrade_01_cost_amount) upgrade_01_cost.setFillColor(sf::Color(81, 39, 22, 255));
	else upgrade_01_cost.setFillColor(sf::Color::Green);
	if (gameScore.getTotal() < upgrade_02_cost_amount) upgrade_02_cost.setFillColor(sf::Color(81, 39, 22, 255));
	else upgrade_02_cost.setFillColor(sf::Color::Green);
	if (gameScore.getTotal() < upgrade_03_cost_amount) upgrade_03_cost.setFillColor(sf::Color(81, 39, 22, 255));
	else upgrade_03_cost.setFillColor(sf::Color::Green);
	if (gameScore.getTotal() < upgrade_04_cost_amount) upgrade_04_cost.setFillColor(sf::Color(81, 39, 22, 255));
	else upgrade_04_cost.setFillColor(sf::Color::Green);

	// Set to "Max" if lvl 9
	if (barbedWire_lvl == 10)
	{
		upgrade_01_cost.setString("MAX");
		upgrade_01_cost.setFillColor(sf::Color::White);
	}
	if (barricade_lvl == 10)
	{
		upgrade_02_cost.setString("MAX");
		upgrade_02_cost.setFillColor(sf::Color::White);
	}
	if (shootingTower_lvl == 10)
	{
		upgrade_03_cost.setString("MAX");
		upgrade_03_cost.setFillColor(sf::Color::White);
	}
	if (incomeRate_lvl == 10)
	{
		upgrade_04_cost.setString("MAX");
		upgrade_04_cost.setFillColor(sf::Color::White);
	}
}

bool GameScreen::buttonIsClicked(sf::Sprite* sprite, sf::RenderWindow* window)
{
	float x1 = sprite->getPosition().x - sprite->getGlobalBounds().width / 2;
	float x2 = x1 + sprite->getGlobalBounds().width;
	float y1 = sprite->getPosition().y - sprite->getGlobalBounds().height / 2;
	float y2 = y1 + sprite->getGlobalBounds().height;
	int mouse_x = sf::Mouse::getPosition(*window).x;
	int mouse_y = sf::Mouse::getPosition(*window).y;
	if (//sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		mouse_x > x1 && mouse_x < x2 && mouse_y > y1 && mouse_y < y2)
	{
		return true;
	}
	return false;
}