#include "Obstacle.h"

//Constructor
Obstacle::Obstacle()
{

}

Obstacle::Obstacle(sf::Vector2f pos, bool isRotated)
{
	this->setPointCount(3);
	this->setFillColor(sf::Color(100, 100, 100));
	
	if (!isRotated)
	{
		this->setPoint(0, sf::Vector2f(0, 0));
		this->setPoint(1, sf::Vector2f(50, 0));
		this->setPoint(2, sf::Vector2f(25, 25 * 1.71f));
	} else
	{
		this->setPoint(0, sf::Vector2f(0, 0));
		this->setPoint(1, sf::Vector2f(50, 0));
		this->setPoint(2, sf::Vector2f(25, -25 * 1.71f));
	}
	this->setPosition(pos);
}

Obstacle::Obstacle(sf::Vector2f pos, char side)
{
	this->setPointCount(3);
	this->setFillColor(sf::Color(100, 100, 100));
	if (side == 'l')
	{
		this->setPoint(0, sf::Vector2f(0, 0));
		this->setPoint(1, sf::Vector2f(25 * 1.71, 25));
		this->setPoint(2, sf::Vector2f(0, 50));
	}
	else if (side == 'r')
	{
		this->setPoint(0, sf::Vector2f(0, 0));
		this->setPoint(1, sf::Vector2f(25 * -1.71, 25));
		this->setPoint(2, sf::Vector2f(0, 50));
	}

	this->setPosition(pos);

}

//Destructor
Obstacle::~Obstacle()
{

}

void Obstacle::renderObstacle(sf::RenderTarget& target)
{
	target.draw(*this);
}

