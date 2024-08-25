cmake_minimum_required(VERSION 3.20.0)
project(algs4cpp VERSION 0.1.3 LANGUAGES C CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#add_executable(gui_test main.cpp)
#target_link_libraries(gui_test wx::net wx::core wx::base)

add_subdirectory(lib)
add_subdirectory(exec)