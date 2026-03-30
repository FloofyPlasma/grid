#pragma once

#include <memory>
#include <vector>

#include "ISystem.hpp"
#include "SystemContext.hpp"

namespace grid
{
  class Engine
  {
  public:
    Engine();
    ~Engine();

    void register_system(std::unique_ptr<ISystem> system);
    void request_quit() { m_running = false; }
    void run();

  private:
    void loop();
    void tick(SystemContext &ctx);
    void frame(SystemContext &ctx);

    entt::registry m_registry;
    std::vector<std::unique_ptr<ISystem>> m_systems;
    bool m_running = false;
  };
} // namespace grid
