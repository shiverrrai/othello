# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(utils)

# create executable
add_executable(Othello main.cpp)

# Link any libraries into executable
target_link_libraries(Othello ${SDL2_LIBRARIES})
target_link_libraries(Othello Utils)