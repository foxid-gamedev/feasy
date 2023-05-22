
#pragma once

#include "feasy.hpp"

class Platform;
class Application;

#include "containers/feasy_string.hpp"
#include "core/application.hpp"

namespace feasy
{
    class FEASY_API Game
    {
    public:
        Game(i32 width, i32 height, const String &title);

        virtual ~Game() {}

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(f32 delta) = 0;
        virtual void render() = 0;

        const Application &get_app() { return *m_app; }

    private:
        Ref<Application> m_app;
    };
}