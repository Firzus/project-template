#pragma once

#include <string>

#include "Entity.h"

class Window : public Entity
{
private:
	std::string title;
	sf::RenderWindow renderWindow;
	int fps;

public:
	Window(std::string title, int width, int height, int fps);
	~Window();

	void OnCollision(Entity* other) override;
	void Respawn() override;

	// Getters
	bool isOpen() const { return renderWindow.isOpen(); }
	sf::RenderWindow& GetRenderWindow() { return renderWindow; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
};