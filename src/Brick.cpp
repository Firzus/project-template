#include "Brick.h"

#include "Ball.h"

Brick::Brick(int width, int height, float posX, float posY, sf::Color color)
{
	this->width = width;
	this->height = height;
	this->color = color;
	this->posX = posX;
	this->posY = posY;

	destroyed= false;

	rectangle = sf::RectangleShape(sf::Vector2f((float)width, (float)height));
	rectangle.setPosition(posX, posY);
	rectangle.setFillColor(color);
}

Brick::~Brick() {}

void Brick::OnCollision(Entity* other)
{
	// Collision width ball
	Ball* ball = dynamic_cast<Ball*>(other);
	if (ball)
	{
		if (rectangle.getGlobalBounds().intersects(ball->getCircle().getGlobalBounds())) {
			std::cout << "Brick collided with ball" << std::endl;
			destroyed = true;
		}
	}
}