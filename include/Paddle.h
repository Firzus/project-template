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
	void Respawn() override;

	// Getters and setters
	sf::RectangleShape getRectangle() const { return rectangle; }
	void SetSpeed(float newSpeed) { speed = newSpeed; }
};