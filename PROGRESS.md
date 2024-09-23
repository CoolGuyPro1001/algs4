## Key
* C - Completely implemented
* R - Redundant
* I - Incomplete or commented out code
* M - Missing unit testing main 
* B - Has bugs or vulnerability
* N - Not implemented
* W - Doesn't work in Windows
* U - Doesn't work in Linux/Mac/Unix

## Redudant Classes
Some classes are not implemented due to having near identical code as other classes. 
This is because of the differences between C++ and Java.
Some features from the redudant class are moved into the other class.

For example, in the original algs4 library the only difference between Bag and LinkedBag is
Bag's Node class is static while LinkedBag's Node isn't. C++ doesn't have static classes,
and creating a new Node struct with static data has no benefit.
Only the Bag class is needed to represent a multiset implemented by a linked list. 

## List
| Fundamentals | Status |
| :---------: | :---------: |
| BinarySearch | C |
| RandomSeq | C |
| Average | C |
| Cat | M |
| Knuth | C |
| Counter | C |
| StaticSETofInts | C |
| Allowlist | C |
| Vector | C |
| Date | C |
| Transaction | C |
| Point2D | MI |
| RectHV | I |
| Interval1D | C |
| Interval2D | MI |
| Accumulator | C |
| ResizingArrayStack | C |
| LinkedStack | R |
| Stack | C |
| ResizingArrayQueue | C |
| LinkedQueue | R |
| Queue | C |
| ResizingArrayBag | C |
| LinkedBag | R |
| Bag | C |
| Stopwatch | C |
| StopwatchCPU | W |
| LinearRegression | C |
| ThreeSum | C |
| ThreeSumFast | C |
| DoublingTest | C |
| DoublingRatio | C |
| QuickFindUF | C |
| QuickUnionUF | C |
| WeightedQuickUnionUF | C |
| UF | C |

| Sorting | Status |
| :---------: | :---------: |
| Insertion | C |
| InsertionX | C |
| BinaryInsertion | C |
| Selection | C |
| Shell | C |
| Merge | C |
| MergeBU | C |
| MergeX | C |
| Inversions | C |
| Quick | C |
| Quick3way | C |
| QuickX | C |
| QuickBentleyMcllroy | C |
| TopM | C |
| MaxPQ | C |
| MinPQ | C |
| IndexMinPQ | C |
| IndexMaxPQ | C |
| Multiway | C |
| Heap | C |

| Searching | Status |
| :---------: | :---------: |
| FrequencyCounter | N |
| SequentialSearchST | N |
| BinarySearchST | N |
| BST | N |
| RedBlackBST | N |
| SeperateChainingHashST | N |
| LinearProbingHashST | N |
| ST | MI |
| SET | N |
| DeDup | N |
| AllowFilter | N |
| BlockFilter | N |
| LookupCSV | N |
| LookupIndex | N |
| FileIndex | N |
| SparseVector | N |

| Graphs | Status |
| :---------: | :---------: |
| Graph | N |
| GraphGenerator | N |
| DepthFirstSearch | N |
| NonrecursiveDFS | N |
| DepthFirstPaths | N |
| BreadthFirstPaths | N |
| CC | N |
| Bipartite | N |
| BipartiteX | N |
| Cycle | N |
| EulerianCycle | N |
| EulerianPath | N |
| SymbolGraph | N |
| DegreesOfSeperation | N |
| Digraph | N |
| DigraphGenerator | N |
| DirectedDFS | N |
| NonrecursiveDirectedDFS | N |
| DepthFirstDirectedPaths | N |
| BreadthFirstDirectedPaths | N |
| DirectedCycle | N |
| DirectedCycleX | N |
| DirectedEulerianCycle | N |
| DirectedEulerianPath | N |
| DepthFirstOrder | N |
| Topological | N |
| TopologicalX | N |
| TransitiveClosure | N |
| SymbolDigraph | N |
| KosarajuSharirSCC | N |
| TarjanSCC | N |
| GabowSCC | N |
| EdgeWeightedGraph | N |
| LazyPrimMST | N |
| PrimMST | N |
| KruskalMST | N |
| BoruvkaMST | N |
| EdgeWeightedDigraph | N |
| DirectedEdge | N |
| DijkstraSP | N |
| DijkstraUndirectedSP | N |
| DijkstraAllPairsSP | N |
| AcyclicSP | N |
| AcyclicLP | N |
| CPM | N |
| BellmanFordSP | N |
| EdgeWeightedDirectedCycle | N |
| Arbitrage | N |
| FloydWarshall | N |
| AdjMatrixEdgeWeightedDigraph | N |

| String | Status |
| :---------: | :---------: |
| Alphabet | N |
| Count | N |
| LSD | N |
| MSD | N |
| ImplaceMSD | N |
| Quick3string | N |
| AmericanFlag | N |
| AmericanFlagX | N |
| TrieST | N |
| TrieSET | N |
| TST | N |
| KMP | N |
| BoyerMoore | N |
| RabinKarp | N |
| NFA | N |
| GREP | N |
| BinaryDump | N |
| HexDump | N |
| PictureDump | N |
| Genome | N |
| RunLength | N |
| Huffman | N |
| LZW | N |

| Context | Status |
| :---------: | :---------: |
| CollisionSystem | N |
| Particle | N |
| BTree | N |
| SuffixArray | N |
| SuffixArrayX | N |
| LongestRepeatedSubstring | N |
| KWIK | N |
| LongestCommonSubstring | N |
| FordFulkerson | N |
| FlowNetwork | N |
| FlowEdge | N |
| GlobalMincut | N |
| BipartiteMatching | N |
| HopcroftKarp | N |
| AssignmentProblem | N |
| LinearProgramming | N |
| TwoPersonZeroSumGame | N |

| Beyond | Status |
| :---------: | :---------: |
| GaussianElimination | N |
| GaussJordanElimination | N |
| FFT | N |
| Complex | N |
| Polynomial | N |
| GrahamScan | N |
| FarthestPair | N |
| ClosestPair | N |
| FerwickTree | N |
| SegmentTree | N |
| PatriciaST | N |
| PatriciaSET | N |
| MultiwayMinPQ | N |
| IndexMultiwayMinPQ | N |
| BinomialMinPQ | N |
| IndexBinomialMinPQ | N |
| FibonacciMinPQ | N |
| IndexFibonacciMinPQ | N |
| AVLTreeST | N |

| Standard IO | Status |
| :---------: | :---------: |
| StdIn | C |
| StdOUt | C |
| StdDraw | N |
| StdAudio | N |
| StdRandom | C |
| StdStats | N |
| StdArrayIO | N |
| StdPicture | N |
| In | I |
| Out | N |
| Draw | N |
| DrawListener | N |
| Picture | N |
| GrayscalePicture | N |
| BinaryStdin | N |
| BinaryStdOut | N |
| BinaryIn | N |
| BinaryOut | N |1