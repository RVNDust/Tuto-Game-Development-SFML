#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "Textbox.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();

	float GetElapsed();
	void RestartClock();

	void MoveSprite(EventDetails* l_details);
private:
	void MoveMushroom();

	Window m_window;
	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	sf::Vector2i m_increment;

	sf::Clock m_clock;
	float m_elapsed;

	Textbox m_textbox;
};


#endif // !GAME_H

