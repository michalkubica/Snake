#include "text.h"

TextDisplayer::TextDisplayer( std::string s, int chs, sf::Color c, sf::Vector2f p ) : writing( s ), charsize( chs ), color( c ), position( p )
{
	loadFont();
	prepareFont();
}

TextDisplayer::~TextDisplayer()
{
}

void TextDisplayer::loadFont()
{
	if( !font.loadFromFile( "consolas.ttf" ) ) exit( EXIT_FAILURE );
}

void TextDisplayer::prepareFont()
{
	text.setFont( font );
	text.setString( writing );
	text.setCharacterSize( charsize );
	text.setFillColor( color );
	text.setPosition( position );
}