cmake_minimum_required(VERSION 3.1..3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)

    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

endif()

project(Labyrinth VERSION 0.1.0
                  DESCRIPTION "A Labyrinth project"
                  LANGUAGES C)

include_directories(
    ${PROJECT_SOURCE_DIR}/../src
)

add_executable(LabExample example.c)
set_property(TARGET LabExample PROPERTY C_STANDARD 11)

target_link_libraries(LabExample PUBLIC ${PROJECT_SOURCE_DIR}/../build/libLabCUtils.a)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(LabExample PRIVATE -fprofile-arcs -ftest-coverage -fPIC -O0)
    target_link_libraries(LabExample PRIVATE -fprofile-arcs -ftest-coverage -fPIC -O0)
else()
    target_compile_options(LabExample PRIVATE -O3 -flto)
endif()