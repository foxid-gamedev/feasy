#pragma once

#include "feasy.hpp"
#include "ref.hpp"

#include "game.hpp"

namespace feasy
{
    struct ApplicationState;

    class FEASY_API Application
    {
    public:
        void create(Game *gameInstance);
        void run();

    private:
        Ref<ApplicationState> m_appState{nullptr};
    };
}