cmake_minimum_required(VERSION 3.0)

project(test_kDTree LANGUAGES CXX)


add_executable(test_kDTree test_kDTree.cpp)

target_include_directories(test_kDTree PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/kDTree_lib
        ${CMAKE_SOURCE_DIR}/HalfEdge_structure)

target_link_libraries(test_kDTree HalfEdge_structure kDTree)

