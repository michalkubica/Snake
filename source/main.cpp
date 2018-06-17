#include "window.h"
#include "game.h"

int main()
{
	Game game;

	while( !game.getFinishFlag() )
	{
		game.restartClock();
		if( game.getFrametimeCondition() )
		{
			game.Update();
			game.HandleInput();
			game.Render();
       		game.substract();
		}
	}
}