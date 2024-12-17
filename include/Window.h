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

	// Getters
	bool isOpen() const { return renderWindow.isOpen(); }
	sf::RenderWindow& GetRenderWindow() { return renderWindow; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
};

Window::Window(std::string title, int width, int height, int fps)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->fps = fps;

	renderWindow.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	renderWindow.setFramerateLimit(fps);
}

Window::~Window()
{
	renderWindow.close();
}

void Window::OnCollision(Entity* other)
{
	// Do nothing
}
