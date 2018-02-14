cmake_minimum_required(VERSION 3.0)

# test of HalfEdge structure
project(test_HalfEdge_structure LANGUAGES CXX)

add_executable(test_HEStruct test_HEStructure.cpp)

target_include_directories(test_HEStruct PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_SOURCE_DIR}/HalfEdge_structure
                           ${CMAKE_SOURCE_DIR}/kDTree_lib)

target_link_libraries(test_HEStruct HalfEdge_structure kDTree)

