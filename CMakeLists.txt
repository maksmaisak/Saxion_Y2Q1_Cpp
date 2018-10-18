MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list "*.h")
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

cmake_minimum_required(VERSION 3.12)
project(Saxion_Y2Q1_Cpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(Saxion_Y2Q1_Cpp ${SOURCES})

HEADER_DIRECTORIES(INCLUDES)
include_directories(${INCLUDES})

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(Saxion_Y2Q1_Cpp sfml-graphics sfml-audio)
