#pragma once

#include "feasy.hpp"

#include "core/logger.hpp"
#include "platform/platform.hpp"
#include "game.hpp"

// TODO: remove and wrap SDL input event system
#include <SDL.h>

extern feasy::Game *createGame();

int main()
{
    feasy::log::initialize();
    feasy::Game *game = createGame();

    if (game == nullptr)
    {
        feasy::log::fatal("game instance isn't initialized or defined");
        return -1;
    }

    game->init();

    auto app = game->get_app();
    auto platform = app.get_platform();

    while (game->get_app().isRunning())
    {
        // input handling
        platform.resetEvent();
        while (platform.pollEvent())
        {
            if (platform.isCloseEvent())
            {
                app.stop();
            }
            game->handleInput();
        }

        // TODO: evaluate delta
        game->update(0.166);

        game->render();
    }

    return 0;
}