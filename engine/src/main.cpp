#include "Engine/Engine.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Engine/Render/RenderSystem.hpp"

int main(int argc, char *argv[])
{
  grid::Engine engine;
  engine.register_system(std::make_unique<grid::input::InputSystem>(engine));
  engine.register_system(std::make_unique<grid::renderer::RenderSystem>(engine));
  engine.run();

  return 0;
}
