cmake_minimum_required(VERSION 3.5.0)
project(rogue VERSION 0.0.1 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.hpp"
)
add_executable(rogue ${SOURCES})

# I had install it with homebrew (brew install sfml). If you use another os, you will need to install it differently.
add_subdirectory(${CMAKE_SOURCE_DIR}/SFML)
include_directories(${CMAKE_SOURCE_DIR}/SFML/include)
link_directories(${CMAKE_SOURCE_DIR}/SFML/lib)

target_link_libraries(rogue sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
