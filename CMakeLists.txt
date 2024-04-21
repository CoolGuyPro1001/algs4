cmake_minimum_required(VERSION 3.20.0)
project(algs4cpp VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_library(algs4cpp STATIC)

target_include_directories(
    algs4cpp
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_precompile_headers(algs4cpp
    PUBLIC
    pch.h
)

install(TARGETS algs4cpp
    EXPORT algs4cpp-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT algs4cpp-targets
  FILE
    JSONUtilsTargets.cmake
  NAMESPACE
    JSONUtils::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/algs4cpp
)

export(
    TARGETS
    algs4cpp
    NAMESPACE algs4cpp::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/algs4cppConfig.cmake"
)

find_package(algs4cpp)

add_executable(algs4testing
    Main.cpp
)

target_link_libraries(algs4testing
    PUBLIC
    algs4cpp::algs4cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src)