#pragma once

#include <iostream>

class Ball
{
protected:
	sf::CircleShape circle;
	sf::FloatRect collider;
	float radius = 0;
	float positionX = 0;
	float positionY = 0;
	float velocityX = 0;
	float velocityY = 0;

public:
	Ball(float radius, float posX, float posY, float velocityX, float velocityY, sf::Color color);
	~Ball();

	void move();
	void checkCollision(int windowWidth, int windowHeight);

	// Getters and setters
	sf::CircleShape getCircle() const { return circle; }

	void setVelocity(float newVelocityX, float newVelocityY) { 
		velocityX = newVelocityX, velocityY = newVelocityY
	;}
};

Ball::Ball(float radius, float posX, float posY, float velocityX, float velocityY, sf::Color color)
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

void Ball::checkCollision(int windowWidth, int windowHeight)
{
	// Left collision
	if (positionX <= 0)
	{
		positionX = radius;
		velocityX = -velocityX;
	}
	// Right collision
	if (positionX + radius*2 >= windowWidth)
	{
		positionX = windowWidth - radius*2;
		velocityX = -velocityX;
	}
	// Up collision
	if (positionY <= 0)
	{
		positionY = radius;
		velocityY = -velocityY;
	}
	// Down collision
	if (positionY + radius * 2 >= windowHeight)
	{
		positionY = windowHeight - radius*2;
		velocityY = -velocityY;
	}
}