#ifndef BULLET_H
#define BULLET_T

#include "SFML/Graphics.hpp"

#include "MoreInfo.h"
#include "Enemy.h"
#include "ToggleKey.h"

#include <iostream>

class Bullet {
	public:
		Bullet(sf::Texture* texture);

		void renderTo(sf::RenderWindow& window);
		void setPosition(sf::Vector2<float> newPos);
		void updateBullet(bool shooting, int playerX, int playerY);

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds();


		//Collision
		bool enemyCollision(Enemy& enemy);

	private:
		sf::Sprite bullet;
};

#endif