cmake_minimum_required(VERSION 3.0)

project(test_MarchingCubes LANGUAGES CXX)


add_executable(test_MarchingCubes test_marchingCubes.cpp)

target_include_directories(test_MarchingCubes PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_SOURCE_DIR}/HalfEdge_structure
                           ${CMAKE_SOURCE_DIR}/kDTree_lib
                           ${CMAKE_SOURCE_DIR}/Plane_lib
                           ${CMAKE_SOURCE_DIR}/PlanesGraph_lib
                           ${CMAKE_SOURCE_DIR}/VoxelGrid_lib
                           ${CMAKE_SOURCE_DIR}/MarchingCubes_lib
                           )

target_link_libraries(test_MarchingCubes  marchingCubes voxelGrid HalfEdge_structure kDTree Plane planesGraph )


