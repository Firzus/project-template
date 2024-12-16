#pragma once
#include <iostream>
#include "Ball.h"

class Game
{
private:
	bool isRunning;
	int score;
	int lives;

	Ball ball = Ball(20, 50, 50, -3, -3, sf::Color::Blue);
	int windowWidth;
	int windowHeight;

public:
	Game();
	~Game();
	void Start();
	void Stop();
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void HandleEvents(sf::RenderWindow& window);

	// Getters
	bool IsRunning() const { return isRunning; }
};

Game::Game()
{
	isRunning = false;
	score = 0;
	lives = 3;
}

Game::~Game()
{
}

void Game::Start()
{
	isRunning = true;
}

void Game::Stop()
{
	isRunning = false;
}

void Game::Update(float deltaTime)
{
	//std::cout << "Update - Delta Time: " << deltaTime << " seconds\n";
	ball.checkCollision(windowWidth, windowHeight);
}

void Game::FixedUpdate(float deltaTime)
{
	//std::cout << "FixedUpdate - Delta Time: " << deltaTime << " seconds\n";
	ball.move();
}

void Game::Draw(sf::RenderWindow& window)
{
	//window.draw(shape);
	window.draw(ball.getCircle());
}

void Game::HandleEvents(sf::RenderWindow& window)
{
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Stop();
			}
		}
	}
}
