add_library(Entities STATIC
    player.cpp
)

target_include_directories(Entities PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Entities PUBLIC 
    Graphics
)