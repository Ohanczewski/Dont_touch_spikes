#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Obstacle.h"
#include <iostream>

class Player : public sf::Sprite
{
private: 
	//Variables
	float speedX, speedY;
	float elapsedTime;
	float gravity;
	bool spacePressed;

	//Functions
	void initVariables();
	void initShape();
public: 
	int points;
	//Functions
	Player();
	~Player();

	void renderPlayer(sf::RenderTarget& target);
	void step(sf::Time time);
	bool checkCollision();
	bool checkHit();
	bool checkHit(std::vector<Obstacle*> spikes);
};

