#pragma once

#include <iostream>
#include "Paddle.h"
#include "Brick.h"

class Ball
{
protected:
	sf::CircleShape circle;
	float radius = 0;
	float positionX = 0;
	float positionY = 0;
	float velocityX = 0;
	float velocityY = 0;

public:
	Ball(float radius, float posX, float posY, float velocityX, float velocityY, sf::Color color);
	~Ball();

	void move();
	void checkCollision(int windowWidth, int windowHeight, Paddle paddle, std::vector<Brick> bricks);
	std::string checkSideOfCollision(sf::RectangleShape rect);

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

void Ball::checkCollision(int windowWidth, int windowHeight, Paddle paddle, std::vector<Brick> bricks)
{
	//Paddle collision
	if (circle.getGlobalBounds().intersects(paddle.getRectangle().getGlobalBounds()))
	{
		std::string side = checkSideOfCollision(paddle.getRectangle());

		if (side == "left")
		{
			circle.setPosition(paddle.getRectangle().getPosition().x - (radius * 2), circle.getPosition().y);
			velocityX = -velocityX;
		}
		else if (side == "right")
		{
			circle.setPosition(paddle.getRectangle().getPosition().x + paddle.getRectangle().getSize().x, circle.getPosition().y);
			velocityX = -velocityX;
		}
		else if (side == "top")
		{
			circle.setPosition(circle.getPosition().x, paddle.getRectangle().getPosition().y - (radius * 2));
			velocityY = -velocityY;
		}
		else if (side == "bottom")
		{
			circle.setPosition(circle.getPosition().x, paddle.getRectangle().getPosition().y + paddle.getRectangle().getSize().y);
			velocityY = -velocityY;
		}
	}

	
	for (int i = 0; i < bricks.size(); i++)
	{
		if (circle.getGlobalBounds().intersects(bricks[i].getRectangle().getGlobalBounds()))
		{
			std::string side = checkSideOfCollision(bricks[i].getRectangle());

			if (side == "left")
			{
				circle.setPosition(bricks[i].getRectangle().getPosition().x - (radius * 2), circle.getPosition().y);
				velocityX = -velocityX;
			}
			else if (side == "right")
			{
				circle.setPosition(bricks[i].getRectangle().getPosition().x + bricks[i].getRectangle().getSize().x, circle.getPosition().y);
				velocityX = -velocityX;
			}
			else if (side == "top")
			{
				circle.setPosition(circle.getPosition().x, bricks[i].getRectangle().getPosition().y - (radius * 2));
				velocityY = -velocityY;
			}
			else if (side == "bottom")
			{
				circle.setPosition(circle.getPosition().x, bricks[i].getRectangle().getPosition().y + bricks[i].getRectangle().getSize().y);
				velocityY = -velocityY;
			}
		}
	}
	

	// Screen collisions
	// Left collision
	if (positionX <= 0)
	{
		circle.setPosition(0, circle.getPosition().y);
		velocityX = -velocityX;
	}
	// Right collision
	if (positionX + (radius * 2) >= windowWidth)
	{
		circle.setPosition(windowWidth - (radius * 2), circle.getPosition().y);
		velocityX = -velocityX;
	}
	// Up collision
	if (positionY <= 0)
	{
		circle.setPosition(circle.getPosition().x, 0);
		velocityY = -velocityY;
	}
	// Down collision
	if (positionY + (radius * 2) >= windowHeight)
	{
		circle.setPosition(circle.getPosition().x, windowHeight - (radius * 2));
		velocityY = -velocityY;
	}
}

inline std::string Ball::checkSideOfCollision(sf::RectangleShape rect)
{
	// Calculates which side was the brick touched
	float deltaLeft = std::abs(rect.getPosition().x - positionX - (radius * 2));
	float deltaRight = std::abs(rect.getPosition().x + rect.getSize().x - positionX);
	float deltaTop = std::abs((rect.getPosition().y - positionY) - (radius * 2));
	float deltaBottom = std::abs(rect.getPosition().y + rect.getSize().y - positionY);

	if (deltaLeft < deltaTop && deltaLeft < deltaRight && deltaLeft < deltaBottom) {
		// Left collision
		return "left";
	}
	else if (deltaRight < deltaTop && deltaRight < deltaLeft && deltaRight < deltaBottom) {
		// Right collision
		return "right";
	}
	else if (deltaTop < deltaLeft && deltaTop < deltaRight && deltaTop < deltaBottom) {
		// Up collision
		return "top";
	}
	else {
		// Down collision
		return "bottom";
	}
}
