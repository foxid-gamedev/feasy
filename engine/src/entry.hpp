#pragma once

#include "feasy.hpp"

#include "core/application.hpp"
#include "game.hpp"

extern feasy::Game *createGame();

int main()
{
    feasy::Game *game = createGame();

    if (game == nullptr)
    {
        return -1;
    }

    feasy::Application app;
    app.create(game);
    app.run();

    return 0;
}
