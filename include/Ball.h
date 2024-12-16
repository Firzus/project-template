#pragma once

#include <iostream>

class Ball
{
protected:
	sf::CircleShape circle;
	sf::FloatRect collider;
	float radius = 0;
	int positionX = 0;
	int positionY = 0;
	int velocityX = 0;
	int velocityY = 0;

public:
	Ball(float radius, int posX, int posY, int velocityX, int velocityY, sf::Color color);
	~Ball();

	void move();
	void checkCollision(int width, int height);

	// Getters and setters
	sf::CircleShape getCircle() const { return circle; }

	void setVelocity(float newVelocityX, float newVelocityY) { 
		velocityX = newVelocityX, velocityY = newVelocityY
	;}
};

Ball::Ball(float radius, int posX, int posY, int velocityX, int velocityY, sf::Color color)
{
	this->radius = radius;
	positionX = posX;
	positionY = posY;
	this->velocityX = velocityX;
	this->velocityY = velocityY;

	circle = sf::CircleShape(this->radius);
	circle.setPosition(positionX, positionY);
	circle.setFillColor(color);

	collider = circle.getGlobalBounds();
}

Ball::~Ball()
{

}

void Ball::move()
{
	circle.move(velocityX, velocityY);
	positionX = circle.getPosition().x;
	positionY = circle.getPosition().y;
}

void Ball::checkCollision(int width, int height)
{
	// Left and right screen collisions
	if (positionX <= 0)
	{
		positionX = radius;
		velocityX = -velocityX;
	}
	if (positionX + radius*2 >= width)
	{
		positionX = width - radius*2;
		velocityX = -velocityX;
	}

	// Up and down screen collisions
	if (positionY <= 0)
	{
		positionY = radius;
		velocityY = -velocityY;
	}
	if (positionY + radius * 2 >= height)
	{
		positionY = height - radius*2;
		velocityY = -velocityY;
	}
}