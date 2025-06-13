cmake_minimum_required(VERSION 3.8)

project(CEngine LANGUAGES C) # Explicitly set the language to C

# Set C standard globally (optional)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set(CMAKE_C_STANDARD 11)
endif()

# Include FetchContent module
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

# Add the executable directly
add_executable(CEngine "source/main.c" "source/renderer.c" "source/grid.c" "source/simulation.c" "source/util.c")

# Link raylib to your executable
target_link_libraries(CEngine PRIVATE raylib)

# Add the include folder for header files
target_include_directories(CEngine PRIVATE "${CMAKE_SOURCE_DIR}/include")
