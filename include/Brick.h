#pragma once

#include <iostream>

class Brick
{
protected:
	sf::RectangleShape rectangle;
	sf::FloatRect collider;
	float width = 0;
	float height = 0;
	float positionX = 0;
	float positionY = 0;

public:
	Brick(float width, float height, float posX, float posY, sf::Color color);
	~Brick();

	// Getters and setters
	sf::RectangleShape GetRectangle() const { return rectangle; }
};

Brick::Brick(float width, float height, float posX, float posY, sf::Color color)
{
	this->width = width;
	this->height = height;
	positionX = posX - (width / 2);
	positionY = posY - (height / 2);

	rectangle = sf::RectangleShape(sf::Vector2f(width, height));
	rectangle.setPosition(positionX, positionY);
	rectangle.setFillColor(color);

	collider = rectangle.getGlobalBounds();
}

Brick::~Brick()
{
}
