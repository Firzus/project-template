#include "Ball.h"

#include "Paddle.h"
#include "Brick.h"
#include "Window.h"

Ball::Ball(float radius, float posX, float posY, float velocityX, float velocityY, sf::Color color)
{
	this->radius = radius;
	this->posX = posX;
	this->posY = posY;
	this->velocityX = velocityX;
	this->velocityY = velocityY;

	circle = sf::CircleShape(this->radius);
	circle.setPosition(posX, posY);
	circle.setFillColor(color);
}

Ball::~Ball() {}

void Ball::Move()
{
	circle.move(velocityX, velocityY);
}

std::string Ball::checkSideOfCollision(sf::RectangleShape rect)
{
	// Calculates which side was the brick touched
	float deltaLeft = std::abs(rect.getPosition().x - circle.getPosition().x - (radius * 2));
	float deltaRight = std::abs(rect.getPosition().x + rect.getSize().x - circle.getPosition().x);
	float deltaTop = std::abs((rect.getPosition().y - circle.getPosition().y) - (radius * 2));
	float deltaBottom = std::abs(rect.getPosition().y + rect.getSize().y - circle.getPosition().y);

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

void Ball::OnCollision(Entity* other)
{
	// Paddle collision
	Paddle* paddle = dynamic_cast<Paddle*>(other);
	if (paddle) {
		if (circle.getGlobalBounds().intersects(paddle->getRectangle().getGlobalBounds()))
		{
			std::string side = checkSideOfCollision(paddle->getRectangle());

			if (side == "left")
			{
				circle.setPosition(paddle->getRectangle().getPosition().x - (radius * 2), circle.getPosition().y);
				velocityX = -velocityX;
			}
			else if (side == "right")
			{
				circle.setPosition(paddle->getRectangle().getPosition().x + paddle->getRectangle().getSize().x, circle.getPosition().y);
				velocityX = -velocityX;
			}
			else if (side == "top")
			{
				circle.setPosition(circle.getPosition().x, paddle->getRectangle().getPosition().y - (radius * 2));
				velocityY = -velocityY;
			}
			else if (side == "bottom")
			{
				circle.setPosition(circle.getPosition().x, paddle->getRectangle().getPosition().y + paddle->getRectangle().getSize().y);
				velocityY = -velocityY;
			}
		}

		return;
	}

	// Bricks collision
	Brick* brick = dynamic_cast<Brick*>(other);
	if (brick)
	{
		if (circle.getGlobalBounds().intersects(brick->GetRectangle().getGlobalBounds()))
		{
			std::string side = checkSideOfCollision(brick->GetRectangle());

			if (side == "left")
			{
				circle.setPosition(brick->GetRectangle().getPosition().x - (radius * 2), circle.getPosition().y);
				velocityX = -velocityX;
			}
			else if (side == "right")
			{
				circle.setPosition(brick->GetRectangle().getPosition().x + brick->GetRectangle().getSize().x, circle.getPosition().y);
				velocityX = -velocityX;
			}
			else if (side == "top")
			{
				circle.setPosition(circle.getPosition().x, brick->GetRectangle().getPosition().y - (radius * 2));
				velocityY = -velocityY;
			}
			else if (side == "bottom")
			{
				circle.setPosition(circle.getPosition().x, brick->GetRectangle().getPosition().y + brick->GetRectangle().getSize().y);
				velocityY = -velocityY;
			}

			brick->OnCollision(this);
		}

		return;
	}

	Window* window = dynamic_cast<Window*>(other);
	if (window)
	{
		if (circle.getPosition().x <= 0)
		{
			circle.setPosition(0, circle.getPosition().y);
			velocityX = -velocityX;
		}
		// Right collision
		if (circle.getPosition().x + (radius * 2) >= window->GetWidth())
		{
			circle.setPosition(window->GetWidth() - (radius * 2), circle.getPosition().y);
			velocityX = -velocityX;
		}
		// Up collision
		if (circle.getPosition().y <= 0)
		{
			circle.setPosition(circle.getPosition().x, 0);
			velocityY = -velocityY;
		}
		// Down collision
		if (circle.getPosition().y + (radius * 2) >= window->GetHeight())
		{
			circle.setPosition(circle.getPosition().x, window->GetHeight() - (radius * 2));
			velocityY = -velocityY;
		}

		return;
	}
}
