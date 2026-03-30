#pragma once

#include <splice/splice.hpp>

#include "Engine/ISystem.hpp"

namespace grid
{
  class Engine;
} // namespace grid

namespace grid::input
{
  class InputSystem : public ISystem
  {
  public:
    explicit InputSystem(Engine &engine) : m_engine(engine) { };

    void on_start(SystemContext &context) override;

    [[SPLICE_HOOKABLE]]
    void on_frame(SystemContext &context) override;

    int priority() const override { return 0; };

  private:
    Engine &m_engine;
  };
} // grid::input

SPLICE_HOOK_REGISTRY(grid::input::InputSystem, g_input);
