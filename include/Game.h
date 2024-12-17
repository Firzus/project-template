#pragma once
#include <iostream>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

#include <SFML/Graphics.hpp>
#include "FontManager.h"

class Game
{
private:
	FontManager fontManager;
	bool isRunning;
	int score;
	int lives;

	Ball ball = Ball(20, 50, 50, -3, -3, sf::Color::Blue);
	Paddle paddle = Paddle(100, 30, 400, 550, 5, sf::Color::Blue);
	int windowWidth;
	int windowHeight;

	sf::Text scoreText;

	bool isLeftArrowPressed = false;
	bool isRightArrowPressed = false;

public:
	Game();
	~Game();
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void HandleEvents(sf::RenderWindow& window);

	// Getters
	bool IsRunning() const { return isRunning; }
};

Game::Game()
{
	fontManager.LoadFont("resources/fonts/Roboto.ttf");

	isRunning = false;
	score = 0;
	lives = 3;

	isRunning = true;

	scoreText.setFont(fontManager.GetFont());
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(10, 10);
	scoreText.setString("Score : " + std::to_string(score));
}

Game::~Game()
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
	
	// Inputs
	if (isLeftArrowPressed)
	{
		paddle.moveLeft();
	}
	if (isRightArrowPressed)
	{
		paddle.moveRight(windowWidth);
	}
}

void Game::Draw(sf::RenderWindow& window)
{
	window.draw(ball.getCircle());
	window.draw(paddle.getRectangle());
	window.draw(scoreText);
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
				window.close();
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				isLeftArrowPressed = true;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				isRightArrowPressed = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				isLeftArrowPressed = false;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				isRightArrowPressed = false;
			}
		}
	}
}
