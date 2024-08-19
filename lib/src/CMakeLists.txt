add_subdirectory(Fundamentals)
add_subdirectory(Misc)
add_subdirectory(Searching)
add_subdirectory(Sorting)

target_sources(
    algs4cpp
    PRIVATE
    
    Helper.cpp
)