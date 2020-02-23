cmake_minimum_required(VERSION 3.10)
project(Viewer)

set(CMAKE_CXX_STANDARD 14)
find_package(PNG REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_XX_FLAGS} -Wall")
include_directories(${PNG_INCLUDE_DIR})

add_executable(MapViewer generationByCubitect/generator.cpp generationByCubitect/layers.cpp generationByCubitect/finders.cpp xmap.cpp main.cpp)
target_link_libraries(MapViewer ${PNG_LIBRARY})
