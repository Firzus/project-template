#pragma once
#include <string>

class Window
{
private:
	const int width;
	const int height;
	const std::string title;
	sf::RenderWindow window;
	const int fps;

public:
	Window(std::string title, int width, int height, int fps);
	~Window();

	// Getters
	bool isOpen() const { return window.isOpen(); }
	sf::RenderWindow& GetWindow() { return window; }
};

Window::Window(std::string title, int width, int height, int fps) : title(title), width(width), height(height), fps(fps)
{
	window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(fps);
}

Window::~Window()
{
	window.close();
}