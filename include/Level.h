#pragma once

#include <map>

class Level
{
private:
	std::map<std::pair<int, int>, bool> grid;

public:
	Level();
	Level(std::map<std::pair<int, int>, bool> grid);
	~Level();
	void CheckBricksCollision();

	// Getters
	std::map<std::pair<int, int>, bool> GetGrid() const { return grid; }
};