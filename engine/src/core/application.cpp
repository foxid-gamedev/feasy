#include "application.hpp"

#include "platform/platform.hpp"
// #include "core/logger.hpp"

#include "ref.hpp"

#include <SDL.h>

using namespace feasy;

struct feasy::ApplicationState
{
    Game *gameInstance;
    b8 isRunning;
    Ref<Platform> platform;
    i32 width;
    i32 height;
};

void Application::create(Game *gameInstance)
{
    m_appState = createRef<ApplicationState>();

    m_appState->gameInstance = gameInstance;

    // Logger::initialize(LogLevel::DEBUG);

    // FEASY_FATAL("test fatal msg: %f", 3.14f);
    // FEASY_ERROR("test error msg: %f", 3.14f);
    // FEASY_INFO("test info msg: %f", 3.14f);
    // FEASY_DEBUG("test debug msg: %f", 3.14f);
    // FEASY_TRACE("test fatal msg: %f", 3.14f);

    m_appState->isRunning = true;

    m_appState->platform = createRef<Platform>();

    auto app_config = gameInstance->getAppConfig();
    m_appState->width = app_config.width;
    m_appState->height = app_config.height;
    m_appState->platform->create(app_config.width, app_config.height, app_config.name);
}

void Application::run()
{
    // init
    auto game = m_appState->gameInstance;
    game->init();

    while (m_appState->isRunning)
    {
        // input handling
        // TODO: event system for clients
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                m_appState->isRunning = false;
            }

            game->handleInput();
        }

        // TODO: add delta time
        game->update(3.14f);

        game->render();
    }

    // cleanup
    m_appState->platform->destroy();
}
