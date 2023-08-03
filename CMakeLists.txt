cmake_minimum_required(VERSION 3.5.0)
project(rogue VERSION 0.0.1 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES
    "src/*.cpp" "src/*.h"
    "src/logger/*.cpp" "src/logger/*.h"
)
add_executable(rogue ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
