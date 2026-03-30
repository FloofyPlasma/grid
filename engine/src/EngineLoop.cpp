#include "Engine/Engine.hpp"

#include <SDL3/SDL.h>

static constexpr float TICK_RATE = 1.f / 64.f;
static constexpr float MAX_ACCUMULATED = 0.25f;
static constexpr int MAX_TICKS_FRAME = 8;

namespace grid
{
  void Engine::loop()
  {
    std::uint64_t last = SDL_GetTicks();
    float accumulator = 0.f;
    std::uint64_t tick_count = 0;
    std::uint64_t frame_count = 0;
    float elapsed = 0.f;

    while (m_running)
    {
      std::uint64_t now = SDL_GetTicks();
      float delta = (now - last) / 1000.f;
      last = now;

      if (delta > MAX_ACCUMULATED)
        delta = MAX_ACCUMULATED;
      accumulator += delta;

      int ticks_this_frame = 0;
      while (accumulator >= TICK_RATE && ticks_this_frame < MAX_TICKS_FRAME)
      {
        SystemContext ctx { m_registry, TICK_RATE, elapsed, tick_count, frame_count };
        tick(ctx);
        accumulator -= TICK_RATE;
        elapsed += TICK_RATE;
        ++tick_count;
        ++ticks_this_frame;
      }

      SystemContext ctx { m_registry, delta, elapsed, tick_count, frame_count };
      frame(ctx);
      ++frame_count;
    }
  }
}
