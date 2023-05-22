#pragma once

#include "containers/feasy_string.hpp"
#include "core/ref.hpp"
#include "feasy.hpp"

namespace feasy
{

    struct FEASY_API ApplicationConfig
    {
        i32 width = 1280;
        i32 height = 720;
        String name;
    };

    class FEASY_API Platform
    {
    public:
        explicit Platform(const ApplicationConfig &appConfig);
        ~Platform();

        void initialize();

        void resetEvent() const;
        b8 pollEvent() const;
        b8 isCloseEvent() const;

        const ApplicationConfig &getAppConfig() const { return *m_appConfig; }

    private:
        Ref<ApplicationConfig> m_appConfig{nullptr};
        void *m_windowHandle{nullptr};
        SDL_Event m_event;
    };

}