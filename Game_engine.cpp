#include "Game_engine.h"

//Constructor 
Game_engine::Game_engine()
{
	this->initVariables();
	this->initObstacles();
	this->initWindow();
}

//Destructor
Game_engine::~Game_engine()
{
	delete this->window;
}

//private Functions
void Game_engine::initWindow()
{
	this->videomode.width = 800;
	this->videomode.height = 900;
	this->window = new sf::RenderWindow(this->videomode, "Don't touch the spikes!", sf::Style::Close | sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings::ContextSettings(0, 0, 15, 2, 0));
	this->window->setFramerateLimit(60);
}

void Game_engine::initVariables()
{
	this->end = false;
	playerTexture.loadFromFile("birbTexture.png");
	player.setTexture(playerTexture);
	playerAnim = Animation(playerTexture, sf::Vector2u(2, 1), 0.2f);
	pointFont.loadFromFile("cheri.ttf");
	pointDisp.setFont(pointFont);
	pointDisp.setCharacterSize(160);
	pointDisp.setFillColor(sf::Color(0, 0, 0, 30));
	pointDisp.setPosition(sf::Vector2f(800 / 2 - pointDisp.getGlobalBounds().width / 2, 900 / 2 - pointDisp.getGlobalBounds().height / 2 - 100));
	pointDisp.setLetterSpacing(2.f);
}

void Game_engine::initObstacles()
{
	topBar.setSize(sf::Vector2f(800.f, 25.f));
	topBar.setFillColor(obstacleColor);
	topBar.setPosition(0.f, 0.f);
	bottomBar.setSize(sf::Vector2f(800.f, 50.f));
	bottomBar.setFillColor(obstacleColor);
	bottomBar.setPosition(0.f, 850.f);

	for (int i = 0; i < 14; i++) 
	{
		staticObstaclesTop.emplace_back(Obstacle(sf::Vector2f(20 + i * 55, 25), false));
		staticObstaclesBottom.emplace_back(Obstacle(sf::Vector2f(20 + i * 55, 850), true));
	}
	
}

//public Functions
void Game_engine::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game_engine::updateWindow()
{
	this->pollEvents();
	this->player.step(timer.restart());
	this->player.checkCollision(*window);
	//Update player animation
	playerAnim.update(0, animClock.restart().asSeconds());
	player.setTextureRect(playerAnim.uvRect);

	//Update points
	pointDisp.setString(std::to_string(player.points));
	pointDisp.setPosition(sf::Vector2f(800 / 2 - pointDisp.getGlobalBounds().width / 2, 900 / 2 - pointDisp.getGlobalBounds().height / 2 - 100));

}

void Game_engine::renderWindow()
{
	this->window->clear(bgColor);

	//Rednering sth
	this->window->draw(pointDisp);
	this->player.renderPlayer(*window);
	this->renderStaticObstacles();

	this->window->display();
}

void Game_engine::renderStaticObstacles()
{
	window->draw(topBar);
	window->draw(bottomBar);
	for (auto& i : staticObstaclesTop)
	{
		i.renderObstacle(*window);
	}
	for (auto& i : staticObstaclesBottom)
	{
		i.renderObstacle(*window);
	}
}

const bool Game_engine::running() const
{
	return this->window->isOpen();
}


