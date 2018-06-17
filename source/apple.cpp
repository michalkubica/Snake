#include "apple.h"

Apple::Apple() : rectangle( sf::Vector2f( ONETILESIZE, ONETILESIZE ) ), dist( 0, 23 )
{
	rectangle.setFillColor( sf::Color( 255, 0, 0 ) );
	rectangle.setOutlineThickness( -1 );
	rectangle.setOutlineColor( sf::Color( 0, 0, 0 ) );
	generateNewOne();
}

Apple::~Apple()
{
}

void Apple::generateNewOne()
{
	sf::Vector2i randpos;
	randpos.x = dist( gen );
	randpos.y = dist( gen );
	grid_position = randpos;
	setupPositions();
}
