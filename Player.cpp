#include "Player.h"

//private Functions
void Player::initVariables()
{
	this->speedX = 8.f;
	this->speedY = -12.f;
	this->gravity = 14.f;
	this->points = 0;
	this->spacePressed = false;
}

void Player::initShape()
{
	this->setPosition(sf::Vector2f(375.f, 400.f));
}

//Constructor
Player::Player()
{
	this->initVariables();
	this->initShape();
}

//Destructor
Player::~Player()
{

}

void Player::step(sf::Time time)
{
	this->elapsedTime = time.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!spacePressed) {
			speedY = -8.5f;
			spacePressed = true;
		}
	}
	else {
		spacePressed = false;

	}

	speedY += gravity * elapsedTime;

	this->move(speedX, speedY);
}

void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Player::checkCollision(sf::RenderWindow &window)
{
	if (this->getGlobalBounds().left < 0.f)
	{
		speedX = -speedX;
		this->scale(-1, 1);
		points++;
	}

	if (this->getGlobalBounds().left + this->getGlobalBounds().width > 800.f)
	{
		speedX = -speedX;
		this->scale(-1, 1);
		points++;
	}


	if (this->getGlobalBounds().top < 67.75f || this->getGlobalBounds().top + this->getGlobalBounds().height > 807.25f)
	{
		window.close();
	}
}





