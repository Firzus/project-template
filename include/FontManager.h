#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class FontManager
{
private:
	sf::Font font;

public:
	FontManager();
	~FontManager();

	void LoadFont(const std::string& fontPath);
	
	// Getters
	sf::Font& GetFont() { return font; }
};

FontManager::FontManager() {}

FontManager::~FontManager()
{
	delete& font;
}

void FontManager::LoadFont(const std::string& fontPath)
{
	if (!font.loadFromFile(fontPath))
	{
		std::cout << "Error loading font: " << fontPath << std::endl;
	}
}