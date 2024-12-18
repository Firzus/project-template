#include "Level.h"

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

Level::~Level() {}

void Level::CheckBricksCollision()
{
	// Remove bricks that were hit
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks[i].WasHit())
		{
			bricks.erase(bricks.begin() + i);
		}
	}
}