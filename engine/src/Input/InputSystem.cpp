#include "Engine/Input/InputSystem.hpp"

#include "Engine/Engine.hpp"
#include "Engine/SystemContext.hpp"

#include <SDL3/SDL.h>

namespace grid::input
{
  void InputSystem::on_start(SystemContext &context) {  }

  void InputSystem::on_frame(SystemContext &context)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
        m_engine.request_quit();
    }
  }
} // namespace grid::input