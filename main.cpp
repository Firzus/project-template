#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    // Window
    const int wWidth = 800;
    const int wHeight = 600;
    const std::string wTitle = "Breakout";

    // Update
	const int fps = 60;
    const float fixedDeltaTime = 1.0f / fps;
    float timeSinceLastUpdate = 0.0f;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), wTitle, sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(fps);

    Game game;
    game.Start();

    while (window.isOpen() && game.IsRunning())
    {
        // Update
        float deltaTime = clock.restart().asSeconds();
        timeSinceLastUpdate += deltaTime;
		game.Update(deltaTime);
        while (timeSinceLastUpdate >= fixedDeltaTime) {
            game.FixedUpdate(fixedDeltaTime);
            timeSinceLastUpdate -= fixedDeltaTime;
        }

        // Events
        game.HandleEvents(window);

        // Render
        window.clear(sf::Color::White);
        game.Draw(window);
        window.display();
    }

    return 0;
}