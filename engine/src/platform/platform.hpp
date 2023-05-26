#pragma once

#include "feasy.hpp"

#include "containers/feasy_string.hpp"
#include "core/ref.hpp"

namespace feasy
{
    struct RenderState
    {
        void *contextHandle;
    };

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

        const PlatformState &getState() const { return *m_platformState; }

    private:
        Ref<PlatformState> m_platformState;
        Ref<RenderState> m_renderState;
    };

}