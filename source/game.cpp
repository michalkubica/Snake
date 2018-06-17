#include "game.h"

Game::Game() : window( "Snake", sf::Vector2u( 384, 384 ) ),
			   txt_gametitle( "SNAKE", 38, sf::Color::White, sf::Vector2f( 146, 100 ) ),
	           txt_startinfo( "Press space to start", 18, sf::Color::White, sf::Vector2f( 100, 210 ) ),
			   txt_crashed( "Your snake has crashed", 26, sf::Color::White, sf::Vector2f( 42, 120 ) ),
			   txt_tryagain( "Score: xx | press space to try again", 16, sf::Color::White, sf::Vector2f( 36, 200 ) ),
			   snake()
{
	state = GameState::MENU;
	frametime = 1.0 / 60.0;
}

void Game::Render()
{
	window.BeginDraw();
	if( state == GameState::MENU )
	{
		window.Draw( txt_gametitle.getText() );
		window.Draw( txt_startinfo.getText() );
	}
	else if( state == GameState::THEGAME )
	{
		snake.drawSnake( window );
		window.Draw( snake.getAppleTile() );
	}
	else if( state == GameState::LOST )
	{
		window.Draw( txt_crashed.getText() );
		window.Draw( txt_tryagain.getText() );
	}
	window.EndDraw();
}

void Game::Update() 
{
	window.Update();
	if( snake_clock.getElapsedTime().asMilliseconds() >= 80 && state == GameState::THEGAME )
	{
		snake.tick();
		snake_clock.restart();
		if( snake.hasCrashed() )
		{
			txt_tryagain.setText( "Score: " + std::to_string( snake.getScore() ) + " | press space to try again" );
			txt_tryagain.prepareFont();
			state = GameState::LOST;
		}
	}
}

void Game::HandleInput()
{
	if( state == GameState::MENU && sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
	{
		state = GameState::THEGAME;
		snake.setDirection( Direction::RIGHT );
	}
	else if( state == GameState::THEGAME ) snake.processInput();
	else if( state == GameState::LOST && sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
	{
		snake.reset();
		state = GameState::THEGAME;
		snake.setDirection( Direction::RIGHT );
	}
}