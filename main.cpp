#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Ball.h"

int main()
{
    Ball ball(20, 50, 50, 3, 3, sf::Color::Blue);

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
        ball.checkCollision(&window);

        ball.move();
        window.display();
    }

    return 0;
}