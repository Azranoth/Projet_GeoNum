cmake_minimum_required(VERSION 3.0)

# test of VoxelGrid structure
project(test_voxelGrid LANGUAGES CXX)

add_executable(test_voxelGrid test_voxelGrid.cpp)

target_include_directories(test_voxelGrid PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_SOURCE_DIR}/HalfEdge_structure
                           ${CMAKE_SOURCE_DIR}/kDTree_lib
                           ${CMAKE_SOURCE_DIR}/Plane_lib
                           ${CMAKE_SOURCE_DIR}/PlanesGraph_lib
                           ${CMAKE_SOURCE_DIR}/VoxelGrid_lib)

target_link_libraries(test_voxelGrid voxelGrid HalfEdge_structure planesGraph Plane kDTree)

