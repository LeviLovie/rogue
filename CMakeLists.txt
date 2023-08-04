cmake_minimum_required(VERSION 3.5.0)
project(rogue VERSION 0.0.1 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES
    "src/*.cpp" "src/*.h"
)
add_executable(rogue ${SOURCES})

# I had install it with homebrew (brew install sfml). If you use another os, you will need to install it differently.
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(rogue sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
