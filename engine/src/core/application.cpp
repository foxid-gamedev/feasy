#include "application.hpp"

#include <SDL.h>

using namespace feasy;

feasy::Application::Application(const ApplicationConfig &config)
    : m_platform(createRef<Platform>(config))
{

}

void feasy::Application::run()
{
    m_platform->initialize();
    m_isRunning = true;
}

void feasy::Application::stop() const
{
    m_isRunning = false;
}