#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Animation.h"
#include "ToggleKey.h"

#include "Enemy.h"

#include <iostream>

class Player {
	public:
		Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void renderTo(sf::RenderWindow& window);
		void setPosition(sf::Vector2<float> newPos);
		void updateAnimation(bool continuous);
		void updateMovement();

		void setDirection(const Animation::Direction& direction);

		int getX();
		int getY();
		void updateBorderBounds();
		sf::FloatRect getGlobalBounds() const;

		//Collisions
		bool enemyCollision(Enemy& enemy);


	private:
		Animation animation;
		float speed;

		bool moving = false;

		sf::Sprite player;
};

#endif