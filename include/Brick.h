#pragma once

#include <iostream>

class Brick
{
protected:
	sf::RectangleShape rectangle;
	float width = 0;
	float height = 0;
	float positionX = 0;
	float positionY = 0;

public:
	Brick(float width, float height, float posX, float posY, sf::Color color);
	~Brick();

	// Getters and setters
	sf::RectangleShape getRectangle() const { return rectangle; }
};

Brick::Brick(float width, float height, float posX, float posY, sf::Color color)
{
	this->width = width;
	this->height = height;
	positionX = posX;
	positionY = posY;

	rectangle = sf::RectangleShape(sf::Vector2f(width, height));
	rectangle.setPosition(positionX, positionY);
	rectangle.setFillColor(color);
}

Brick::~Brick()
{

}