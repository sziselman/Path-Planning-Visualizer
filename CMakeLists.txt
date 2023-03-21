cmake_minimum_required(VERSION 3.16)
project(path_planning_visualizer VERSION 1.0.1 DESCRIPTION "path planning visualizer")

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(visualizer SHARED
    src/visualizer.cpp
)

add_library(grid SHARED
    src/grid.cpp
)

# add_library(grid SHARED
#     src/grid.cpp
# )
    
target_include_directories(visualizer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(grid PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(SFML COMPONENTS graphics)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    visualizer 
    grid
    ${SFML_LIBRARIES} 
    sfml-graphics)