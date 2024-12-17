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
	sf::Color color;

public:
	Entity();
	virtual ~Entity() = default;

	virtual void OnCollision(Entity* other) = 0;
};

Entity::Entity()
{
	width = 0;
	height = 0;
	posX = 0;
	posY = 0;
	speed = 0;
	velocityX = 0;
	velocityY = 0;
	color = sf::Color::Black;
}