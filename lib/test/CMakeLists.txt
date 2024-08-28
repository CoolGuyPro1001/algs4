include(CTest)
enable_testing()

set(test_sources
  Fundamentals/TestAccumulator.cpp
  Fundamentals/TestBag.cpp 
  #Fundamentals/TestBinarySearch.cpp 
  Fundamentals/TestCounter.cpp
  Fundamentals/TestDate.cpp
  #Fundamentals/TestDoublingRatio.cpp
  Fundamentals/TestDoublingTest.cpp
  Fundamentals/TestInterval1D.cpp
  Fundamentals/TestInterval2D.cpp
  Fundamentals/TestKnuth.cpp 
  Fundamentals/TestLinkedStack.cpp
  #Fundamentals/TestPoint2D.cpp 
  Fundamentals/TestQuickFindUF.cpp
  Fundamentals/TestQuickUnionUF.cpp
  #Fundamentals/ResizingArrayStack.cpp 
  #Fundamentals/TestStack.cpp
  Fundamentals/TestStopwatch.cpp
  Fundamentals/TestStopwatchCPU.cpp
  Fundamentals/TestTransaction.cpp
  Fundamentals/TestUF.cpp
  #Fundamentals/TestThreeSum.cpp
  #Fundamentals/TestThreeSumFast.cpp
  Fundamentals/TestVector.cpp
  Fundamentals/TestWeightedQuickUnionUF.cpp

  #Misc/TestStdDraw.cpp
  Misc/TestStdIn.cpp
  Misc/TestStdOut.cpp
  Misc/TestStdRandom.cpp

  Sorting/TestBinaryInsertion.cpp
  Sorting/TestHeap.cpp
  Sorting/TestInsertion.cpp
  Sorting/TestInsertionX.cpp
  Sorting/TestMerge.cpp
  Sorting/TestMergeBU.cpp
  Sorting/TestMergeX.cpp
  Sorting/TestQuick.cpp
  Sorting/TestQuick3way.cpp
  Sorting/TestQuickBentleyMcIlroy.cpp
  Sorting/TestQuickX.cpp
  Sorting/TestSelection.cpp
  Sorting/TestShell.cpp
)

create_test_sourcelist(tests Algs4CppTests.cpp ${test_sources})
add_executable(algs4cpp-tests ${tests})
target_link_libraries(algs4cpp-tests algs4cpp)

# Add all the ADD_TEST for each test
foreach (test ${test_sources})
  get_filename_component(test_name ${test} NAME_WE)
  add_test(NAME ${test_name} COMMAND algs4cpp-tests ${test_name})
endforeach()