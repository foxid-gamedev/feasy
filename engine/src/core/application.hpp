#pragma once

#include "feasy.hpp"
#include "ref.hpp"
#include "platform/platform.hpp"

namespace feasy
{
    class FEASY_API Application
    {
    public:
        explicit Application(const ApplicationConfig &config);

        void run();
        void stop() const;
        b8 isRunning() const { return m_isRunning; }

        const Platform &get_platform() { return *m_platform; }

    private:
        Ref<Platform> m_platform{nullptr};
        mutable b8 m_isRunning{false};
    };
}