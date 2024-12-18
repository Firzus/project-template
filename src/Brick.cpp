#include "Brick.h"

#include "Ball.h"

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
	hit = true;
}