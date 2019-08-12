#include "Bullet.h"


Bullet::Bullet(sf::Texture* texture) {
	bullet.setTexture(*texture);
	bullet.setScale(1 * 2, 1 * 2);
	setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
}

void Bullet::renderTo(sf::RenderWindow& window) {
	window.draw(bullet);
}

void Bullet::setPosition(sf::Vector2<float> newPos) {
 	bullet.setPosition(newPos);
}

void Bullet::updateBullet(bool shooting, int playerX, int playerY) {
	//Touches top of the border
	if (getY() <= 0) {
		setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
		bullet.move(sf::Vector2<float>(0.f, 0.f));
	}


	//Updating shooting
	sf::Vector2<float> bulletMovement(0.f, 0.f);
	bulletMovement.y -= BULLET_SPEED;

	if (shooting) {
		if (getX() == BULLET_ORIGIN) {
			setPosition(sf::Vector2<float>(playerX, playerY));
			//SOUND
		}
	}

	bullet.move(bulletMovement);
}

int Bullet::getX() {
	return bullet.getPosition().x;
}

int Bullet::getY() {
	return bullet.getPosition().y;
}

sf::FloatRect Bullet::getGlobalBounds() {
	return bullet.getGlobalBounds();
}

bool Bullet::enemyCollision(Enemy& enemy) {
	if (getGlobalBounds().intersects(enemy.getGlobalBounds())) {
		return true;
	}
	return false;
}
