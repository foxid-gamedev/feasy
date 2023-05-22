#include "game.hpp"

feasy::Game::Game(i32 width, i32 height, const String &title)
	: m_app(createRef<Application>(ApplicationConfig{width, height, title}))
{
	m_app->run();
}
