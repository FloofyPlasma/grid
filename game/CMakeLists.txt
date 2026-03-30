if(GAME_BUILD STREQUAL "Release")
    add_library(game STATIC src/GamePlugin.cpp)
else()
    add_library(game SHARED src/GamePlugin.cpp)
endif()

target_include_directories(game PRIVATE ../engine/include)
target_link_libraries(game PRIVATE EnTT::EnTT)