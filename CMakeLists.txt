cmake_minimum_required(VERSION 3.30)
project(grid CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GAME_BUILD "Editor" CACHE STRING "Build mode: Editor, Dev, or Release")
set_property(CACHE GAME_BUILD PROPERTY STRINGS Editor Dev Release)

message(STATUS "Build mode: ${GAME_BUILD}")

if(GAME_BUILD STREQUAL "Editor")
    add_compile_definitions(GRID_EDITOR GRID_HOTRELOAD)
elseif(GAME_BUILD STREQUAL "Dev")
    add_compile_definitions(GRID_HOTRELOAD)
elseif(GAME_BUILD STREQUAL "Release")
    add_compile_definitions(GRID_RELEASE)
else()
    message(FATAL_ERROR "Unknown GAME_BUILD value: ${GAME_BUILD}. Must be Editor, Dev, or Release.")
endif()

include(cmake/CPM.cmake)

CPMAddPackage("gh:libsdl-org/SDL#release-3.4.2")
CPMAddPackage("gh:bkaradzic/bgfx.cmake@1.142.9197-527")
CPMAddPackage("gh:skypjack/entt#9c5281c79a241ec810f999ad9675fa32f51f934f")
CPMAddPackage("gh:floofyplasma/splice#main")

add_subdirectory(engine)
add_subdirectory(game)

if (GAME_BUILD STREQUAL "Editor")
    add_subdirectory(editor)
endif()

add_subdirectory(compiler)