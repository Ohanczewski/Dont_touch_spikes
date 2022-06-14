#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Obstacle : public sf::ConvexShape
{
private:

public:
	//Constructor
	Obstacle();
	Obstacle(sf::Vector2f pos, bool isRotated);
	Obstacle(sf::Vector2f pos, char side);

	//Destructor
	~Obstacle();

	//Functions
	void renderObstacle(sf::RenderTarget & target);
	
};

