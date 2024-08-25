add_library(algs4cpp)

target_compile_features(algs4cpp PUBLIC cxx_std_20)

target_compile_options(
    algs4cpp
    PUBLIC
    -Wno-unused-value
    -Wno-comment
)

target_include_directories(
    algs4cpp
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/include/algs4cpp>
)

target_precompile_headers(algs4cpp
    PUBLIC
    pch.h
)

#add_subdirectory(wxWidgets-3.2.5)
#target_link_libraries(algs4cpp wx::net wx::core wx::base)

include(GNUInstallDirs)

install(TARGETS algs4cpp
    EXPORT algs4cpp-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT algs4cpp-targets
    FILE algs4cppTargets.cmake
    NAMESPACE algs4cpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/algs4cpp
)

install(DIRECTORY include/algs4cpp/
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/algs4cpp 
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/algs4cppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/algs4cppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/algs4cppConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/algs4cpp 
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/algs4cppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/algs4cppConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDR}/cmake/algs4cpp
)

export(
    EXPORT algs4cpp-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/algs4cppTargets.cmake"
    NAMESPACE algs4cpp::
)

export(PACKAGE algs4cpp)


add_subdirectory(src)
add_subdirectory(test)