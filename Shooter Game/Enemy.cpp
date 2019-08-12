#include "Enemy.h"


Enemy::Enemy(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, std::string type_normal_hard_advanced)
	: animation{ texture, imageCount, switchTime } {

	enemy.setTexture(*texture);
	enemy.setOrigin(enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().height / 2);

	if (type_normal_hard_advanced == "normal")   { speed = NORMAL_ENEMY_SPEED; }
	if (type_normal_hard_advanced == "hard")     { speed = HARD_ENEMY_SPEED; } 
	if (type_normal_hard_advanced == "advanced") { speed = ADVANCED_ENEMY_SPEED; }
}

void Enemy::renderTo(sf::RenderWindow& window) {
	window.draw(enemy);
}

void Enemy::setPosition(sf::Vector2<float> newPos) {
 	enemy.setPosition(newPos);
}

void Enemy::move(sf::Vector2<float> distance) {
	enemy.move(distance);
}

void Enemy::updateMovement(bool up, bool left, bool down, bool right) {
	//Movement
	sf::Vector2<float> enemyMovement(0.f, 0.f);
	if (getX() == ENEMY_ORIGIN) {
		enemyMovement.x = 0;
		enemyMovement.y = 0;
	}
	
	else {
		if (up)    { enemyMovement.y -= speed; }
		if (left)  { enemyMovement.x -= speed; }
		if (down)  { enemyMovement.y += speed; }
		if (right) { enemyMovement.x += speed; }
	}

	enemy.move(enemyMovement);
}

void Enemy::updateAnimation(bool continuous) {
	//Animation
	animation.updateAnimation(continuous, moving);
	enemy.setTextureRect(animation.uvRect);
}

bool Enemy::isOnScreen() {
	if ((getX() >= 0 && getX() <= SCREEN_WIDTH) || (getY() >= ENEMY_ORIGINAL_POSITION_Y && getY() <= SCREEN_HEIGHT)) {
		return true;
	}
	return false;
}

int Enemy::getX() {
	return enemy.getPosition().x;
}

int Enemy::getY() {
	return enemy.getPosition().y;
}

sf::FloatRect Enemy::getGlobalBounds() {
	return enemy.getGlobalBounds();
}
