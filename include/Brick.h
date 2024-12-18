#pragma once

#include "Entity.h"

class Brick : public Entity
{
private:
	sf::RectangleShape rectangle;
	bool destroyed;

public:
	Brick(int width, int height, float posX, float posY, sf::Color color);
	~Brick();

	void OnCollision(Entity* other) override;

	// Getters and setters
	sf::RectangleShape GetRectangle() const { return rectangle; }
	bool IsDestroyed() const { return destroyed; }
};
