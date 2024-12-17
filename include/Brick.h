#pragma once

#include "Entity.h"

class Brick : public Entity
{
protected:
	sf::RectangleShape rectangle;

public:
	Brick(int width, int height, float posX, float posY, sf::Color color);
	~Brick();

	void OnCollision(Entity* other) override;

	// Getters and setters
	sf::RectangleShape getRectangle() const { return rectangle; }
};

Brick::Brick(int width, int height, float posX, float posY, sf::Color color)
{
	this->width = width;
	this->height = height;
	this->color = color;
	this->posX = posX;
	this->posY = posY;

	rectangle = sf::RectangleShape(sf::Vector2f((float)width, (float)height));
	rectangle.setPosition(posX, posY);
	rectangle.setFillColor(color);
}

Brick::~Brick() {}

void Brick::OnCollision(Entity* other)
{
	// delete si collision avec la balle
}
