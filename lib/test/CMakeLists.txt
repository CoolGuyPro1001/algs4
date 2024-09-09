include(CTest)
enable_testing()

set(res ${CMAKE_SOURCE_DIR}/res)

file(STRINGS "algs4test-sources.txt" test_sources)
file(COPY ${res} DESTINATION ${CMAKE_BINARY_DIR}/lib/test)

create_test_sourcelist(source_list Algs4CppTests.cpp ${test_sources})
add_executable(algs4cpp-tests ${source_list})
target_link_libraries(algs4cpp-tests algs4cpp)


# Add all the ADD_TEST for each test
#foreach (i RANGE ${num_tests})
#    add_executable(algs4cpp-tests ${test_name})
#    add_test(NAME ${test_name} COMMAND algs4cpp-tests ${test_name} ${test_args})
#endforeach()