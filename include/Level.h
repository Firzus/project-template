#pragma once

#include <iostream>

#include "Brick.h"

class Level
{
private:
	std::vector<Brick> bricks;

	bool isCompleted = false;
	const int brickWidth = 100;
	const int brickHeight = 40;
	const int rows = 2;
	const int cols = 4;

public:
	Level() {};
	Level(std::map<int, int> placement);
	Level(const Level& other);
	Level& operator=(const Level& other);
	~Level();

	// Getters and setters
	std::vector<Brick> GetBricks() const { return bricks; }
	void SetBricks(std::vector<Brick> newBricks) { bricks = newBricks; }
	bool IsCompleted() const { return isCompleted; }
};

Level::Level(std::map<int, int> placement)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int x = j * brickWidth;
			int y = i * brickHeight;
			bricks.push_back(Brick(brickWidth, brickHeight, x, y, sf::Color::Red));
		}
	}
}

Level::Level(const Level& other)
{
	bricks = other.bricks;
}

Level& Level::operator=(const Level& other)
{
	if (this != &other)
	{
		bricks = other.bricks;
	}
	return *this;
}

Level::~Level()
{

}