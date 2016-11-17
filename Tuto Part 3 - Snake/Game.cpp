#include "Game.h"

Game::Game() : m_window("Chapter 2 - Game Development", sf::Vector2u(800, 600)),
				m_snake(m_world.GetBlockSize(), &m_textbox), m_world(sf::Vector2u(800, 600))
{
	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_increment = sf::Vector2i(400, 400);

	m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
	m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
}

Game::~Game()
{
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& m_snake.GetPhysicalDirection() != Direction::Down)
	{
		m_snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& m_snake.GetPhysicalDirection() != Direction::Up)
	{
		m_snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& m_snake.GetPhysicalDirection() != Direction::Right)
	{
		m_snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& m_snake.GetPhysicalDirection() != Direction::Left)
	{
		m_snake.SetDirection(Direction::Right);
	}
}

void Game::Update()
{
	m_window.Update();
	
	float timestep = 1.0f / m_snake.GetSpeed();

	if (m_elapsed >= timestep) {
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;
		if (m_snake.HasLost()) {
			m_textbox.Add("GAME OVER! Score : " + std::to_string((long long)m_snake.GetScore()));
			m_snake.Reset();
		}
	}
}

void Game::Render()
{
	m_window.BeginDraw(); //Clear the window

	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_textbox.Render(*m_window.GetRenderWindow());
	
	m_window.EndDraw(); //Display
}

Window * Game::GetWindow()
{
	return &m_window;
}

float Game::GetElapsed() { return m_elapsed; }

void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }

void Game::MoveMushroom()
{
	sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_mushroomTexture.getSize();

	if ((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x
		&& m_increment.x > 0)
		|| (m_mushroom.getPosition().x < 0
			&& m_increment.x < 0)) {
		m_increment.x = -m_increment.x;
	}

	if ((m_mushroom.getPosition().y > l_windSize.y - l_textSize.y
		&& m_increment.y > 0)
		|| (m_mushroom.getPosition().y < 0
			&& m_increment.y < 0)) {
		m_increment.y = -m_increment.y;
	}

	float fElapsed = m_elapsed;

	m_mushroom.setPosition(
		m_mushroom.getPosition().x + (m_increment.x * fElapsed),
		m_mushroom.getPosition().y + (m_increment.y * fElapsed)
	);
}
