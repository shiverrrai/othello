# Find SDL2
find_package(SDL2 REQUIRED)

add_library(Utils STATIC 
    input.cpp
)

# Link SDL2 and propagate include directories
target_include_directories(Utils PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(Utils PUBLIC ${SDL2_LIBRARIES})
