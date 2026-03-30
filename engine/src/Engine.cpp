#include "Engine/Engine.hpp"
#include "Engine/Input/InputSystem.hpp"

#include <SDL3/SDL.h>
#include <algorithm>
#include <ranges>

namespace grid
{
  Engine::Engine() { SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS); }

  Engine::~Engine() { SDL_Quit(); }

  void Engine::register_system(std::unique_ptr<ISystem> system)
  {
    ISystem *raw = system.get();
    m_systems.push_back(std::move(system));
    std::stable_sort(
        m_systems.begin(), m_systems.end(), [](const auto &a, const auto &b) { return a->priority() < b->priority(); });

    SystemContext ctx { m_registry };
    raw->on_start(ctx);
  }

  void Engine::run()
  {
    m_running = true;
    loop();

    SystemContext ctx { m_registry };
    for (const auto &system: m_systems)
      system->on_stop(ctx);
  }

  void Engine::tick(SystemContext &ctx)
  {
    for (const auto &system: m_systems)
      system->on_tick(ctx);
  }

  void Engine::frame(SystemContext &ctx)
  {
    for (const auto &system: m_systems)
    {
      if (auto *input = dynamic_cast<input::InputSystem *>(system.get()))
      {
        g_input->dispatch<^^input::InputSystem::on_frame>(input, ctx);
      } else
      {
        system->on_frame(ctx);
      }
    }
  }
} // namespace grid
