#include "Level.h"

Level::Level() {}

Level::Level(std::map<std::pair<int, int>, bool> grid) : grid(grid) {}

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