#include "Game.h"

Game::Game()
{
	fontManager.LoadFont("resources/fonts/Roboto.ttf");

	score = 0;
	currentLevel = 1;

	isRunning = true;

	scoreText.setFont(fontManager.GetFont());
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(10, 10);
	scoreText.setString("Score : " + std::to_string(score));

	paddle = new Paddle(175, 30, 400, 550, 5, sf::Color::Blue);
	ball = new Ball(20, 400, 300, 6, -6, sf::Color::Blue);

	levels[1] = Level({
		{ {0, 0}, true }, { {1, 0}, true }, { {2, 0}, true }, { {3, 0}, true }, { {4, 0}, true }, { {5, 0}, true }, { {6, 0}, true }, { {7, 0}, true },
		{ {0, 1}, true }, { {1, 1}, true }, { {2, 1}, true }, { {3, 1}, true }, { {4, 1}, true }, { {5, 1}, true }, { {6, 1}, true }, { {7, 1}, true },
	});

	levels[2] = Level({
		{ {0, 0}, true }, { {1, 0}, true }, { {2, 0}, true }, { {3, 0}, true }, { {4, 0}, true }, { {5, 0}, true }, { {6, 0}, true }, { {7, 0}, true },
		{ {0, 1}, true }, { {1, 1}, true }, { {2, 1}, true }, { {3, 1}, true }, { {4, 1}, true }, { {5, 1}, true }, { {6, 1}, true }, { {7, 1}, true },
		{ {0, 2}, true }, { {1, 2}, true }, { {2, 2}, true }, { {3, 2}, true }, { {4, 2}, true }, { {5, 2}, true }, { {6, 2}, true }, { {7, 2}, true },
	});

	levels[3] = Level({
		{ {0, 0}, true }, { {1, 0}, true }, { {2, 0}, true }, { {3, 0}, true }, { {4, 0}, true }, { {5, 0}, true }, { {6, 0}, true }, { {7, 0}, true },
		{ {0, 1}, true }, { {1, 1}, true }, { {2, 1}, true }, { {3, 1}, true }, { {4, 1}, true }, { {5, 1}, true }, { {6, 1}, true }, { {7, 1}, true },
		{ {0, 2}, true }, { {1, 2}, true }, { {2, 2}, true }, { {3, 2}, true }, { {4, 2}, true }, { {5, 2}, true }, { {6, 2}, true }, { {7, 2}, true },
		{ {0, 3}, true }, { {1, 3}, true }, { {2, 3}, true }, { {3, 3}, true }, { {4, 3}, true }, { {5, 3}, true }, { {6, 3}, true }, { {7, 3}, true },
	});

	BuildLevel(currentLevel);
}

Game::~Game()
{
	isRunning = false;
}

void Game::Update(Window* window, float deltaTime)
{
	ball->OnCollision(window);
	ball->OnCollision(paddle);

	for (Brick& brick : bricks) 
	{
		brick.OnCollision(ball);
		ball->OnCollision(&brick);	
	}

	size_t bricksNumber = bricks.size();
	bricks.erase(std::remove_if(bricks.begin(), bricks.end(), [](const Brick& brick) { return brick.IsDestroyed(); }), bricks.end());

	if (bricks.size() < bricksNumber)
	{
		score += 10;
		scoreText.setString("Score : " + std::to_string(score));
	}

	// check si level est complete
	if (bricks.empty())
	{
		if (levels.find(currentLevel + 1) == levels.end())
		{
			isRunning = false;
			return;
		}

		currentLevel++;
		ball->Respawn();
		paddle->Respawn();
		BuildLevel(currentLevel);
	}

	// If the ball go out of the screen
	if (ball->HasLost())
	{
		ball->Respawn();
		paddle->Respawn();
		BuildLevel(1);

		score = 0;
		scoreText.setString("Score : " + std::to_string(score));
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
	for (Brick brick : bricks)
	{
		if (brick.IsDestroyed()) continue;
		window->GetRenderWindow().draw(brick.GetRectangle());
	}
	window->GetRenderWindow().draw(ball->getCircle());
	window->GetRenderWindow().draw(paddle->GetRectangle());
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

void Game::BuildLevel(int levelIndex)
{
	bricks.clear();
	for (auto const& brick : levels[levelIndex].GetGrid())
	{
		if (!brick.second) continue;
		bricks.push_back(Brick(100, 30, brick.first.first * (float)100, brick.first.second * (float)30, sf::Color::Red));
	}
}
