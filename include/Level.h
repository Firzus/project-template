#pragma once

#include <iostream>

#include "Brick.h"

class Level
{
private:
	std::vector<Brick> bricks;

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
	bool IsCompleted() const { return bricks.empty(); }
};