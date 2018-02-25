cmake_minimum_required(VERSION 3.0)
project(GeometrieNumerique LANGUAGES C CXX)

if(MSVC)
  add_definitions("-D_USE_MATH_DEFINES")
else()
  add_compile_options(-std=c++14 -Wall -I ${CMAKE_CURRENT_SOURCE_DIR}/Eigen/ -I${CMAKE_CURRENT_SOURCE_DIR}/Boost)
endif()

file ( GLOB HEADERS *.h *.hpp)

file ( GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/HalfEdge_structure
                           ${CMAKE_CURRENT_SOURCE_DIR}/kDTree_lib
                           ${CMAKE_CURRENT_SOURCE_DIR}/Plane_lib
                           ${CMAKE_CURRENT_SOURCE_DIR}/PlanesGraph_lib
                           ${CMAKE_CURRENT_SOURCE_DIR}/VoxelGrid_lib)

target_link_libraries(${PROJECT_NAME}
                        HalfEdge_structure
                        kDTree
                        Plane
                        planesGraph
                        voxelGrid
                     )

add_subdirectory(PlanesGraph_lib)
add_subdirectory(Plane_lib)
add_subdirectory(VoxelGrid_lib)
add_subdirectory(HalfEdge_structure)
add_subdirectory(kDTree_lib)

