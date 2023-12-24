# CMakeList.txt : CMake project for Test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

project ("Test" C)

# Set Execution to bin folder




#Get libary
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL2)
include_directories(${SDL2_SOURCE_DIR}/include)




# Add source to this project's executable.
add_executable (Test "src/main.c" "src/mesh.h" "src/mesh.c" "src/display.h" "src/display.c" "src/vector.h" "src/vector.c" "src/triangle.h" "src/triangle.c" "src/array.h" "src/array.c") 

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/asset DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

get_filename_component(ASSET_ABSOLUTE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/asset" ABSOLUTE)


target_compile_definitions(Test PRIVATE ASSET_DIR="${ASSET_ABSOLUTE_PATH}")


target_link_libraries(Test SDL2::SDL2main SDL2::SDL2-static)
# TODO: Add tests and install targets if needed.






