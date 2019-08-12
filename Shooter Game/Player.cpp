#include "Player.h"

#include "MoreInfo.h"


Player::Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed) 
	: animation{ texture, imageCount, switchTime } {

	this->speed = speed;

	player.setTexture(*texture);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
}

void Player::renderTo(sf::RenderWindow& window) {
	window.draw(player);
}

void Player::setPosition(sf::Vector2<float> newPos) {
	player.setPosition(newPos);
}

void Player::updateAnimation(bool continuous) {
	//Animation
	animation.updateAnimation(continuous, moving);
	player.setTextureRect(animation.uvRect);
}

void Player::updateMovement() {
	//Movement/Animation
	sf::Vector2<float> playerMovement(0.f, 0.f);
	using Key = sf::Keyboard::Key;
	auto keyDown = [](sf::Keyboard::Key k) { return sf::Keyboard::isKeyPressed(k); };

	if (keyDown(Key::W)) { playerMovement.y -= speed; setDirection(Animation::Direction::up);    moving = true; }
	if (keyDown(Key::A)) { playerMovement.x -= speed; setDirection(Animation::Direction::left);  moving = true; }
	if (keyDown(Key::S)) { playerMovement.y += speed; setDirection(Animation::Direction::down);  moving = true; }
	if (keyDown(Key::D)) { playerMovement.x += speed; setDirection(Animation::Direction::right); moving = true; }
	else { moving = false; }

	player.move(playerMovement);
}

void Player::setDirection(const Animation::Direction& direction) {
	animation.direction = direction;
}

int Player::getX() {
	return player.getPosition().x;
}

int Player::getY() {
	return player.getPosition().y;
}

void Player::updateBorderBounds() {
	//Entity cannot go through the borders of the screen
	if (getX() <= SCREEN_WIDTH * 0 + 55) { setPosition(sf::Vector2<float>(getX() + PLAYER_SPEED, getY())); } //Left Side
	if (getX() >= SCREEN_WIDTH)		     { setPosition(sf::Vector2<float>(getX() - PLAYER_SPEED, getY())); } //Right Side
}

sf::FloatRect Player::getGlobalBounds() const {
	return player.getGlobalBounds();
}

bool Player::enemyCollision(Enemy& enemy) {
	if (getGlobalBounds().intersects(enemy.getGlobalBounds())) {
		return true;
	}
	return false;
}
