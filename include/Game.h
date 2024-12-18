#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "FontManager.h"
#include "Level.h"
#include "Ball.h"
#include "Paddle.h"
#include "Window.h"
#include "Brick.h"

class Game
{
private:
	FontManager fontManager;
	std::vector<Brick> bricks;
	std::map<int, Level> levels;
	int currentLevel;
	bool isRunning;
	int score;
	int lives;

	Ball* ball = nullptr;
	Paddle* paddle = nullptr;

	sf::Text scoreText;

	bool isLeftArrowPressed = false;
	bool isRightArrowPressed = false;

public:
	Game();
	~Game();

	virtual void Update(Window* window, float deltaTime);
	virtual void FixedUpdate(Window* window);
	void Draw(Window* window);
	void HandleEvents(Window* window);
	void BuildLevel(int levelNumber);

	// Getters
	bool IsRunning() const { return isRunning; }
	int GetScore() const { return score; }
	int GetLives() const { return lives; }
};