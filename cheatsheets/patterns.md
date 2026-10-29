# Patterns: Signal -> Pattern

Read the problem, spot the signal, pick the pattern. Numbers are LC problems in this repo's index.

## Arrays & Hashing
- **"Have I seen X before?" / pair summing to target, unsorted** -> Hashmap complement lookup (0001)
- **Duplicates / membership check** -> Hash set (0217)
- **Same letters, different order** -> Frequency count or sorted key (0242, 0049)
- **Top / most frequent k** -> Counting + bucket sort or heap (0347)
- **Product/sum of everything except i, no division** -> Prefix & suffix passes (0238)
- **Longest run of consecutive values, O(n)** -> Hash set, only start counting at run starts (0128)

## Two Pointers
- **Sorted array + pair/target** -> Two pointers converging (0167, 0015)
- **Palindrome check** -> Pointers from both ends (0125)
- **In-place remove/dedupe, O(1) space** -> Read/write pointers (0026, 0027)
- **Maximize area/water between bars** -> Converge, move the shorter side (0011, 0042)

## Sliding Window
- **Longest/shortest contiguous subarray/substring with a constraint** -> Variable window, grow right, shrink left (0003, 0076)
- **Fixed length k / anagram of pattern in string** -> Fixed window + counts (0567)
- **Max/min of every window of size k** -> Monotonic deque (0239)

## Stack
- **Matching brackets / nested structure** -> Stack (0020)
- **Next greater/smaller element** -> Monotonic stack (0739, 0084)
- **Evaluate expression / undo last thing** -> Operand stack (0150, 0224)

## Binary Search
- **Sorted input, find target/boundary** -> Binary search / lower bound (0704, 0035)
- **"Minimum X such that condition holds", monotonic feasibility** -> Binary search on the answer (0875)
- **Rotated sorted array** -> Find which half is sorted (0033, 0153)

## Linked List
- **Cycle / middle / nth from end** -> Fast & slow pointers (0141, 0019)
- **Head may change** -> Dummy node (0021, 0082)
- **Reverse all or part of a list** -> Iterative prev/curr/next (0206, 0092)
- **O(1) get/put with eviction order** -> Hashmap + doubly linked list (0146)

## Trees
- **Depth / height / path property** -> DFS returning a value up, global for the answer (0104, 0124)
- **Level by level / right side view** -> BFS with queue size per level (0102, 0199)
- **BST + sorted order / kth** -> Inorder traversal (0230)
- **Validate BST** -> DFS with (low, high) bounds (0098)

## Tries
- **Prefix queries / many words against one grid or stream** -> Trie (0208, 0212)

## Heap / Priority Queue
- **Kth largest/smallest, top k** -> Heap of size k (0215, 0973)
- **Running median** -> Two heaps (0295)
- **Merge k sorted things** -> Min-heap of heads (0023)

## Backtracking
- **All subsets / permutations / combinations** -> Backtracking with choose/explore/unchoose (0078, 0046, 0039)
- **Input has duplicates, unique results** -> Sort + skip `i > start && a[i] == a[i-1]` (0090, 0040)

## Graphs
- **Grid of islands / connected regions** -> DFS/BFS flood fill (0200)
- **Shortest path, unweighted** -> BFS (0127)
- **Spreads from many sources at once** -> Multi-source BFS (0994)
- **Prerequisites / ordering / cycle in directed graph** -> Topological sort (Kahn's) (0207, 0210)
- **Dynamic connectivity / redundant edge** -> Union-Find (0684)

## Advanced Graphs
- **Shortest path, non-negative weights** -> Dijkstra (0743)
- **Connect all points with min total cost** -> MST, Prim's or Kruskal's (1584)
- **Shortest path with at most k edges** -> Bellman-Ford, k+1 rounds (0787)

## 1-D DP
- **Count ways / min cost to reach step i** -> dp[i] from dp[i-1], dp[i-2] (0070, 0746)
- **Pick non-adjacent items** -> Take/skip DP (0198)
- **Min coins / can amount be formed** -> Unbounded knapsack (0322)
- **Can string be split into dictionary words** -> Prefix DP (0139)

## 2-D DP
- **Two strings, compare/align** -> dp[i][j] over prefixes (1143, 0072)
- **Paths in a grid** -> Grid DP (0062, 0064)
- **Buy/sell with states (cooldown, k txns)** -> State machine DP (0309, 0188)

## Greedy
- **Max subarray sum** -> Kadane (0053)
- **Can reach end / min jumps** -> Track farthest reach (0055, 0045)

## Intervals
- **Overlapping intervals** -> Sort by start, merge (0056)
- **Max non-overlapping / min removals / min arrows** -> Sort by end, greedy (0435, 0452)
- **Max concurrent intervals (rooms)** -> Sorted starts & ends, or min-heap of ends (0253)

## Math & Geometry
- **Matrix rotation / spiral** -> Transpose + reverse / shrinking bounds (0048, 0054)
- **x^n fast** -> Exponentiation by squaring (0050)

## Bit Manipulation
- **Every element twice except one** -> XOR all (0136)
- **Count/clear lowest set bit** -> `n & (n-1)` (0191)
