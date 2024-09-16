set(res ${CMAKE_SOURCE_DIR}/res)
file(
    COPY 
    ${res}/tinyAllowlist.txt 
    ${res}/tinyText.txt
    ${res}/largeAllowlist.txt
    ${res}/largeText.txt
    ${res}/tinyBatch.txt
    ${res}/m1.txt
    ${res}/m2.txt
    ${res}/m3.txt
    DESTINATION ${CMAKE_BINARY_DIR}/exec/res
)

add_executable(allow-list Fundamentals/Allowlist.cpp)
add_executable(average Fundamentals/Average.cpp)
#add_executable(cat Fundamentals/Cat.cpp)
add_executable(random-seq Fundamentals/RandomSeq.cpp)
add_executable(topm Sorting/TopM.cpp)
add_executable(multiway Sorting/Multiway.cpp)

target_link_libraries(allow-list algs4cpp)
target_link_libraries(average algs4cpp)
#target_link_libraries(cat algs4cpp)
target_link_libraries(random-seq algs4cpp)
target_link_libraries(topm algs4cpp)
target_link_libraries(multiway algs4cpp)

include(GNUInstallDirs)
install(TARGETS average random-seq
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)