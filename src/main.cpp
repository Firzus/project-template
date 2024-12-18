#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Game.h"

int main()
{
    // Update
	const int fps = 60;
    const float fixedDeltaTime = 1.0f / fps;
    float timeSinceLastUpdate = 0.0f;
    sf::Clock clock;

    // Window
    Window* window = new Window("Breakout", 800, 600, 60);
    Game* game = new Game();

    while (window->isOpen() && game->IsRunning())
    {
        // Events
        game->HandleEvents(window);

        // Update
        float deltaTime = clock.restart().asSeconds();
        timeSinceLastUpdate += deltaTime;
		game->Update(window, deltaTime);
        while (timeSinceLastUpdate >= fixedDeltaTime) {
            game->FixedUpdate(window);
            timeSinceLastUpdate -= fixedDeltaTime;
        }

        // Render
        window->GetRenderWindow().clear(sf::Color::White);
        game->Draw(window);
        window->GetRenderWindow().display();
    }

    return 0;
}