#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Animation{
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float switchTime;
	float totalTime;

public:
	Animation();
	Animation(sf::Texture& texture, sf::Vector2u imageCount, float switchTime_);
	~Animation();

	sf::IntRect uvRect;
	void update(int row, float dt);
};

