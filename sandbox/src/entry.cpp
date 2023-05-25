#include <feasy.hpp>
#include <entry.hpp>

#include <iostream>

class SandboxGame : public feasy::Game
{
public:
    SandboxGame() : feasy::Game(1280, 720, "Sandbox Game") {}

    void init() override
    {
        std::cout << "hello";
    }

    void handleInput() override
    {
    }

    void
    update(feasy::f32 delta) override
    {
        delta = 0.0f;
    }

    void render() override {}
};

feasy::Game *createGame()
{
    return new SandboxGame();
}
