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

	initialPosX = posX;
	initialPosY = posY;
	initialVelocityX = velocityX;
	initialVelocityY = velocityY;

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
		if (circle.getGlobalBounds().intersects(paddle->GetRectangle().getGlobalBounds()))
		{
			std::string side = checkSideOfCollision(paddle->GetRectangle());

			if (side == "left")
			{
				Bounce(paddle, side);
				//circle.setPosition(paddle->getRectangle().getPosition().x - (radius * 2), circle.getPosition().y);
			}
			else if (side == "right")
			{
				Bounce(paddle, side);
				//circle.setPosition(paddle->getRectangle().getPosition().x + paddle->getRectangle().getSize().x, circle.getPosition().y);
			}
			else if (side == "top")
			{
				Bounce(paddle, side);
				//circle.setPosition(circle.getPosition().x, paddle->getRectangle().getPosition().y - (radius * 2));
			}
			else if (side == "bottom")
			{
				Bounce(paddle, side);
				//circle.setPosition(circle.getPosition().x, paddle->getRectangle().getPosition().y + paddle->getRectangle().getSize().y);
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
				Bounce(brick, side);
				//circle.setPosition(brick->GetRectangle().getPosition().x - (radius * 2), circle.getPosition().y);
			}
			else if (side == "right")
			{
				Bounce(brick, side);
				//circle.setPosition(brick->GetRectangle().getPosition().x + brick->GetRectangle().getSize().x, circle.getPosition().y);
			}
			else if (side == "top")
			{
				Bounce(brick, side);
				//circle.setPosition(circle.getPosition().x, brick->GetRectangle().getPosition().y - (radius * 2));
			}
			else if (side == "bottom")
			{
				Bounce(brick, side);
				//circle.setPosition(circle.getPosition().x, brick->GetRectangle().getPosition().y + brick->GetRectangle().getSize().y);
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

		// Down collision (losing)
		if (circle.getPosition().y >= window->GetHeight())
		{
			lost = true;
		}

		return;
	}
}

void Ball::Respawn()
{
	circle.setPosition(initialPosX, initialPosY);
	velocityX = initialVelocityX;
	velocityY = initialVelocityY;
	lost = false;
}

void Ball::Bounce(Entity* entity, std::string side)
{
	float normalX = 0.0f, normalY = 0.0f;

	if (side == "left") {
		normalX = -1.0f;
	}
	else if (side == "right") {
		normalX = 1.0f;
	}
	else if (side == "top") {
		normalY = -1.0f;
	}
	else if (side == "bottom") {
		normalY = 1.0f;
	}

	// Calculate dot product
	float dotProduct = velocityX * normalX + velocityY * normalY;

	// Calculate reflection vectors
	float reflectX = velocityX - 2 * dotProduct * normalX;
	float reflectY = velocityY - 2 * dotProduct * normalY;

	// Calculate initial speed and new magnitude to normalize reflection vectors
	float initialSpeed = std::sqrt(velocityX * velocityX + velocityY * velocityY);
	float magnitude = std::sqrt(reflectX * reflectX + reflectY * reflectY);

	// Calculate new directions with the new values
	velocityX = (reflectX / magnitude) * initialSpeed;
	velocityY = (reflectY / magnitude) * initialSpeed;


	Paddle* paddle = dynamic_cast<Paddle*>(entity);
	if (paddle)
	{
		if (side == "left") {
			circle.setPosition(paddle->GetRectangle().getPosition().x - radius * 2, circle.getPosition().y);
		}
		else if (side == "right") {
			circle.setPosition(paddle->GetRectangle().getPosition().x + paddle->GetRectangle().getSize().x, circle.getPosition().y);
		}
		else if (side == "top") {
			circle.setPosition(circle.getPosition().x, paddle->GetRectangle().getPosition().y - radius * 2);
		}
		else if (side == "bottom") {
			circle.setPosition(circle.getPosition().x, paddle->GetRectangle().getPosition().y + paddle->GetRectangle().getSize().y);
		}

		if (side == "top" || side == "bottom") {
			velocityX += (circle.getPosition().x + radius - paddle->GetRectangle().getPosition().x + (paddle->GetRectangle().getSize().x / 2)) * 0.005f;
		}
		else if (side == "left" || side == "right") {
			velocityY += (circle.getPosition().y + radius - paddle->GetRectangle().getPosition().y + (paddle->GetRectangle().getSize().y / 2)) * 0.005f;
		}
	}

	Brick* brick = dynamic_cast<Brick*>(entity);
	if (brick)
	{
		if (side == "left") {
			circle.setPosition(brick->GetRectangle().getPosition().x - radius * 2, circle.getPosition().y);
		}
		else if (side == "right") {
			circle.setPosition(brick->GetRectangle().getPosition().x + brick->GetRectangle().getSize().x, circle.getPosition().y);
		}
		else if (side == "top") {
			circle.setPosition(circle.getPosition().x, brick->GetRectangle().getPosition().y - radius * 2);
		}
		else if (side == "bottom") {
			circle.setPosition(circle.getPosition().x, brick->GetRectangle().getPosition().y + brick->GetRectangle().getSize().y);
		}

		if (side == "top" || side == "bottom") {
			velocityX += (circle.getPosition().x + radius - brick->GetRectangle().getPosition().x + (brick->GetRectangle().getSize().x / 2)) * 0.005f;
		}
		else if (side == "left" || side == "right") {
			velocityY += (circle.getPosition().y + radius - brick->GetRectangle().getPosition().y + (brick->GetRectangle().getSize().y / 2)) * 0.005f;
		}
	}

}
