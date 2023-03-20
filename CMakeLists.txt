cmake_minimum_required(VERSION 3.16)
project(path_planning_visualizer)

add_executable(path_planning_visualizer src/main.cpp)

find_package(SFML COMPONENTS graphics)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
