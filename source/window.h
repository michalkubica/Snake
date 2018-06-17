#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Window
{
private:
	sf::RenderWindow the_window;
	std::string window_title;
	sf::Vector2u window_size;
	bool done;

public:
	Window( const std::string& title, const sf::Vector2u& size ) : window_title( title ), window_size( size ), done( 0 ) { Create(); }
	~Window() { the_window.close(); }
	void Create();
	void Update();
	void BeginDraw();
	void Draw( sf::Drawable& drawable_item );
	void EndDraw();
	bool getDone() { return done; }
};