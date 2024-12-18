#include "Game.h"

Game::Game()
{
	fontManager.LoadFont("resources/fonts/Roboto.ttf");

	score = 0;
	lives = 3;
	currentLevel = 1;

	isRunning = true;

	scoreText.setFont(fontManager.GetFont());
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(10, 10);
	scoreText.setString("Score : " + std::to_string(score));

	paddle = new Paddle(200, 30, 400, 550, 5, sf::Color::Blue);
	ball = new Ball(20, 400, 300, 5, 5, sf::Color::Blue);

	levels[1] = Level({
		{0, 1}, {1, 1}, {2, 1}, {3, 1},
		{4, 1}, {5, 1}, {6, 1}, {7, 1}
		});

	levels[2] = Level({
		{0, 1}, {1, 1}, {2, 1}, {3, 1},
		{4, 1}, {5, 1}, {6, 1}, {7, 1}
		});
}

Game::~Game()
{
	isRunning = false;
}

void Game::Update(Window* window, float deltaTime)
{
	ball->OnCollision(window);
	ball->OnCollision(paddle);

	for (Brick brick : levels[currentLevel].GetBricks()) {
		brick.OnCollision(ball);
		ball->OnCollision(&brick);
	}

	levels[currentLevel].CheckBricksCollision();

	// check si level est complete
	if (levels[currentLevel].IsCompleted())
	{
		currentLevel++;
	}
}

void Game::FixedUpdate(Window* window)
{
	ball->Move();

	// Inputs
	if (isLeftArrowPressed)
	{
		paddle->MoveLeft();
	}
	if (isRightArrowPressed)
	{
		paddle->MoveRight(window->GetWidth());
	}
}

void Game::Draw(Window* window)
{
	for (const auto& pair : levels[1].GetBricks()) {
		window->GetRenderWindow().draw(pair.GetRectangle());
	}
	window->GetRenderWindow().draw(ball->getCircle());
	window->GetRenderWindow().draw(paddle->getRectangle());
	window->GetRenderWindow().draw(scoreText);
}

void Game::HandleEvents(Window* window)
{
	sf::Event event;
	while (window->GetRenderWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->GetRenderWindow().close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->GetRenderWindow().close();
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				levels[currentLevel].IsCompleted() ? std::cout << "Level " << currentLevel << " Complete" : std::cout << "Level " << currentLevel << " Incomplete";
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				isLeftArrowPressed = true;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				isRightArrowPressed = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				isLeftArrowPressed = false;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				isRightArrowPressed = false;
			}
		}
	}
}
