cmake_minimum_required(VERSION 3.0)

# test of PlanesGraph structure
project(test_graph LANGUAGES CXX)

add_executable(test_graph test_graph.cpp)

target_include_directories(test_graph PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_SOURCE_DIR}/HalfEdge_structure
                           ${CMAKE_SOURCE_DIR}/kDTree_lib
                           ${CMAKE_SOURCE_DIR}/Plane_lib
                           ${CMAKE_SOURCE_DIR}/PlanesGraph_lib)

target_link_libraries(test_graph HalfEdge_structure planesGraph Plane kDTree)

