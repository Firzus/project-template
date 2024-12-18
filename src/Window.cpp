#include "Window.h"

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
