#include "platform.hpp"

#include "core/logger.hpp"

#include <SDL.h>

using namespace feasy;

Platform::Platform(const ApplicationConfig &appConfig)
    : m_appConfig(createRef<ApplicationConfig>(appConfig))
{
}

Platform::~Platform()
{
    if (m_windowHandle == nullptr)
    {
        log::warn("Platform window handle is null.");
        return;
    }

    SDL_DestroyWindow(reinterpret_cast<SDL_Window *>(m_windowHandle));
    SDL_Quit();
}

void feasy::Platform::initialize()
{
    auto result = SDL_Init(SDL_INIT_VIDEO);

    if (result != 0)
    {
        log::fatal("failed to initailize SDL: %s", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow(
        "feasy engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_appConfig->width,
        m_appConfig->height,
        SDL_WINDOW_VULKAN);

    if (window == nullptr)
    {
        log::fatal("failed to create SDL window: %s", SDL_GetError());
        SDL_Quit();
    }

    m_windowHandle = reinterpret_cast<void *>(window);
}

void Platform::resetEvent() const
{
    m_event = {0};
}

b8 Platform::pollEvent() const
{
    return SDL_PollEvent(&m_event);
}

b8 Platform::isCloseEvent() const
{
    return m_event == SDL_QUIT;
}
