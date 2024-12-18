#include "Level.h"

Level::Level() {}

Level::Level(std::map<std::pair<int, int>, bool> grid) : grid(grid) {}

Level::~Level() {}