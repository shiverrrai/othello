# Find SDL2
find_package(SDL2 REQUIRED)

add_library(Graphics STATIC 
    screen.cpp
    board.cpp
    tile.cpp
    circle.cpp
)

# Link SDL2 and propagate include directories
target_include_directories(Graphics PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(Graphics PUBLIC ${SDL2_LIBRARIES})



