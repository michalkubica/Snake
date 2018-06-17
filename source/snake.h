#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "window.h"
#include "apple.h"

enum class Direction { NONE, UP, DOWN, RIGHT, LEFT };

struct SnakeSegment
{
	SnakeSegment( int x, int y, sf::Color c ) : grid_position( x, y ), rectangle( sf::Vector2f( ONETILESIZE, ONETILESIZE ) )
	{
		rectangle.setFillColor( c );
		setupPositions();
		rectangle.setOutlineThickness( -1 );
		rectangle.setOutlineColor( sf::Color( 0, 0, 0 ) );
	}
	sf::Vector2i grid_position;
	sf::Vector2f window_position;
	sf::RectangleShape rectangle;
	sf::RectangleShape getTile() { return rectangle; }
	void setupPositions() { rectangle.setPosition( ONETILESIZE * grid_position.x, ONETILESIZE * grid_position.y ); }
	void setGridPosition( sf::Vector2i p ) { grid_position = p; }
};

class Snake
{
private:
	std::vector<SnakeSegment> snakebody;
	Direction dir;
	int score;
	std::vector<sf::Vector2i> prev_positions;
	Apple apple;
	bool crashed;
	void moveHead();
	void moveBody();
	void updatePrevPos();
	void expand();
	bool otherArrowsClicked( sf::Keyboard::Key k );

public:
	Snake();
	~Snake();
	void processInput();
	void setDirection( Direction d ) { dir = d; }
	void drawSnake( Window &window );
	void tick();
	std::vector<SnakeSegment> getBody() { return snakebody;	}
	sf::RectangleShape getAppleTile() { return apple.getTile(); }
	void checkCollision();
	bool hasCrashed() { return crashed; }
	void reset();
	int getScore() { return score; }
};

