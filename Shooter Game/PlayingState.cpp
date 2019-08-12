#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "MoreInfo.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace },
	versionText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30, 25, ARIAL_FONT, "Version 0.0", sf::Color(255, 255, 0)) {


	//Player information
	playerTexture.loadFromFile(PLAYER_T);
	player = std::make_unique<Player>(&playerTexture, sf::Vector2<unsigned>(1, 1), 0.05, PLAYER_SPEED);
	player->setPosition(sf::Vector2<float>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));


	//Enemy information
	enemyTexture.loadFromFile(ENEMY_T);
	for (int x = 0; x < ORIGINAL_ENEMY_COUNT; x++) {
		enemyVector.emplace_back(new Enemy(&enemyTexture, sf::Vector2<unsigned>(2, 1), 0.05, "normal"));
		enemyVector[x]->setPosition(sf::Vector2<float>(enemyPosition.getInt(100, SCREEN_WIDTH - 100), -50)); 
	}



	//Bullet information
	bulletTexture.loadFromFile(PLAYER_BULLET_T);
	bullet = std::make_unique<Bullet>(&bulletTexture);
}

PlayingState::~PlayingState() {
	//
}

void PlayingState::updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.run(machine.buildState<MainMenuState>(machine, window, true)); }
	if (key == sf::Keyboard::Space)  { shooting = isPressed; }
}

void PlayingState::updateEvents() {
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::KeyPressed:
				updateKeyboardInputs(sfEvent.key.code, true);
				break;

			case sf::Event::KeyReleased:
				updateKeyboardInputs(sfEvent.key.code, false);
				break;
		}
	}
}

void PlayingState::update() {
	/*------------------------------------------------------------------------------------------------------------------*/
	//Generalized Updating
	fpsCounter.updateCounter();
	
	player->updateBorderBounds();
	player->updateAnimation(true);
	player->updateMovement();
	bullet->updateBullet(shooting, player->getX(), player->getY());

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Enemy information
	for (auto& enemy : enemyVector) {
		enemy->updateAnimation(true);
		enemy->updateMovement(false, false, true, false);

		//Player collision with enemy
		if (player->enemyCollision(*enemy)) {
			playerLives--;
		}

		//Bullet collision with enemy
		if (bullet->enemyCollision(*enemy)) {
			bullet->setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			enemy->setPosition(sf::Vector2<float>(ENEMY_ORIGIN, ENEMY_ORIGIN));
		}

		//No bullet collision with enemy (spawns two more enemies)
		else if (bullet->getY() <= 0) {
			//Sets bullet position after touching border
			bullet->setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			newEnemy = true;
		}

		//Determines if the enemy is off the screen
		if (enemy->getY() >= SCREEN_HEIGHT && enemy->getY() < ENEMY_ORIGIN) {
			enemy->isOnScreen() == false;
			newEnemy = true;
		}
	}

	//What happens if the bullet does not collide with the enemy
	if (newEnemy == true) {
		std::unique_ptr<Enemy> enemy(new Enemy(&enemyTexture, sf::Vector2<unsigned>(2, 1), 0.05, "normal"));
		enemy->setPosition(sf::Vector2<float>(enemyPosition.getInt(100, SCREEN_WIDTH - 100), -50));
		enemyVector.push_back(std::move(enemy));
		newEnemy = false;
	}



	/*-------------------------------------------------------------------------------------------------------------------*/
	//Removal of Classes
	auto newEnd = std::remove_if(enemyVector.begin(), enemyVector.end(), [](std::unique_ptr<Enemy> & enemy) {
		return !enemy->isOnScreen();
	});
	enemyVector.erase(newEnd, enemyVector.end());
}

void PlayingState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);
	versionText.renderTo(window);

	player->renderTo(window);
	bullet->renderTo(window);

	for (auto& enemy : enemyVector) { enemy->renderTo(window); }


	window.display();
}


