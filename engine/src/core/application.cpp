#include "application.hpp"

#include "core/logger.hpp"

#include <SDL.h>

using namespace feasy;

void Application::create(Game *gameInstance)
{
    FEASY_LOG_INFO("Create Application Layer...");
    m_appState = createRef<ApplicationState>();

    m_appState->gameInstance = gameInstance;

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
    FEASY_LOG_INFO("Init Game...");
    auto game = m_appState->gameInstance;
    game->init();

    FEASY_LOG_INFO("Start Game-Loop...");
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

    FEASY_LOG_INFO("Application stopped.");
    // cleanup
    m_appState->platform->destroy();

    FEASY_LOG_INFO("Platform destroyed.");

    FEASY_LOG_INFO("Exited Game!");
}
