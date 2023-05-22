#pragma once

#include "feasy.hpp"

#include "containers/feasy_string.hpp"
#include "core/ref.hpp"

namespace feasy
{
    struct PlatformState
    {
        void *handle;
        i32 width;
        i32 height;
        String name;
    };

    class Platform
    {
    public:
        void create(i32 width, i32 height, const String &app_name);
        void destroy();

        const PlatformState &getState() const { return *m_state; }

    private:
        Ref<PlatformState> m_state;
    };

}