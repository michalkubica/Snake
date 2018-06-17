#pragma once

#include <SFML\Graphics.hpp>

class TextDisplayer
{
private:
	sf::Text text;
	sf::Font font;
	std::string writing;
	int charsize;
	sf::Color color;
	sf::Vector2f position;
	void loadFont();

public:
	TextDisplayer( std::string s, int chs, sf::Color c, sf::Vector2f p );
	~TextDisplayer();
	void prepareFont();
	void setText( std::string s ) { writing = s; }
	sf::Text getText() { return text; }
};

