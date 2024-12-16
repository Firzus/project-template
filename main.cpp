#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Window.h"

int main()
{
    // Update
	const int fps = 60;
    const float fixedDeltaTime = 1.0f / fps;
    float timeSinceLastUpdate = 0.0f;
    sf::Clock clock;

    // Window
    Window window("Breakout", 800, 600, 60);
    Game game;

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
        game.HandleEvents(window.GetWindow());

        // Render
        window.GetWindow().clear(sf::Color::White);
        game.Draw(window.GetWindow());
        window.GetWindow().display();
    }

    return 0;
}