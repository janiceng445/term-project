#include "main.h"

int main()
{
	// Loading files
	sf::Texture background;
	if (!background.loadFromFile("images/background.png")) {
		std::cerr << "background failed" << std::endl;
		return -1;
	}

	sf::Texture joeTexture;
	if (!joeTexture.loadFromFile("images/revolverJoe.png")) {
		std::cerr << "revolverJoe failed" << std::endl;
		return -1;
	}

	sf::Texture armTexture;
	if (!armTexture.loadFromFile("images/arm.png")) {
		std::cerr << "arm failed" << std::endl;
		return -1;
	}

	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("images/bullet.png")) {
		std::cerr << "bullet failed" << std::endl;
		return -1;
	}

	//////////////////////////////// Load enemy textures ////////////////////////////////

	sf::Texture skelly_texture;
	if (!skelly_texture.loadFromFile("images/enemies/skelly.png")) {
		std::cerr << "skelly_spriteSheet failed" << std::endl;
		return -1;
	}
	sf::Texture rhino_texture;
	if (!rhino_texture.loadFromFile("images/enemies/rhino.png")) {
		std::cerr << "rhino_spriteSheet failed" << std::endl;
		return -1;
	}

	sf::Texture lancer_texture;
	if (!lancer_texture.loadFromFile("images/enemies/lancer.png")) {
		std::cerr << "lancer_spriteSheet failed" << std::endl;
		return -1;
	}

	//////////////////////////////Caleb Demon Tests/////////////////////////////
	sf::Texture demon_texture;
	if (!demon_texture.loadFromFile("images/enemies/demon.png")) {
		std::cerr << "demon_spriteSheet failed" << std::endl;
		return -1;
	}

	////////////////////////////// Add animations //////////////////////////////

	std::vector<Animation> skellyAni;
	setSpriteAnimations(&skellyAni, &skelly_texture, 's', "Skelly");
	std::vector<Animation> rhinoAni;
	setSpriteAnimations(&rhinoAni, &rhino_texture, 's', "Rhino");
	std::vector<Animation> lancerAni;
	setSpriteAnimations(&lancerAni, &lancer_texture, 'm', "Lancer");
	
	//////////////////////////////Caleb Demon Tests/////////////////////////////
	std::vector<Animation> demonAni;
	setSpriteAnimations(&demonAni, &demon_texture, 'd', "Demon");


	////////////////////////////// Create window //////////////////////////////
	sf::Vector2f dimensions;
	dimensions.x = background.getSize().x;
	dimensions.y = background.getSize().y;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Defend the Joe!");
	//sf::RenderWindow window(sf::VideoMode(dimensions.x, dimensions.y), "Defend the Joe!", sf::Style::Fullscreen);
		
	////////////////////////////// Temporary Placement ///////////////////////////////
	float targetHealth = 200;
	float targets[3] = { 50, 55, 60 };
	int targetX[3] = { 150, 200, 250 };
	int currentTarget = 0;
	// Clocks
	sf::Clock clock_Skelly;
	sf::Clock clock_Rhino;
	sf::Clock clock_Lancer;
	//Demon Clock Test
	sf::Clock clock_Demon;
	sf::Clock clock;

	//************************ TOWER HITPOINTS ************************//
	int targetHP = 100;

	//////////////////////////////// Wave of enemies /////////////////////////////////
	int waveRound = 0;
	std::vector<Monster*> wave;

	//////////////////////////////// Scoreboard ////////////////////////////////
	Score gameScore;
	int scoreTimer = 1000;
	sf::Text scoreText;
	sf::Font pixeled;

	if (!pixeled.loadFromFile("fonts/Pixeled.ttf")) {
		std::cerr << "font failed" << std::endl;
		return -1;
	}

	scoreText.setFont(pixeled);
	scoreText.setString(std::to_string(gameScore.getTotal()));
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(650, 10);

	///////////////////////////////// Projectiles ////////////////////////////////////

	sf::Sprite bulletSprite(bulletTexture);
	std::vector<Projectile> currentProj;
	std::vector<sf::Sprite> ammo;

	for (int i = 0; i < 6; i++) {
		ammo.push_back(bulletSprite);
	}

	sf::Vector2f center;
	sf::Vector2f mousePos;
	sf::Vector2f mouseAimDir;
	sf::Vector2f mouseAimDirNorm;

	Projectile p1(3.0);
	int const maxProjTimer = 250;
	int projTimer = maxProjTimer;
	int reloaded = 0;
	bool shot = false;
	bool reloading = false;

	///////////////////////////////////////////////////////////////////////////////////

	//*****MAIN GAME LOOP******//
	while (window.isOpen())
	{
		sf::Event event;

		///////////////////////////////////////////// Gerard /////////////////////////////////////////////
		sf::Sprite background(background);
		background.setScale((float) (dimensions.x / background.getGlobalBounds().width), (float) (dimensions.y / background.getGlobalBounds().height));
		sf::Sprite joeSprite;
		sf::Sprite armSprite;
		sf::Sprite bulletSprite;
		joeSprite.setTexture(joeTexture);
		joeSprite.setPosition(0.92 * dimensions.x, 0.62 * dimensions.y);
		armSprite.setTexture(armTexture);
		armSprite.setPosition(joeSprite.getPosition().x + joeSprite.getGlobalBounds().width / 2 - 3, 
							  joeSprite.getPosition().y + joeSprite.getGlobalBounds().height / 2 + 5);
		armSprite.setOrigin(armSprite.getGlobalBounds().width, armSprite.getGlobalBounds().height / 2);
		armSprite.setRotation((180.0 / PI) * atan2(0.52 * dimensions.y - sf::Mouse::getPosition(window).y, 0.76 * dimensions.x - sf::Mouse::getPosition(window).x));
		//sets rotation of arm based on mouse location (gun points at mouse pointer)
		bulletSprite.setTexture(bulletTexture);

		///////////////////////////////////////////// Samuel /////////////////////////////////////////////

		// Score
		scoreTimer--;
		if (scoreTimer == 0) {
			gameScore.add(10);
			scoreTimer = 1000;
		}
		scoreText.setString(std::to_string(gameScore.getTotal()));

		// Shooting mechanic
		center = armSprite.getPosition();
		mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		mouseAimDir = mousePos - center;
		mouseAimDirNorm = mouseAimDir / sqrt(pow(mouseAimDir.x, 2) + pow(mouseAimDir.y, 2));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && projTimer == maxProjTimer && reloading == false && !ammo.empty()) {
			shot = true;
			ammo.pop_back();
			if (ammo.empty()) reloading = true;
			p1.bullet.setPosition(center + sf::Vector2f(19, 4));
			p1.bullet.setRotation((180.0 / PI) * atan2(248 - sf::Mouse::getPosition(window).y, 550 - sf::Mouse::getPosition(window).x) - 90);
			p1.vel = (mouseAimDirNorm * p1.getMaxVel());
			currentProj.push_back(Projectile(p1));
		}
		else if (reloading) {
			if (reloaded == 6) {
				reloaded = 0;
				reloading = false;
			}
		}
		if (shot == true) {
			projTimer--;
			if (projTimer == 0) {
				shot = false;
				projTimer = maxProjTimer;
			}
		}

		// Drawing the main sprites on screen
		window.draw(background);
		window.draw(armSprite);
		window.draw(joeSprite);
		window.draw(scoreText);

		// Drawing the bullets
		for (unsigned int i = 0; i < ammo.size(); i++) {
			ammo[i].setPosition(sf::Vector2f((float) (i * 11) + 1, 0.0f));
			window.draw(ammo[i]);
		}

		// Deleting bullets off screen or collisions
		if (!currentProj.empty()) {
			for (unsigned int i = 0; i < currentProj.size(); i++) {
				currentProj[i].bullet.move(currentProj[i].vel);
				window.draw(currentProj[i].bullet);

				// Checks collision with enemies from the bullet scope
				if (currentProj[i].checkCollision(&wave)) currentProj.erase(currentProj.begin() + i);

				// Ends the loop if the bullet vector is empty and reading attempt is made to see next element in empty vector
				if (currentProj.empty()) {
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

		///////////////////////////////////////////// Janice /////////////////////////////////////////////

		std::vector<std::string> name;
		name.push_back("Skelly");
		name.push_back("Rhino");
		name.push_back("Lancer");
		//Demon Tests
		name.push_back("Demon");

		// Parameters: maximum spawns, clock, spawn timer, wave vector, window, animation vector, dmg, hp, boundary, target's hp
		runSpawners(&skellyMax, &clock_Skelly, SKELLY_SPWN_TIMER, &wave, &window, &skellyAni, skelly_DMG, skelly_HP, boundary, &targetHP, name.at(0), &gameScore);
		runSpawners(&rhinoMax, &clock_Rhino, RHINO_SPWN_TIMER, &wave, &window, &rhinoAni, rhino_DMG, rhino_HP, boundary, &targetHP, name.at(1), &gameScore);
		runSpawners(&lancerMax, &clock_Lancer, LANCER_SPWN_TIMER, &wave, &window, &lancerAni, lancer_DMG, lancer_HP, boundary, &targetHP, name.at(2), &gameScore);
		//Demon Tests
		runSpawners(&demonMax, &clock_Demon, DEMON_SPWN_TIMER, &wave, &window, &demonAni, demon_DMG, demon_HP, boundary, &targetHP, name.at(3), &gameScore);

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
		for (unsigned int i = 0; i < wave.size(); i++) {
			wave[i]->run();
			wave[i]->draw();
			wave[i]->attackMove();
			if (wave[i]->isDead()) {
				wave.erase(wave.begin() + i);
			}
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////

		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelMoved) {
				if (reloaded != 6 && reloading == true) {
					reloaded++;
					ammo.push_back(bulletSprite);
					continue;
				}
			}
		}
		window.clear();
	}

	return 0;
}

void setSpriteAnimations(std::vector<Animation>* ani, sf::Texture* texture, char size, std::string name) {
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

void runSpawners(int* maxSpawn, sf::Clock* clock, int spwn_timer, std::vector<Monster*>* wave, sf::RenderWindow* win, std::vector<Animation>* ani, int dmg, int hp, int boundary, int* targetHP, std::string name, Score* score) {
	int r = (rand() % 6) - 3;
	if (clock->getElapsedTime().asSeconds() > spwn_timer + r && *maxSpawn != 0) {
		if (name == "Lancer") {
			Lancer* spawn = new Lancer(win, *ani, dmg, hp, score);
			spawn->setTarget(boundary, *&targetHP);
			wave->push_back(spawn);
		}
		//Demon Testing
		else if (name == "Demon")
		{
			int ran = rand() % 200 + 1;
			Monster* spawn = new Monster(win, *ani, dmg, hp, score);
			spawn->setStartingPosition(-25, (300 + ran));
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