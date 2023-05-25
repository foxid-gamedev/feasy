#include "platform.hpp"

#include "core/logger.hpp"

#include <SDL.h>

using namespace feasy;

SDL_Window *receive_window(const Ref<PlatformState> &state);

void Platform::create(i32 width, i32 height, const String &app_name)
{
	m_state = createRef<PlatformState>();
	m_state->width = width;
	m_state->height = height;
	m_state->name = app_name;
	m_state->handle = nullptr;

	i32 result = SDL_Init(SDL_INIT_VIDEO);

	if (result != 0)
	{
		FEASY_LOG_FATAL("Failed to initialize SDL: %s", SDL_GetError());
		return;
	}

	SDL_Window *window = SDL_CreateWindow(
		"feasy engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_state->width,
		m_state->height,
		SDL_WINDOW_VULKAN);

	if (window == nullptr)
	{
		FEASY_LOG_FATAL("Failed to initialize Window: %s", SDL_GetError());
		SDL_Quit();
		return;
	}

	m_state->handle = reinterpret_cast<void *>(window);

	if (m_state->handle == nullptr)
	{
		// FEASY_FATAL("Failed to cast SDL Window to void*");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}
}

void Platform::destroy()
{
	SDL_Window *window = receive_window(m_state);

	if (window == nullptr)
		return;

	SDL_DestroyWindow(window);
	window = nullptr;
	m_state->handle = nullptr;
	SDL_Quit();
}

SDL_Window *receive_window(const Ref<PlatformState> &state)
{
	void *handle = state->handle;
	return reinterpret_cast<SDL_Window *>(handle);
}
