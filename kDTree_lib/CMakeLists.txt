cmake_minimum_required(VERSION 3.0)

project(kDTree LANGUAGES CXX)

file ( GLOB HEADERS *.h *.hpp)

file ( GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_SOURCE_DIR}/Plane_lib
                           ${CMAKE_SOURCE_DIR}/HalfEdge_structure
                           ${CMAKE_SOURCE_DIR}/kDTree_lib)

add_subdirectory(Tests)
