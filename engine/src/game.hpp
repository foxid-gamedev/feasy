
#pragma once

#include "feasy.hpp"

#include "containers/feasy_string.hpp"

namespace feasy
{
    struct FEASY_API AppConfig
    {
        i32 width;
        i32 height;
        String name;
    };

    class FEASY_API Game
    {
    public:
        Game(i32 width, i32 height, const String &title);

        virtual ~Game() {}

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(f32 delta) = 0;
        virtual void render() = 0;

        const AppConfig &getAppConfig() const { return m_config; }

    private:
        AppConfig m_config;
    };
}