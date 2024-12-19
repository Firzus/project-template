#pragma once

#include "Entity.h"

class Ball : public Entity
{
private:
	sf::CircleShape circle;
	float radius;
	bool lost = false;

public:
	Ball(float radius, float posX, float posY, float velocityX, float velocityY, sf::Color color);
	~Ball();

	void Move();
	std::string checkSideOfCollision(sf::RectangleShape rect);
	void OnCollision(Entity* other) override;
	void Respawn() override;
	void Bounce(Entity* entity, std::string side);

	// Getters and setters
	sf::CircleShape getCircle() const { return circle; }
	bool HasLost() const { return lost; }
	void setVelocity(float newVelocityX, float newVelocityY) { velocityX = newVelocityX, velocityY = newVelocityY; }
};