#include "cScreen.hpp"
#include "GameScreen.hpp"

GameScreen::GameScreen(void) {}

int GameScreen::Run(sf::RenderWindow &window){
	sf::Event event;
	bool running = true;

	// Loading files
	if (!backgroundTexture.loadFromFile("images/background.png")) {
		std::cerr << "background failed" << std::endl;
		return -1;
	}
	if (!joeTexture.loadFromFile("images/revolverJoe.png")) {
		std::cerr << "revolverJoe failed" << std::endl;
		return -1;
	}
	if (!armTexture.loadFromFile("images/arm.png")) {
		std::cerr << "arm failed" << std::endl;
		return -1;
	}
	if (!bulletTexture.loadFromFile("images/bullet.png")) {
		std::cerr << "bullet failed" << std::endl;
		return -1;
	}

	//////////////////////////////// Load enemy textures ////////////////////////////////

	if (!skelly_texture.loadFromFile("images/enemies/skelly.png")) {
		std::cerr << "skelly_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!rhino_texture.loadFromFile("images/enemies/rhino.png")) {
		std::cerr << "rhino_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!lancer_texture.loadFromFile("images/enemies/lancer.png")) {
		std::cerr << "lancer_spriteSheet failed" << std::endl;
		return -1;
	}
	if (!demon_texture.loadFromFile("images/enemies/demon.png")) {
		std::cerr << "demon_spriteSheet failed" << std::endl;
		return -1;
	}

	//////////////////////////////// Load tower textures ////////////////////////////////

	if (!basicTowerTx.loadFromFile("images/Towers/NewBasicTower.png"))
	{
		std::cout << "Basic tower could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!shootyTowerTx.loadFromFile("images/Towers/ShootyTower.png"))
	{
		std::cout << "Shooty tower could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	if (!barbedWireTx.loadFromFile("images/Towers/NewBarbedWire.png"))
	{
		std::cout << "Barbed Wire could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	//////////////////////////////// Load audio files ////////////////////////////////
	if (!MUSIC.openFromFile("Audio/MUSIC.wav"))
	{
		std::cout << "Music could not be loaded. Check filepath" << std::endl;
		return -1;
	}
	MUSIC.setLoop(true);
	MUSIC.setVolume(50);
	MUSIC.play();
	
	if (!gunshot_buffer.loadFromFile("Audio/gunshotSound.wav")) 
	{
		std::cout << "Gunshot sound could not be loaded. Check filepath" << std::endl;
	}
	gunshotSound.setBuffer(gunshot_buffer);
	gunshotSound.setVolume(20);

	if (!reload_buffer.loadFromFile("Audio/reloadSound.wav")) 
	{
		std::cout << "Reload sound could not be loaded. Check filepath" << std::endl;
	}
	reloadSound.setBuffer(reload_buffer);
	reloadSound.setVolume(50);

	////////////////////////////// Create window //////////////////////////////
	//dimensions.x = backgroundTexture.getSize().x; // DELETE IF WE DECIDE NOT TO DO FULLSCREEN
	//dimensions.y = backgroundTexture.getSize().y; // DELETE IF WE DECIDE NOT TO DO FULLSCREEN
	dimensions.x = 1080;
	dimensions.y = 720;
	menuBar.setSize(sf::Vector2f(dimensions.x, 70));
	menuBar.setFillColor(sf::Color(0, 0, 0, 255));
	createPauseScreen();

	///////////////////////////////// Projectiles ////////////////////////////////////

	//projectile initialization
	Projectile p1(3.0);
	Projectile p2(3.0);

	sf::Sprite bulletSprite(bulletTexture);

	for (int i = 0; i < 6; i++) {
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

	Tower barbedWire(&window, barbedWire_HP, barbedWire_DMG, barbedWireSpr, dimensions.x * 0.5f, dimensions.y * 0.7f);				//deals damage to enemies who are walking through it
	Tower basicTower(&window, basicTower_HP, basicTower_DMG, basicTowerSpr, dimensions.x * 0.6f, dimensions.y * 0.85f);				//a simple barricade
	Tower shootyTower(&window, shootyTower_HP, shootyTower_DMG, shootyTowerSpr, dimensions.x * 0.7f, dimensions.y * 0.7f);			//shoots the enemies

																																	////////////////////////////// Add animations //////////////////////////////

	setSpriteAnimations(&skellyAni, &skelly_texture, 's', "Skelly");
	setSpriteAnimations(&rhinoAni, &rhino_texture, 's', "Rhino");
	setSpriteAnimations(&lancerAni, &lancer_texture, 'm', "Lancer");
	setSpriteAnimations(&demonAni, &demon_texture, 'd', "Demon");

	////////////////////////////// Temporary Placement ///////////////////////////////
	float targetHealth = 200;
	int currentTarget = 0;

	//************************ TOWER HITPOINTS ************************//
	int targetHP = 100;

	//////////////////////////////// Wave of enemies /////////////////////////////////
	test.push_back(skellyAmount);
	test.push_back(rhinoAmount);
	test.push_back(lancerAmount);
	test.push_back(demonAmount);
	createRounds();

	//////////////////////////////// Scoreboard ////////////////////////////////

	int scoreTimer = 1000;

	if (!pixeled.loadFromFile("fonts/Pixeled.ttf")) {
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
		//////////////////// BACKGROUND : Draw background image beneath all other images ////////////////////
		window.draw(background);

		if (!paused)
		{
			//sets rotation of arm based on mouse location (gun points at mouse pointer)
			armSprite.setRotation((float) ((180.0 / PI) * atan2(0.52 * dimensions.y - sf::Mouse::getPosition(window).y, 0.76f * dimensions.x - sf::Mouse::getPosition(window).x)));

			// Score
			scoreTimer--;
			if (scoreTimer == 0)
			{
				gameScore.add(10);
				scoreTimer = 1000;
			}

			//==================================================// SHOOTING //==================================================//
			// Shooting mechanic
			center = armSprite.getPosition();
			mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			mouseAimDir = mousePos - center;
			mouseAimDirNorm = mouseAimDir / sqrt(pow(mouseAimDir.x, 2) + pow(mouseAimDir.y, 2));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && projTimer == maxProjTimer && reloading == false && !ammo.empty())
			{
				gunshotSound.play();
				shot = true;
				ammo.pop_back();
				if (ammo.empty()) reloading = true;
				p1.bullet.setPosition(center + sf::Vector2f(19, 4));
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
					if (currentProj[i].checkCollision(&wave)) currentProj.erase(currentProj.begin() + i);

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

			std::vector<std::string> name;
			name.push_back("Skelly");
			name.push_back("Rhino");
			name.push_back("Lancer");
			name.push_back("Demon");
			//waveRound = 9;
			// Parameters: maximum spawns, clock, spawn timer, wave vector, window, animation vector, dmg, hp, boundary, target's hp, name, score
			runSpawners(&skellyAmount[waveRound], &clock_Skelly, SKELLY_SPWN_TIMER, &wave, &window, &skellyAni, skelly_DMG, skelly_HP, boundary, &targetHP, name.at(0), &gameScore);
			runSpawners(&rhinoAmount[waveRound], &clock_Rhino, RHINO_SPWN_TIMER, &wave, &window, &rhinoAni, rhino_DMG, rhino_HP, boundary, &targetHP, name.at(1), &gameScore);
			runSpawners(&lancerAmount[waveRound], &clock_Lancer, LANCER_SPWN_TIMER, &wave, &window, &lancerAni, lancer_DMG, lancer_HP, boundary, &targetHP, name.at(2), &gameScore);
			runSpawners(&demonAmount[waveRound], &clock_Demon, DEMON_SPWN_TIMER, &wave, &window, &demonAni, demon_DMG, demon_HP, boundary, &targetHP, name.at(3), &gameScore);
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

			// Targets and health
			/*if (targets[0] <= 0) {
			targets[0] = 0;
			currentTarget = 1;
			}
			if (targets[1] <= 0) {
			targets[1] = 0;
			currentTarget = 2;
			}
			if (targets[2] <= 0) { // Game should be over after this
			targets[2] = 0;
			for (unsigned int i = 0; i < wave.size(); i++) {
			wave[i].setTarget(720, 0);
			}
			}*/

			//////////////////////// TEST TAKE DAMAGE CODE ////////////////////////
			/*if (!wave.empty() && wave.back().getX() >= 100 && temp.getElapsedTime().asSeconds() > 1.5f) {
			wave.back().takeDamage(25);
			if (wave.back().getHealth() == 0) {
			wave.pop_back();
			}
			temp.restart();
			}*/
			///////////////////////////////////////////////////////////////////////
			// Controlling waves of mobs, updating animations, and moving
			for (unsigned int i = 0; i < wave.size(); i++)
			{
				wave[i]->run();
				wave[i]->attackMove();
				if (wave[i]->isDead())
				{
					if(waves.at(waveRound)->getNumMobs() > 0) waves.at(waveRound)->deductMob();
					wave.erase(wave.begin() + i);
				}
			}

			//==================================================// TOWERS //==================================================//
			for (unsigned int i = 0; i < wave.size(); i++)
			{
				//checks to see if the enemy is attacking. The clock keeps the attack from having every game tick
				if (wave.at(i)->isCurrAttacking() == true && enemyAtkTimer.getElapsedTime().asSeconds() > 0.5f)
				{
					basicTower.takeDamage(wave.at(i)->getDamage());
					enemyAtkTimer.restart();
				}
				if (basicTower.getHealth() <= 0)
				{
					basicTower.die();
				}

				if (wave.at(i)->isAliveFunc())
				{
					//checks to see if any enemies should take damage from the barbed wire
					if (wave.at(i)->getSpriteGlobalBounds().intersects(barbedWire.getSpriteGlobalBounds()))
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

			// Shoot only when wave is not empty
			if (!wave.empty())
			{
				// Keeps a counter of how many enemies are alive
				while (enemyCounter < wave.size() && wave.at(enemyCounter)->isAliveFunc() == false)
				{
					enemyCounter++;
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
						if (towerProjectiles[i].checkCollision(&wave))
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

		//if the tower is alive, it draws it and then sets the enemies to target it
		if (basicTower.amIAlive())
		{
			for (unsigned int i = 0; i < wave.size(); i++)
			{
				wave.at(i)->setTarget(basicTower.getXPosition() - (int) (basicTower.getSpriteGlobalBounds().width / 2), &targetHP);
			}
			basicTower.draw();
		}
		else
		{
			//if the tower is dead, it resets the enemies' target to what it was before
			for (unsigned int i = 0; i < wave.size(); i++)
			{
				wave.at(i)->setTarget(shootyTower.getXPosition() - (int) (shootyTower.getSpriteGlobalBounds().width / 2), &targetHP);
			}
		}

		// Draws enemies
		for (unsigned int i = 0; i < wave.size(); i++)
		{
			wave[i]->draw();
		}

		shootyTower.draw();
		//barbedWire.draw();

		//////////////////// FOREGROUND : Draw menu bar on top of all other images ////////////////////
		window.draw(menuBar);
		window.draw(scoreText);
		// Drawing the bullets
		for (unsigned int i = 0; i < ammo.size(); i++)
		{
			ammo[i].setPosition(sf::Vector2f((float)(i * 11) + 1 + 10, 15 + scoreText.getGlobalBounds().height));
			window.draw(ammo[i]);
		}

		// Draws the pause screen
		if (paused)	{ drawPauseScreen(&window); }
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return -1;
			}
			else if (event.type == sf::Event::MouseWheelMoved) {
				if (reloaded != 6 && reloading == true) {
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
				}
			}

		}
		window.clear();
	}

	return -1;
}

void GameScreen::setSpriteAnimations(std::vector<Animation>* ani, sf::Texture* texture, char size, std::string name) {
	int size_x;
	int size_y;
	switch (size) {
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
	if (name == "Lancer") {
		attack.addFrame(sf::IntRect(0, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x, size_y, size_x, size_y));
		attack.addFrame(sf::IntRect(size_x * 2, size_y, size_x * 2, size_y));
		attack.addFrame(sf::IntRect(size_x * 2, size_y, size_x * 2, size_y));
		attack.addFrame(sf::IntRect(size_x * 4, size_y, size_x, size_y));
	}
	else {
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

	if (size == 'm' || size == 'l') {
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
void GameScreen::runSpawners(int* maxSpawn, sf::Clock* clock, float spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* win, std::vector<Animation>* ani, int dmg, int hp, int boundary, int* targetHP, std::string name, Score* score) {
	int r = (rand() % 6) - 3;
	if (clock->getElapsedTime().asSeconds() > spwn_timer + r && *maxSpawn != 0) {
		if (name == "Lancer") {
			Lancer* spawn = new Lancer(win, *ani, dmg, hp, score);
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		else if (name == "Demon")
		{
			int ran = rand() % 200 + 1;
			Monster* spawn = new Monster(win, *ani, dmg, hp, score);
			spawn->setStartingPosition((float)-25, (float) (300 + ran));
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		else {
			Monster* spawn = new Monster(win, *ani, dmg, hp, score);
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
	// Format Order: Round #, # of skelly, # of rhino, # of lancer, # of demon
	waves.push_back(new Wave(1, skellyAmount[0], rhinoAmount[0], lancerAmount[0], demonAmount[0])); // Round 1
	waves.push_back(new Wave(2, skellyAmount[1], rhinoAmount[1], lancerAmount[1], demonAmount[1])); // Round 2
	waves.push_back(new Wave(3, skellyAmount[2], rhinoAmount[2], lancerAmount[2], demonAmount[2])); // Round 3
	waves.push_back(new Wave(4, skellyAmount[3], rhinoAmount[3], lancerAmount[3], demonAmount[3])); // Round 4
	waves.push_back(new Wave(5, skellyAmount[4], rhinoAmount[4], lancerAmount[4], demonAmount[4])); // Round 5
	waves.push_back(new Wave(6, skellyAmount[5], rhinoAmount[5], lancerAmount[5], demonAmount[5])); // Round 6
	waves.push_back(new Wave(7, skellyAmount[6], rhinoAmount[6], lancerAmount[6], demonAmount[6])); // Round 7
	waves.push_back(new Wave(8, skellyAmount[7], rhinoAmount[7], lancerAmount[7], demonAmount[7])); // Round 8
	waves.push_back(new Wave(9, skellyAmount[8], rhinoAmount[8], lancerAmount[8], demonAmount[8])); // Round 9
	waves.push_back(new Wave(10, skellyAmount[9], rhinoAmount[9], lancerAmount[9], demonAmount[9])); // Round 10
}