add_subdirectory(graphics)
add_subdirectory(utils)
add_subdirectory(entities)

add_executable(${PROJECT_NAME} 
    main.cpp 
    game.cpp
)

target_link_libraries(${PROJECT_NAME} 
    Graphics 
    Utils 
    Entities
)
