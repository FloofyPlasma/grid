add_executable(grid
        src/main.cpp
)

target_include_directories(grid PUBLIC include)

target_link_libraries(grid
        SDL3::SDL3
        bgfx
        EnTT::EnTT
        splice::splice
)