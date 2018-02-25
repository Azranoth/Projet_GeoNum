cmake_minimum_required(VERSION 3.0)

project(test_Plane LANGUAGES CXX)


add_executable(test_Plane test_Plane.cpp)

target_include_directories(test_Plane PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/kDTree_lib
        ${CMAKE_SOURCE_DIR}/HalfEdge_structure
        ${CMAKE_SOURCE_DIR}/Plane_lib)

target_link_libraries(test_Plane HalfEdge_structure kDTree Plane)

