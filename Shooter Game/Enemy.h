#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Animation.h"
#include "MoreInfo.h"

#include <iostream>

class Enemy {
	public:
		Enemy(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, std::string type_normal_hard_advanced);
		
		void renderTo(sf::RenderWindow& window);
		void setPosition(sf::Vector2<float> newPos);
		void move(sf::Vector2<float> distance);
		void updateMovement(bool up, bool left, bool down, bool right);

		void updateAnimation(bool continuous);

		bool isOnScreen();

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds();


	private:
		Animation animation;
		float speed;
		bool moving = false;

		sf::Sprite enemy;
};

#endif