#include <SFML/Graphics.hpp>

#include "FontManager.h"
#include "Ball.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    Ball ball(20, 50, 50, 3, 3, sf::Color::Blue);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.checkCollision(&window);

        window.clear();
        window.draw(ball.getCircle());
        ball.move();
        window.display();
    }

    return 0;
}