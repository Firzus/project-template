#pragma once

#include "Entity.h"

class Paddle : public Entity
{
protected:
	sf::RectangleShape rectangle;

public:
	Paddle(int width, int height, float posX, float posY, float speed, sf::Color color);
	~Paddle();

	void MoveLeft();
	void MoveRight(int windowWidth);
	void OnCollision(Entity* other) override;

	// Getters and setters
	sf::RectangleShape getRectangle() const { return rectangle; }
	void SetSpeed(float newSpeed) { speed = newSpeed; }
};

Paddle::Paddle(int width, int height, float posX, float posY, float speed, sf::Color color)
{
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	this->speed = speed;
	this->color = color;

	rectangle = sf::RectangleShape(sf::Vector2f((float)width, (float)height));
	rectangle.setPosition(posX, posY);
	rectangle.setFillColor(color);
}

Paddle::~Paddle()
{

}

void Paddle::MoveLeft()
{
	if (posX >= 0)
	{
		rectangle.move(-speed, 0);
		posX = rectangle.getPosition().x;
		posY = rectangle.getPosition().y;
	}
}

void Paddle::MoveRight(int windowWidth)
{
	if (posX <= windowWidth - width)
	{
		rectangle.move(speed, 0);
		posX = rectangle.getPosition().x;
		posY = rectangle.getPosition().y;
	}
}

void Paddle::OnCollision(Entity* other)
{
	// Do nothing
}
