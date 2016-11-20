#include "Game.h"
#include <iostream>

Game::Game() : m_window("Chapter 4 - Game Development", sf::Vector2u(800, 600))
{
	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_increment = sf::Vector2i(400, 400);

	m_window.GetEventManager()->AddCallback("Move",
		&Game::MoveSprite, this);
}

Game::~Game()
{
}

void Game::HandleInput()
{
}

void Game::Update()
{
	m_window.Update();
}

void Game::Render()
{
	m_window.BeginDraw(); //Clear the window

	m_window.Draw(m_mushroom);
	
	m_window.EndDraw(); //Display
}

Window * Game::GetWindow()
{
	return &m_window;
}

float Game::GetElapsed() { return m_elapsed; }

void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }

void Game::MoveSprite(EventDetails * l_details)
{
	sf::Vector2i mousepos =
		m_window.GetEventManager()->GetMousePos(
			m_window.GetRenderWindow());
	m_mushroom.setPosition(mousepos.x, mousepos.y);
	std::cout << "Moving sprite to: "
		<< mousepos.x << ":"
		<< mousepos.y << std::endl;
}

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
