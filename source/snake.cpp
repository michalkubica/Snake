#include "snake.h"
#include <algorithm>

Snake::Snake() : score( 0 ), crashed( false )
{
	snakebody.clear();
	snakebody.push_back( SnakeSegment( 7, 15, sf::Color( 255, 255, 0 ) ) );
	snakebody.push_back( SnakeSegment( 6, 15, sf::Color( 0, 255, 0 ) ) );
	snakebody.push_back( SnakeSegment( 5, 15, sf::Color( 0, 255, 0 ) ) );
	setDirection( Direction::NONE );
}

Snake::~Snake()
{
}

bool Snake::otherArrowsClicked( sf::Keyboard::Key k )
{
	switch( k )
	{
	case sf::Keyboard::Up: return sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Right );
	case sf::Keyboard::Down: return sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Right );
	case sf::Keyboard::Left: return sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Right );
	case sf::Keyboard::Right: return sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Left );
	}
}

void Snake::processInput()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && dir != Direction::DOWN && !otherArrowsClicked( sf::Keyboard::Up ) ) dir = Direction::UP;
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && dir != Direction::UP && !otherArrowsClicked( sf::Keyboard::Down ) ) dir = Direction::DOWN;
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && dir != Direction::RIGHT && !otherArrowsClicked( sf::Keyboard::Left ) ) dir = Direction::LEFT;
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && dir != Direction::LEFT && !otherArrowsClicked( sf::Keyboard::Right ) ) dir = Direction::RIGHT;
}

void Snake::drawSnake( Window &window )
{
	std::for_each( snakebody.rbegin(), snakebody.rend(), [ & ]( SnakeSegment x ) { window.Draw( x.getTile() ); } );
}

void Snake::tick()
{	
	updatePrevPos();
	moveHead();
	moveBody();
	if( snakebody[ 0 ].grid_position == apple.getGridPosition() )
	{
		do
		{
			apple.generateNewOne();
		} while( std::any_of( snakebody.begin(), snakebody.end(), [ & ]( SnakeSegment x ) { return x.grid_position == apple.getGridPosition(); } ) );
		score++;
		expand();
	}
	checkCollision();
}

void Snake::moveHead()
{
	if( dir == Direction::RIGHT ) { snakebody[ 0 ].grid_position.x++; snakebody[ 0 ].setupPositions(); }
	else if( dir == Direction::LEFT ) { snakebody[ 0 ].grid_position.x--; snakebody[ 0 ].setupPositions(); }
	else if( dir == Direction::DOWN ) { snakebody[ 0 ].grid_position.y++; snakebody[ 0 ].setupPositions(); }
	else if( dir == Direction::UP ) { snakebody[ 0 ].grid_position.y--; snakebody[ 0 ].setupPositions(); }
}

void Snake::moveBody()
{
	for( int i = 1; i < snakebody.size(); i++ )
	{
		snakebody[ i ].setGridPosition( prev_positions[ i - 1 ] );
		snakebody[ i ].setupPositions();
	}
	prev_positions.clear();
}

void Snake::updatePrevPos()
{
	std::for_each( snakebody.begin(), snakebody.end() - 1, [ & ]( SnakeSegment x ) { prev_positions.push_back( x.grid_position ); } );
}

void Snake::expand()
{
	snakebody.push_back( SnakeSegment( apple.getGridPosition().x, apple.getGridPosition().y, sf::Color( 0, 255, 0 ) ) );
}

void Snake::checkCollision()
{
	if( snakebody[ 0 ].grid_position.x < 0 || snakebody[ 0 ].grid_position.x > 23 ) crashed = true;
	if( snakebody[ 0 ].grid_position.y < 0 || snakebody[ 0 ].grid_position.y > 23 ) crashed = true;
	for( int i = 3; i < snakebody.size(); ++i ) if( snakebody[ 0 ].grid_position == snakebody[ i ].grid_position ) crashed = true;
}

void Snake::reset()
{
	crashed = false;
	score = 0;
	snakebody.clear();
	snakebody.push_back( SnakeSegment( 7, 15, sf::Color( 255, 255, 0 ) ) );
	snakebody.push_back( SnakeSegment( 6, 15, sf::Color( 0, 255, 0 ) ) );
	snakebody.push_back( SnakeSegment( 5, 15, sf::Color( 0, 255, 0 ) ) );
	setDirection( Direction::NONE );
	do
	{
		apple.generateNewOne();
	} while( std::any_of( snakebody.begin(), snakebody.end(), [ & ]( SnakeSegment x ) { return x.grid_position == apple.getGridPosition(); } ) );
}