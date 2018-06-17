#include "window.h"

void Window::Create() { the_window.create( { window_size.x, window_size.y }, window_title, sf::Style::Close ); }
void Window::BeginDraw() { the_window.clear( sf::Color::Black ); }
void Window::Draw( sf::Drawable& drawable_item ) { the_window.draw( drawable_item ); }
void Window::EndDraw() { the_window.display(); }

void Window::Update()
{
	sf::Event event;
	while( the_window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed ) done = true;
	}
}