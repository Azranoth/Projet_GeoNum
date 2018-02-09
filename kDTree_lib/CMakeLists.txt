cmake_minimum_required(VERSION 3.0)

project(kDTree LANGUAGES CXX)

file ( GLOB HEADERS *.h *.hpp)

file ( GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/HalfEdge_structure)

target_link_libraries(HalfEdge_structure)


add_subdirectory(Tests)
