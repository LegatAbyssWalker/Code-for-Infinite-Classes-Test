#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "FPSCounter.h"
#include "Text.h"
#include "MoreInfo.h"
#include "Random.h"
#include "PlaySound.h"
#include "OStringText.h"
#include "ToggleKey.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#include "State.h"
#include "MainMenuState.h"
class StateMachine;

#include <iostream>
#include <fstream>
#include <array>
#include <memory>

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~PlayingState();

		void updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		//Variables and Booleans
		unsigned int playerScore = 0;
		unsigned int playerLives = 3;

		bool shooting = false;
		bool newEnemy = false;

		//Arrays



		//Vectors
		std::vector<std::unique_ptr<Enemy>> enemyVector;


		//Class objects
		std::unique_ptr<Player> player = nullptr;
		std::unique_ptr<Bullet> bullet = nullptr;

		FPSCounter fpsCounter;
		Text versionText;
		Random<> enemyPosition;

		//SFML
		sf::Event sfEvent;
		sf::Texture playerTexture, enemyTexture, bulletTexture;
		sf::Clock dtClock;
		float	  dtTimer;
};


#endif