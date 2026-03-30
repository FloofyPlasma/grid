#pragma once

#include <SDL3/SDL.h>

#include "Engine/ISystem.hpp"

namespace grid
{
  class Engine;
}

namespace grid::renderer
{
  class RenderSystem : public ISystem
  {
  public:
    explicit RenderSystem(Engine &engine) : m_engine(engine) {};
    void on_start(SystemContext &context) override;
    void on_frame(SystemContext &context) override;
    void on_stop(SystemContext &context) override;
    int priority() const override { return 100; };

  private:
    Engine &m_engine;
    SDL_Window *m_window = nullptr;
  };
} // namespace grid::renderer
