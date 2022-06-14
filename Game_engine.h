#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Player.h"
#include "Obstacle.h"
#include "Animation.h"

class Game_engine
{
private: 
	//Variables
	sf::RenderWindow *window;
	sf::VideoMode videomode;
	sf::Event event;

	//Player in game engine
	Player player;
	sf::Clock animClock;
	Animation playerAnim;
	sf::Texture playerTexture;
	sf::Clock timer;

	//Points & counting
	sf::Font pointFont;
	sf::Text pointDisp;

	//Bonuses
	sf::Clock bonusTime;
	sf::Texture bonusTexture;
	sf::Sprite bonus;
	bool bonusSeen;

	//Obstacles
	sf::RectangleShape topBar, bottomBar;
	std::vector<Obstacle> staticObstaclesTop;
	std::vector<Obstacle> staticObstaclesBottom;

	std::vector<Obstacle*> leftSpikes;
	std::vector<Obstacle*> rightSpikes;

	//Colors
	sf::Color bgColor = sf::Color(247, 233, 195);
	sf::Color obstacleColor = sf::Color(100, 100, 100);

	bool end;

	//End screen
	bool endScreen;
	sf::Text endText;

	//Functions
	void initWindow();
	void initVariables();
	void initObstacles();

public: 
	//Constructor 
	Game_engine();
	//Destructor
	~Game_engine();

	//Functions
	const bool running() const;
	void pollEvents();
	void renderWindow();
	void renderStaticObstacles();
	void renderSpikes();
	void updateWindow();

};

