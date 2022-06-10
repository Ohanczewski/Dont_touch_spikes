#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Obstacle : sf::ConvexShape
{
private:

public:
	//Constructor
	Obstacle();
	Obstacle(sf::Vector2f pos, bool isRotated);

	//Destructor
	~Obstacle();

	//Functions
	void renderObstacle(sf::RenderTarget & target);
	
};

