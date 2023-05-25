#pragma once

#include "feasy.hpp"
#include "ref.hpp"
#include "platform/platform.hpp"
#include "game.hpp"

namespace feasy
{
    struct ApplicationState
    {
        Game *gameInstance;
        b8 isRunning;
        Ref<Platform> platform;
        i32 width;
        i32 height;
    };

    class FEASY_API Application
    {
    public:
        void create(Game *gameInstance);
        void run();

    private:
        Ref<ApplicationState> m_appState;
    };
}