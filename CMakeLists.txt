cmake_minimum_required(VERSION 3.0)
project(GeometrieNumerique LANGUAGES C CXX)

if(MSVC)
  add_definitions("-D_USE_MATH_DEFINES")
else()
  add_compile_options(-std=c++14 -Wall)
endif()

file ( GLOB HEADERS *.h *.hpp)

file ( GLOB SOURCES *.cpp)

#add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/HalfEdge_structure
#                    ${CMAKE_SOURCE_DIR}/kDTree_lib)
#target_link_libraries(HalfEdge_structure
#                      kDTree)

target_link_libraries(${PROJECT_NAME}
                        HalfEdge_structure
                     )

add_subdirectory(HalfEdge_structure)
add_subdirectory(kDTree_lib)

