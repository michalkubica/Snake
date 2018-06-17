#pragma once

#include "window.h"
#include "text.h"
#include "snake.h"
#include "apple.h"

enum class GameState { MENU, THEGAME, LOST };

class Game
{
private:
	Window window;
	GameState state;
	sf::Clock clock;
	sf::Time elapsed_time;
	float frametime;
	TextDisplayer txt_gametitle;
	TextDisplayer txt_startinfo;
	Snake snake;
	sf::Clock snake_clock;
	sf::Time snake_time;
	TextDisplayer txt_crashed;
	TextDisplayer txt_tryagain;

public:
	Game();
	~Game() {}
	void HandleInput();
	void Update();
	void Render();
	bool getFinishFlag() { return window.getDone(); }

	void restartClock() { elapsed_time += clock.restart(); }
	bool getFrametimeCondition() { return elapsed_time.asSeconds() >= frametime; }
	void substract() { elapsed_time -= sf::seconds( frametime ); }
};