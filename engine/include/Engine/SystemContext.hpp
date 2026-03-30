#pragma once

#include <entt/entt.hpp>

namespace grid
{
  struct SystemContext
  {
    entt::registry &registry;
    float dt = 0.f;
    float elapsed = 0.f;
    std::uint64_t tick = 0;
    std::uint64_t frame = 0;
  };
} // namespace grid
