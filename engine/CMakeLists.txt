add_executable(grid
        src/Engine.cpp
        src/EngineLoop.cpp
        src/main.cpp
        src/Render/RenderSystem.cpp
        src/Input/InputSystem.cpp
)

target_include_directories(grid PUBLIC include)

target_link_libraries(grid
        SDL3::SDL3
        bgfx
        EnTT::EnTT
        splice::splice
)