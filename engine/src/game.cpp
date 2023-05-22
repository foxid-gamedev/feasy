#include "game.hpp"

feasy::Game::Game(i32 width, i32 height, const String &title)
{
	m_config.width = width;
	m_config.height = height;
	m_config.name = title;
}
