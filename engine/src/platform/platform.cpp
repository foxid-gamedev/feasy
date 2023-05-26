#include "platform.hpp"

#include "platform/vulkan/vulkan_context.hpp"

#include "core/logger.hpp"
#include <SDL.h>

using namespace feasy;

SDL_Window *receive_window(const Ref<PlatformState> &state);

void Platform::create(i32 width, i32 height, const String &app_name)
{
	FEASY_LOG_INFO("Create Platform Layer...");
	m_platformState = createRef<PlatformState>();
	m_platformState->width = width;
	m_platformState->height = height;
	m_platformState->name = app_name;
	m_platformState->handle = nullptr;

	i32 result = SDL_Init(SDL_INIT_VIDEO);

	if (result != 0)
	{
		FEASY_LOG_FATAL("Failed to initialize SDL: %s", SDL_GetError());
		return;
	}
	else
	{
		FEASY_LOG_DEBUG("Initialized SDL.");
	}

	SDL_Window *window = SDL_CreateWindow(
		"feasy engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_platformState->width,
		m_platformState->height,
		SDL_WINDOW_VULKAN);

	if (window == nullptr)
	{
		FEASY_LOG_FATAL("Failed to initialize Window: %s", SDL_GetError());
		SDL_Quit();
		return;
	}
	else
	{
		FEASY_LOG_DEBUG("Initialized SDL Window.");
	}

	m_platformState->handle = reinterpret_cast<void *>(window);

	if (m_platformState->handle == nullptr)
	{
		FEASY_LOG_FATAL("Failed to cast SDL Window to void*.");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	// TODO: refactor graphics api context creationi
	m_renderState = createRef<RenderState>();
	VulkanContext *vulkan_context = Allocator::allocate<VulkanContext>(m_platformState);
	m_renderState->contextHandle = vulkan_context;
	vulkan_context->init();
}

void Platform::destroy()
{
	Allocator::deallocate(m_renderState->contextHandle);

	SDL_Window *window = receive_window(m_platformState);

	if (window == nullptr)
		return;

	SDL_DestroyWindow(window);
	window = nullptr;
	m_platformState->handle = nullptr;
	SDL_Quit();
}

SDL_Window *receive_window(const Ref<PlatformState> &state)
{
	void *handle = state->handle;
	return reinterpret_cast<SDL_Window *>(handle);
}
