#include "FontManager.h"

FontManager::FontManager() {}

FontManager::~FontManager() {}

void FontManager::LoadFont(const std::string& fontPath)
{
	if (!font.loadFromFile(fontPath))
	{
		std::cout << "Error loading font: " << fontPath << std::endl;
	}
}