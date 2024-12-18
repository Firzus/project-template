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