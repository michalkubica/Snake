#pragma once

#include <random>
#include <SFML\Graphics.hpp>

const int MAPSIZE = 20;
const float ONETILESIZE = 16;

class Apple
{
private:
	sf::Vector2i grid_position;
	sf::Vector2f window_position;
	sf::RectangleShape rectangle;
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist;
	void setupPositions() { rectangle.setPosition( ONETILESIZE * grid_position.x, ONETILESIZE * grid_position.y ); }

public:
	Apple();
	~Apple();
	sf::RectangleShape getTile() { return rectangle; }
	sf::Vector2i getGridPosition() { return grid_position; }
	void generateNewOne();
};