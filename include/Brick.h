#pragma once

#include "Entity.h"

class Brick : public Entity
{
private:
	sf::RectangleShape rectangle;

public:
	Brick(int width, int height, float posX, float posY, sf::Color color);
	~Brick();

	void OnCollision(Entity* other) override;

	// Getters and setters
	sf::RectangleShape getRectangle() const { return rectangle; }
};
