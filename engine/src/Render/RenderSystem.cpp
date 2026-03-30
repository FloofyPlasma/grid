#include "Engine/Render/RenderSystem.hpp"
#include "Engine/Engine.hpp"
#include "Engine/SystemContext.hpp"

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

static void *get_native_window_handle(SDL_Window *window)
{
#if defined(SDL_PLATFORM_LINUX)
  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0)
    return SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_X11_WINDOW_NUMBER, nullptr);

  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0)
    return SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);

#elif defined(SDL_PLATFORM_WIN32)
  return SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);

#elif defined(SDL_PLATFORM_MACOS)
  return SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, nullptr);
#endif
  return nullptr;
}

static void *get_native_display_handle(SDL_Window *window)
{
#if defined(SDL_PLATFORM_LINUX)
  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0)
    return SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr);

  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0)
    return SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
#endif
  return nullptr;
}

static bgfx::NativeWindowHandleType::Enum get_native_window_handle_type()
{
#if defined(SDL_PLATFORM_LINUX)
  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0)
    return bgfx::NativeWindowHandleType::Wayland;
#endif
  return bgfx::NativeWindowHandleType::Default;
}

namespace grid::renderer
{
  void RenderSystem::on_start(SystemContext &context)
  {
    m_window = SDL_CreateWindow("Grid Engine", 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY );

    if (!m_window)
    {
      SDL_Log("Failed to create window: %s", SDL_GetError());
      m_engine.request_quit();
      return;
    }

    void *window_handle = get_native_window_handle(m_window);
    void *display_handle = get_native_display_handle(m_window);

    bgfx::PlatformData platform_data { };
    platform_data.nwh = window_handle;
    platform_data.ndt = display_handle;
    platform_data.type = get_native_window_handle_type();
    bgfx::setPlatformData(platform_data);

    bgfx::Init init { };
    init.type = bgfx::RendererType::Count;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.resolution.width = 1280;
    init.resolution.height = 720;
    init.resolution.reset = BGFX_RESET_VSYNC;
    init.platformData.nwh = get_native_window_handle(m_window);
    init.platformData.ndt = get_native_display_handle(m_window);
    init.platformData.type = get_native_window_handle_type();

    if (!bgfx::init(init))
    {
      SDL_Log("Failed to initialize BGFX");
      m_engine.request_quit();
      return;
    }

    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1a1a2eff, 1.f, 0);
    bgfx::setViewRect(0, 0, 0, 1280, 720);
  }

  void RenderSystem::on_frame(SystemContext &context)
  {
    bgfx::touch(0);
    bgfx::frame();
  }

  void RenderSystem::on_stop(SystemContext &context)
  {
    bgfx::shutdown();
    if (m_window)
    {
      SDL_DestroyWindow(m_window);
      m_window = nullptr;
    }
  }
} // namespace grid::renderer
