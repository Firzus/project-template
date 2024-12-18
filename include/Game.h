#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "FontManager.h"
#include "Level.h"
#include "Ball.h"
#include "Paddle.h"
#include "Window.h"

class Game
{
private:
	FontManager fontManager;
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

	// Getters
	bool IsRunning() const { return isRunning; }
};