#pragma once

#include <iostream>

class Paddle
{
protected:
	sf::RectangleShape rectangle;
	sf::FloatRect collider;
	float width = 0;
	float height = 0;
	float positionX = 0;
	float positionY = 0;
	float speed = 0;

public:
	Paddle(float width, float height, float posX, float posY, float speed, sf::Color color);
	~Paddle();

	void moveLeft();
	void moveRight(int windowWidth);

	// Getters and setters
	sf::RectangleShape getRectangle() const { return rectangle; }

	void setSpeed(float newSpeed) { speed = newSpeed; }
};

Paddle::Paddle(float width, float height, float posX, float posY, float speed, sf::Color color)
{
	this->width = width;
	this->height = height;
	positionX = posX - (width/2);
	positionY = posY - (height/2);
	this->speed = speed;

	rectangle = sf::RectangleShape(sf::Vector2f(width, height));
	rectangle.setPosition(positionX, positionY);
	rectangle.setFillColor(color);

	collider = rectangle.getGlobalBounds();
}

Paddle::~Paddle()
{

}

inline void Paddle::moveLeft()
{
	if (positionX >= 0)
	{
		rectangle.move(-speed, 0);
		positionX = rectangle.getPosition().x;
		positionY = rectangle.getPosition().y;
	}
}

inline void Paddle::moveRight(int windowWidth)
{
	if (positionX <= windowWidth - width)
	{
		rectangle.move(speed, 0);
		positionX = rectangle.getPosition().x;
		positionY = rectangle.getPosition().y;
	}
}
