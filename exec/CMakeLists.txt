#add_executable(allow-list Fundamentals/Allowlist.cpp)
add_executable(average Fundamentals/Average.cpp)
#add_executable(cat Fundamentals/Cat.cpp)
add_executable(random-seq Fundamentals/RandomSeq.cpp)

#target_link_libraries(allow-list algs4cpp)
target_link_libraries(average algs4cpp)
#target_link_libraries(cat algs4cpp)
target_link_libraries(random-seq algs4cpp)

include(GNUInstallDirs)
install(TARGETS average random-seq
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)