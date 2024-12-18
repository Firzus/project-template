#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	int width;
	int height;
	float posX;
	float posY;
	float speed;
	float velocityX;
	float velocityY;

	float initialPosX;
	float initialPosY;
	float initialSpeed;
	float initialVelocityX;
	float initialVelocityY;
	sf::Color color;

public:
	Entity();
	virtual ~Entity() = default;

	virtual void OnCollision(Entity* other) = 0;
	virtual void Respawn() = 0;
};