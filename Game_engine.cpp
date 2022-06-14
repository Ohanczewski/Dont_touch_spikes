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
	this->endScreen = false;
	playerTexture.loadFromFile("birbTexture.png");
	player.setTexture(playerTexture);
	playerAnim = Animation(playerTexture, sf::Vector2u(2, 1), 0.2f);
	pointFont.loadFromFile("cheri.ttf");
	pointDisp.setFont(pointFont);
	pointDisp.setCharacterSize(160);
	pointDisp.setFillColor(sf::Color(0, 0, 0, 30));
	pointDisp.setPosition(sf::Vector2f(800 / 2 - pointDisp.getGlobalBounds().width / 2, 900 / 2 - pointDisp.getGlobalBounds().height / 2 - 100));
	pointDisp.setLetterSpacing(2.f);

	endText.setFont(pointFont);
	endText.setCharacterSize(96);
	endText.setFillColor(sf::Color(0, 0, 0));
	endText.setPosition(sf::Vector2f(800 / 2 - endText.getGlobalBounds().width / 2, 900 / 2 - endText.getGlobalBounds().height / 2 - 200));
	endText.setLetterSpacing(2.f);
	endText.setString(L"Przegrana!");

	bonusTexture.loadFromFile("candyTexture.png");
	bonusSeen = false;
	bonus.setTexture(bonusTexture);
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

	for (int i = 0; i < 4; i++)
	{
		rightSpikes.emplace_back(new Obstacle(sf::Vector2f(800, (rand()%18)*50), 'r'));
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
		if (this->event.type == sf::Event::KeyPressed)
		{
			if (this->event.key.code == sf::Keyboard::Escape) 
			{
				this->window->close();
			}
		}
	}
}

void Game_engine::updateWindow()
{
	this->pollEvents();

	if (!endScreen) 
	{
		this->player.step(timer.restart());
		if (this->player.checkCollision()) 
		{
			if (player.points % 2 == 0) 
			{
				
				for (int i = 0; i < 5; i++)
				{
					leftSpikes.clear();
					rightSpikes.emplace_back(new Obstacle(sf::Vector2f(800, (rand() % 16) * 50 + 50), 'r'));
				}
			}
			if (player.points % 2 == 1)
			{
				for (int i = 0; i < 5; i++)
				{
					rightSpikes.clear();
					leftSpikes.emplace_back(new Obstacle(sf::Vector2f(0, (rand() % 16) * 50 + 50), 'l'));
				}
			}
			if (player.points % 10 == 0) {
				bgColor = sf::Color(180 + rand() % 75, 180 + rand() % 75, 180 + rand() % 75);
			}
		}

		endScreen = this->player.checkHit();
		if (!endScreen)
		{
			if (player.points % 2 == 0 && player.getGlobalBounds().left + player.getGlobalBounds().width > 700)
			{
				endScreen = this->player.checkHit(rightSpikes);
			}
			if (player.points % 2 == 1 && player.getGlobalBounds().left < 100)
			{
				endScreen = this->player.checkHit(leftSpikes);
			}
		}
		
	}
	//Update player animation
	playerAnim.update(0, animClock.restart().asSeconds());
	player.setTextureRect(playerAnim.uvRect);

	//Update bonuses
	if (bonusTime.getElapsedTime().asSeconds() > 6)
	{
		bonus.setPosition(100 + rand() % 600, 100 + rand() % 700);
		bonusSeen = true;
		bonusTime.restart();
	}
	if (player.getGlobalBounds().intersects(bonus.getGlobalBounds()) && bonusSeen)
	{
		player.points += 4;
		bonusSeen = false;
	}
	

	//Update points
	pointDisp.setString(std::to_string(player.points));
	pointDisp.setPosition(sf::Vector2f(800 / 2 - pointDisp.getGlobalBounds().width / 2, 900 / 2 - pointDisp.getGlobalBounds().height / 2 - 100));
	endText.setPosition(sf::Vector2f(800 / 2 - endText.getGlobalBounds().width / 2, 900 / 2 - endText.getGlobalBounds().height / 2 - 200));

}

void Game_engine::renderWindow()
{
	this->window->clear(bgColor);

	if (!endScreen) 
	{
		//Rednering sth
		this->window->draw(pointDisp);
		this->player.renderPlayer(*window);
		if (bonusSeen) {
			this->window->draw(bonus);
		}
		this->renderStaticObstacles();
		this->renderSpikes();
	}
	else
	{
		this->window->draw(endText);
		pointDisp.setPosition(sf::Vector2f(800 / 2 - pointDisp.getGlobalBounds().width / 2, 900 / 2 - pointDisp.getGlobalBounds().height / 2));
		pointDisp.setFillColor(sf::Color(0, 0, 0));
		this->window->draw(pointDisp);
	}
	

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

void Game_engine::renderSpikes()
{
	for (auto& i : leftSpikes)
	{
		i->renderObstacle(*window);
	}
	for (auto& i : rightSpikes)
	{
		i->renderObstacle(*window);
	}
}

const bool Game_engine::running() const
{
	return this->window->isOpen();
}


