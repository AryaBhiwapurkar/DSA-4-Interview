# DSA-4-Interview

Personal DSA interview revision repo. Each problem has an interview-style README plus C++, Python, and Go solutions. See [CLAUDE.md](CLAUDE.md) for conventions.

## Progress

| List | Problems | Done |
|------|---------:|-----:|
| NeetCode 150 (NC150) | 150 | 20 |
| LeetCode Top Interview 150 (TI150) | 150 | 37 |
| In both lists | 77 | 14 |
| **Unique total** | **223** | **43** |

Cheatsheets: [patterns](cheatsheets/patterns.md) · [syntax](cheatsheets/syntax.md)

## Topics

| Topic | Problems | Done |
|-------|---------:|-----:|
| [01. Arrays & Hashing](topics/01-arrays-hashing/) | 24 | 24 |
| [02. Two Pointers](topics/02-two-pointers/) | 10 | 10 |
| [03. Sliding Window](topics/03-sliding-window/) | 9 | 9 |
| [04. Stack](topics/04-stack/) | 9 | 0 |
| [05. Binary Search](topics/05-binary-search/) | 11 | 0 |
| [06. Linked List](topics/06-linked-list/) | 16 | 0 |
| [07. Trees](topics/07-trees/) | 29 | 0 |
| [08. Tries](topics/08-tries/) | 3 | 0 |
| [09. Heap / Priority Queue](topics/09-heap-priority-queue/) | 9 | 0 |
| [10. Backtracking](topics/10-backtracking/) | 11 | 0 |
| [11. Graphs](topics/11-graphs/) | 16 | 0 |
| [12. Advanced Graphs](topics/12-advanced-graphs/) | 6 | 0 |
| [13. 1-D Dynamic Programming](topics/13-1d-dp/) | 12 | 0 |
| [14. 2-D Dynamic Programming](topics/14-2d-dp/) | 17 | 0 |
| [15. Greedy](topics/15-greedy/) | 11 | 0 |
| [16. Intervals](topics/16-intervals/) | 8 | 0 |
| [17. Math & Geometry](topics/17-math-geometry/) | 12 | 0 |
| [18. Bit Manipulation](topics/18-bit-manipulation/) | 10 | 0 |

Status: ✅ done · ⬜ not added yet. Within each topic, problems are sorted Easy → Hard, then by number.

## 01. Arrays & Hashing

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0001 | [Two Sum](topics/01-arrays-hashing/0001-two-sum/) | Easy | Hashmap complement lookup | NC150, TI150 | ✅ |
| 0013 | [Roman to Integer](topics/01-arrays-hashing/0013-roman-to-integer/) | Easy | Hashmap, subtractive rule | TI150 | ✅ |
| 0014 | [Longest Common Prefix](topics/01-arrays-hashing/0014-longest-common-prefix/) | Easy | Vertical scan | TI150 | ✅ |
| 0028 | [Find the Index of the First Occurrence in a String](topics/01-arrays-hashing/0028-find-the-index-of-the-first-occurrence-in-a-string/) | Easy | String matching (KMP optional) | TI150 | ✅ |
| 0058 | [Length of Last Word](topics/01-arrays-hashing/0058-length-of-last-word/) | Easy | Reverse scan | TI150 | ✅ |
| 0169 | [Majority Element](topics/01-arrays-hashing/0169-majority-element/) | Easy | Boyer-Moore voting | TI150 | ✅ |
| 0205 | [Isomorphic Strings](topics/01-arrays-hashing/0205-isomorphic-strings/) | Easy | Two-way mapping | TI150 | ✅ |
| 0217 | [Contains Duplicate](topics/01-arrays-hashing/0217-contains-duplicate/) | Easy | Hash set | NC150 | ✅ |
| 0242 | [Valid Anagram](topics/01-arrays-hashing/0242-valid-anagram/) | Easy | Frequency count | NC150, TI150 | ✅ |
| 0290 | [Word Pattern](topics/01-arrays-hashing/0290-word-pattern/) | Easy | Two-way mapping | TI150 | ✅ |
| 0383 | [Ransom Note](topics/01-arrays-hashing/0383-ransom-note/) | Easy | Frequency count | TI150 | ✅ |
| 0006 | [Zigzag Conversion](topics/01-arrays-hashing/0006-zigzag-conversion/) | Medium | Row simulation | TI150 | ✅ |
| 0012 | [Integer to Roman](topics/01-arrays-hashing/0012-integer-to-roman/) | Medium | Greedy over value table | TI150 | ✅ |
| 0036 | [Valid Sudoku](topics/01-arrays-hashing/0036-valid-sudoku/) | Medium | Hash sets per row/col/box | NC150, TI150 | ✅ |
| 0049 | [Group Anagrams](topics/01-arrays-hashing/0049-group-anagrams/) | Medium | Hashmap with canonical key | NC150, TI150 | ✅ |
| 0128 | [Longest Consecutive Sequence](topics/01-arrays-hashing/0128-longest-consecutive-sequence/) | Medium | Hash set, start-of-run | NC150, TI150 | ✅ |
| 0151 | [Reverse Words in a String](topics/01-arrays-hashing/0151-reverse-words-in-a-string/) | Medium | Split + reverse | TI150 | ✅ |
| 0189 | [Rotate Array](topics/01-arrays-hashing/0189-rotate-array/) | Medium | Reverse in place | TI150 | ✅ |
| 0238 | [Product of Array Except Self](topics/01-arrays-hashing/0238-product-of-array-except-self/) | Medium | Prefix & suffix products | NC150, TI150 | ✅ |
| 0271 | [Encode and Decode Strings](topics/01-arrays-hashing/0271-encode-and-decode-strings/) | Medium | Length-prefix encoding | NC150 | ✅ |
| 0274 | [H-Index](topics/01-arrays-hashing/0274-h-index/) | Medium | Sort / counting | TI150 | ✅ |
| 0347 | [Top K Frequent Elements](topics/01-arrays-hashing/0347-top-k-frequent-elements/) | Medium | Bucket sort / heap | NC150 | ✅ |
| 0380 | [Insert Delete GetRandom O(1)](topics/01-arrays-hashing/0380-insert-delete-getrandom-o1/) | Medium | Hashmap + array, swap-delete | TI150 | ✅ |
| 0068 | [Text Justification](topics/01-arrays-hashing/0068-text-justification/) | Hard | Greedy line packing | TI150 | ✅ |

## 02. Two Pointers

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0026 | [Remove Duplicates from Sorted Array](topics/02-two-pointers/0026-remove-duplicates-from-sorted-array/) | Easy | Read/write pointers | TI150 | ✅ |
| 0027 | [Remove Element](topics/02-two-pointers/0027-remove-element/) | Easy | Read/write pointers | TI150 | ✅ |
| 0088 | [Merge Sorted Array](topics/02-two-pointers/0088-merge-sorted-array/) | Easy | Merge from the back | TI150 | ✅ |
| 0125 | [Valid Palindrome](topics/02-two-pointers/0125-valid-palindrome/) | Easy | Converging pointers | NC150, TI150 | ✅ |
| 0392 | [Is Subsequence](topics/02-two-pointers/0392-is-subsequence/) | Easy | Two pointers on two strings | TI150 | ✅ |
| 0011 | [Container With Most Water](topics/02-two-pointers/0011-container-with-most-water/) | Medium | Converging, move shorter side | NC150, TI150 | ✅ |
| 0015 | [3Sum](topics/02-two-pointers/0015-3sum/) | Medium | Sort + fix one + two pointers | NC150, TI150 | ✅ |
| 0080 | [Remove Duplicates from Sorted Array II](topics/02-two-pointers/0080-remove-duplicates-from-sorted-array-ii/) | Medium | Read/write, compare k back | TI150 | ✅ |
| 0167 | [Two Sum II - Input Array Is Sorted](topics/02-two-pointers/0167-two-sum-ii-input-array-is-sorted/) | Medium | Converging pointers on sorted | NC150, TI150 | ✅ |
| 0042 | [Trapping Rain Water](topics/02-two-pointers/0042-trapping-rain-water/) | Hard | Two pointers with running max | NC150, TI150 | ✅ |

## 03. Sliding Window

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0121 | [Best Time to Buy and Sell Stock](topics/03-sliding-window/0121-best-time-to-buy-and-sell-stock/) | Easy | Running min | NC150, TI150 | ✅ |
| 0219 | [Contains Duplicate II](topics/03-sliding-window/0219-contains-duplicate-ii/) | Easy | Fixed window + set | TI150 | ✅ |
| 0003 | [Longest Substring Without Repeating Characters](topics/03-sliding-window/0003-longest-substring-without-repeating-characters/) | Medium | Variable window + last-seen map | NC150, TI150 | ✅ |
| 0209 | [Minimum Size Subarray Sum](topics/03-sliding-window/0209-minimum-size-subarray-sum/) | Medium | Variable window, shrink while valid | TI150 | ✅ |
| 0424 | [Longest Repeating Character Replacement](topics/03-sliding-window/0424-longest-repeating-character-replacement/) | Medium | Variable window + max freq | NC150 | ✅ |
| 0567 | [Permutation in String](topics/03-sliding-window/0567-permutation-in-string/) | Medium | Fixed window + counts | NC150 | ✅ |
| 0030 | [Substring with Concatenation of All Words](topics/03-sliding-window/0030-substring-with-concatenation-of-all-words/) | Hard | Fixed window per offset + counts | TI150 | ✅ |
| 0076 | [Minimum Window Substring](topics/03-sliding-window/0076-minimum-window-substring/) | Hard | Variable window + need/have | NC150, TI150 | ✅ |
| 0239 | [Sliding Window Maximum](topics/03-sliding-window/0239-sliding-window-maximum/) | Hard | Monotonic deque | NC150 | ✅ |

## 04. Stack

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0020 | Valid Parentheses | Easy | Stack matching | NC150, TI150 | ⬜ |
| 0022 | Generate Parentheses | Medium | Backtracking on open/close counts | NC150, TI150 | ⬜ |
| 0071 | Simplify Path | Medium | Stack of directory names | TI150 | ⬜ |
| 0150 | Evaluate Reverse Polish Notation | Medium | Operand stack | NC150, TI150 | ⬜ |
| 0155 | Min Stack | Medium | Stack of (val, min) | NC150, TI150 | ⬜ |
| 0739 | Daily Temperatures | Medium | Monotonic decreasing stack | NC150 | ⬜ |
| 0853 | Car Fleet | Medium | Sort by position + stack of arrival times | NC150 | ⬜ |
| 0084 | Largest Rectangle in Histogram | Hard | Monotonic increasing stack | NC150 | ⬜ |
| 0224 | Basic Calculator | Hard | Stack for sign/paren context | TI150 | ⬜ |

## 05. Binary Search

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0035 | Search Insert Position | Easy | Lower bound | TI150 | ⬜ |
| 0069 | Sqrt(x) | Easy | Binary search on answer | TI150 | ⬜ |
| 0704 | Binary Search | Easy | Classic binary search | NC150 | ⬜ |
| 0033 | Search in Rotated Sorted Array | Medium | Find the sorted half | NC150, TI150 | ⬜ |
| 0034 | Find First and Last Position of Element in Sorted Array | Medium | Lower & upper bound | TI150 | ⬜ |
| 0074 | Search a 2D Matrix | Medium | Treat as flat sorted array | NC150, TI150 | ⬜ |
| 0153 | Find Minimum in Rotated Sorted Array | Medium | Compare mid with right | NC150, TI150 | ⬜ |
| 0162 | Find Peak Element | Medium | Binary search on slope | TI150 | ⬜ |
| 0875 | Koko Eating Bananas | Medium | Binary search on answer | NC150 | ⬜ |
| 0981 | Time Based Key-Value Store | Medium | Hashmap + binary search on time | NC150 | ⬜ |
| 0004 | Median of Two Sorted Arrays | Hard | Binary search on partition | NC150, TI150 | ⬜ |

## 06. Linked List

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0021 | Merge Two Sorted Lists | Easy | Dummy head merge | NC150, TI150 | ⬜ |
| 0141 | Linked List Cycle | Easy | Floyd fast/slow | NC150, TI150 | ⬜ |
| 0206 | Reverse Linked List | Easy | Iterative reversal | NC150 | ⬜ |
| 0002 | Add Two Numbers | Medium | Digit-wise add with carry | NC150, TI150 | ⬜ |
| 0019 | Remove Nth Node From End of List | Medium | Fast/slow with n gap | NC150, TI150 | ⬜ |
| 0061 | Rotate List | Medium | Close ring, cut at n-k | TI150 | ⬜ |
| 0082 | Remove Duplicates from Sorted List II | Medium | Dummy + skip duplicate runs | TI150 | ⬜ |
| 0086 | Partition List | Medium | Two dummy lists | TI150 | ⬜ |
| 0092 | Reverse Linked List II | Medium | Sublist reversal | TI150 | ⬜ |
| 0138 | Copy List with Random Pointer | Medium | Hashmap old→new / interleave | NC150, TI150 | ⬜ |
| 0143 | Reorder List | Medium | Find mid + reverse + merge | NC150 | ⬜ |
| 0146 | LRU Cache | Medium | Hashmap + doubly linked list | NC150, TI150 | ⬜ |
| 0148 | Sort List | Medium | Merge sort on list | TI150 | ⬜ |
| 0287 | Find the Duplicate Number | Medium | Floyd cycle on indices | NC150 | ⬜ |
| 0023 | Merge k Sorted Lists | Hard | Min-heap / divide & conquer | NC150, TI150 | ⬜ |
| 0025 | Reverse Nodes in k-Group | Hard | Group reversal with dummy | NC150, TI150 | ⬜ |

## 07. Trees

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0100 | Same Tree | Easy | Parallel DFS | NC150, TI150 | ⬜ |
| 0101 | Symmetric Tree | Easy | Mirror DFS | TI150 | ⬜ |
| 0104 | Maximum Depth of Binary Tree | Easy | DFS height | NC150, TI150 | ⬜ |
| 0108 | Convert Sorted Array to Binary Search Tree | Easy | Divide at middle | TI150 | ⬜ |
| 0110 | Balanced Binary Tree | Easy | DFS height with early exit | NC150 | ⬜ |
| 0112 | Path Sum | Easy | DFS with remaining sum | TI150 | ⬜ |
| 0222 | Count Complete Tree Nodes | Easy | Compare left/right heights | TI150 | ⬜ |
| 0226 | Invert Binary Tree | Easy | DFS swap children | NC150, TI150 | ⬜ |
| 0530 | Minimum Absolute Difference in BST | Easy | Inorder, track prev | TI150 | ⬜ |
| 0543 | Diameter of Binary Tree | Easy | DFS height, update global | NC150 | ⬜ |
| 0572 | Subtree of Another Tree | Easy | DFS + same-tree check | NC150 | ⬜ |
| 0637 | Average of Levels in Binary Tree | Easy | BFS by level | TI150 | ⬜ |
| 0098 | Validate Binary Search Tree | Medium | DFS with bounds | NC150, TI150 | ⬜ |
| 0102 | Binary Tree Level Order Traversal | Medium | BFS by level | NC150, TI150 | ⬜ |
| 0103 | Binary Tree Zigzag Level Order Traversal | Medium | BFS, alternate direction | TI150 | ⬜ |
| 0105 | Construct Binary Tree from Preorder and Inorder Traversal | Medium | Recursion + inorder index map | NC150, TI150 | ⬜ |
| 0106 | Construct Binary Tree from Inorder and Postorder Traversal | Medium | Recursion + inorder index map | TI150 | ⬜ |
| 0114 | Flatten Binary Tree to Linked List | Medium | Reverse preorder / Morris | TI150 | ⬜ |
| 0117 | Populating Next Right Pointers in Each Node II | Medium | Level linking with dummy | TI150 | ⬜ |
| 0129 | Sum Root to Leaf Numbers | Medium | DFS carrying the number | TI150 | ⬜ |
| 0173 | Binary Search Tree Iterator | Medium | Controlled inorder with stack | TI150 | ⬜ |
| 0199 | Binary Tree Right Side View | Medium | BFS, last per level | NC150, TI150 | ⬜ |
| 0230 | Kth Smallest Element in a BST | Medium | Inorder traversal | NC150, TI150 | ⬜ |
| 0235 | Lowest Common Ancestor of a Binary Search Tree | Medium | BST split point | NC150 | ⬜ |
| 0236 | Lowest Common Ancestor of a Binary Tree | Medium | Postorder DFS | TI150 | ⬜ |
| 0427 | Construct Quad Tree | Medium | Divide & conquer on grid | TI150 | ⬜ |
| 1448 | Count Good Nodes in Binary Tree | Medium | DFS with path max | NC150 | ⬜ |
| 0124 | Binary Tree Maximum Path Sum | Hard | DFS gain, update global | NC150, TI150 | ⬜ |
| 0297 | Serialize and Deserialize Binary Tree | Hard | Preorder with null markers | NC150 | ⬜ |

## 08. Tries

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0208 | Implement Trie (Prefix Tree) | Medium | Trie | NC150, TI150 | ⬜ |
| 0211 | Design Add and Search Words Data Structure | Medium | Trie + DFS on wildcard | NC150, TI150 | ⬜ |
| 0212 | Word Search II | Hard | Trie + grid backtracking | NC150, TI150 | ⬜ |

## 09. Heap / Priority Queue

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0703 | Kth Largest Element in a Stream | Easy | Min-heap of size k | NC150 | ⬜ |
| 1046 | Last Stone Weight | Easy | Max-heap simulation | NC150 | ⬜ |
| 0215 | Kth Largest Element in an Array | Medium | Min-heap of size k / quickselect | NC150, TI150 | ⬜ |
| 0355 | Design Twitter | Medium | Heap merge of k feeds | NC150 | ⬜ |
| 0373 | Find K Pairs with Smallest Sums | Medium | Min-heap frontier | TI150 | ⬜ |
| 0621 | Task Scheduler | Medium | Greedy counting / max-heap | NC150 | ⬜ |
| 0973 | K Closest Points to Origin | Medium | Max-heap of size k | NC150 | ⬜ |
| 0295 | Find Median from Data Stream | Hard | Two heaps | NC150, TI150 | ⬜ |
| 0502 | IPO | Hard | Sort by capital + max-heap | TI150 | ⬜ |

## 10. Backtracking

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0017 | Letter Combinations of a Phone Number | Medium | Backtrack over digit map | NC150, TI150 | ⬜ |
| 0039 | Combination Sum | Medium | Backtrack with reuse | NC150, TI150 | ⬜ |
| 0040 | Combination Sum II | Medium | Sort + skip duplicates, no reuse | NC150 | ⬜ |
| 0046 | Permutations | Medium | Backtrack with used[] | NC150, TI150 | ⬜ |
| 0077 | Combinations | Medium | Backtrack choose k | TI150 | ⬜ |
| 0078 | Subsets | Medium | Include/exclude | NC150 | ⬜ |
| 0079 | Word Search | Medium | Grid DFS backtracking | NC150, TI150 | ⬜ |
| 0090 | Subsets II | Medium | Sort + skip duplicates | NC150 | ⬜ |
| 0131 | Palindrome Partitioning | Medium | Backtrack on cut points | NC150 | ⬜ |
| 0051 | N-Queens | Hard | Backtrack with col/diag sets | NC150 | ⬜ |
| 0052 | N-Queens II | Hard | Backtrack with col/diag sets (count) | TI150 | ⬜ |

## 11. Graphs

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0130 | Surrounded Regions | Medium | DFS from border | NC150, TI150 | ⬜ |
| 0133 | Clone Graph | Medium | DFS + hashmap old→new | NC150, TI150 | ⬜ |
| 0200 | Number of Islands | Medium | Grid DFS/BFS flood fill | NC150, TI150 | ⬜ |
| 0207 | Course Schedule | Medium | Cycle detection / Kahn's | NC150, TI150 | ⬜ |
| 0210 | Course Schedule II | Medium | Topological sort | NC150, TI150 | ⬜ |
| 0261 | Graph Valid Tree | Medium | n-1 edges + connected | NC150 | ⬜ |
| 0286 | Walls and Gates | Medium | Multi-source BFS | NC150 | ⬜ |
| 0323 | Number of Connected Components in an Undirected Graph | Medium | Union-Find / DFS | NC150 | ⬜ |
| 0399 | Evaluate Division | Medium | Weighted graph DFS / weighted Union-Find | TI150 | ⬜ |
| 0417 | Pacific Atlantic Water Flow | Medium | Reverse DFS from both oceans | NC150 | ⬜ |
| 0433 | Minimum Genetic Mutation | Medium | BFS over strings | TI150 | ⬜ |
| 0684 | Redundant Connection | Medium | Union-Find | NC150 | ⬜ |
| 0695 | Max Area of Island | Medium | Grid DFS | NC150 | ⬜ |
| 0909 | Snakes and Ladders | Medium | BFS on board | TI150 | ⬜ |
| 0994 | Rotting Oranges | Medium | Multi-source BFS | NC150 | ⬜ |
| 0127 | Word Ladder | Hard | BFS with wildcard buckets | NC150, TI150 | ⬜ |

## 12. Advanced Graphs

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0743 | Network Delay Time | Medium | Dijkstra | NC150 | ⬜ |
| 0787 | Cheapest Flights Within K Stops | Medium | Bellman-Ford, k+1 rounds | NC150 | ⬜ |
| 1584 | Min Cost to Connect All Points | Medium | MST (Prim's) | NC150 | ⬜ |
| 0269 | Alien Dictionary | Hard | Topological sort on chars | NC150 | ⬜ |
| 0332 | Reconstruct Itinerary | Hard | Hierholzer (Eulerian path) | NC150 | ⬜ |
| 0778 | Swim in Rising Water | Hard | Dijkstra on max edge | NC150 | ⬜ |

## 13. 1-D Dynamic Programming

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0070 | Climbing Stairs | Easy | Fibonacci DP | NC150, TI150 | ⬜ |
| 0746 | Min Cost Climbing Stairs | Easy | Linear DP | NC150 | ⬜ |
| 0005 | Longest Palindromic Substring | Medium | Expand around center | NC150, TI150 | ⬜ |
| 0091 | Decode Ways | Medium | Linear DP on 1/2 digits | NC150 | ⬜ |
| 0139 | Word Break | Medium | Prefix DP + dictionary | NC150, TI150 | ⬜ |
| 0152 | Maximum Product Subarray | Medium | Track max & min | NC150 | ⬜ |
| 0198 | House Robber | Medium | Take/skip DP | NC150, TI150 | ⬜ |
| 0213 | House Robber II | Medium | Two passes of House Robber | NC150 | ⬜ |
| 0300 | Longest Increasing Subsequence | Medium | DP / patience sort + binary search | NC150, TI150 | ⬜ |
| 0322 | Coin Change | Medium | Unbounded knapsack (min) | NC150, TI150 | ⬜ |
| 0416 | Partition Equal Subset Sum | Medium | 0/1 knapsack subset sum | NC150 | ⬜ |
| 0647 | Palindromic Substrings | Medium | Expand around center | NC150 | ⬜ |

## 14. 2-D Dynamic Programming

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0062 | Unique Paths | Medium | Grid DP | NC150 | ⬜ |
| 0063 | Unique Paths II | Medium | Grid DP with obstacles | TI150 | ⬜ |
| 0064 | Minimum Path Sum | Medium | Grid DP | TI150 | ⬜ |
| 0072 | Edit Distance | Medium | Two-string DP | NC150, TI150 | ⬜ |
| 0097 | Interleaving String | Medium | Two-string DP | NC150, TI150 | ⬜ |
| 0120 | Triangle | Medium | Bottom-up DP | TI150 | ⬜ |
| 0221 | Maximal Square | Medium | Grid DP, min of 3 neighbors | TI150 | ⬜ |
| 0309 | Best Time to Buy and Sell Stock with Cooldown | Medium | State machine DP | NC150 | ⬜ |
| 0494 | Target Sum | Medium | Subset-sum DP / memo | NC150 | ⬜ |
| 0518 | Coin Change II | Medium | Unbounded knapsack (count) | NC150 | ⬜ |
| 1143 | Longest Common Subsequence | Medium | Two-string DP | NC150 | ⬜ |
| 0010 | Regular Expression Matching | Hard | Two-string DP with star | NC150 | ⬜ |
| 0115 | Distinct Subsequences | Hard | Two-string DP | NC150 | ⬜ |
| 0123 | Best Time to Buy and Sell Stock III | Hard | State machine DP (2 txns) | TI150 | ⬜ |
| 0188 | Best Time to Buy and Sell Stock IV | Hard | State machine DP (k txns) | TI150 | ⬜ |
| 0312 | Burst Balloons | Hard | Interval DP (last to burst) | NC150 | ⬜ |
| 0329 | Longest Increasing Path in a Matrix | Hard | DFS + memo | NC150 | ⬜ |

## 15. Greedy

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0045 | Jump Game II | Medium | BFS-style level greedy | NC150, TI150 | ⬜ |
| 0053 | Maximum Subarray | Medium | Kadane | NC150, TI150 | ⬜ |
| 0055 | Jump Game | Medium | Track farthest reach | NC150, TI150 | ⬜ |
| 0122 | Best Time to Buy and Sell Stock II | Medium | Sum positive deltas | TI150 | ⬜ |
| 0134 | Gas Station | Medium | Reset start on negative tank | NC150, TI150 | ⬜ |
| 0678 | Valid Parenthesis String | Medium | Track min/max open count | NC150 | ⬜ |
| 0763 | Partition Labels | Medium | Last occurrence + window end | NC150 | ⬜ |
| 0846 | Hand of Straights | Medium | Sorted counts, build from min | NC150 | ⬜ |
| 0918 | Maximum Sum Circular Subarray | Medium | Kadane on max & min | TI150 | ⬜ |
| 1899 | Merge Triplets to Form Target Triplet | Medium | Filter valid triplets | NC150 | ⬜ |
| 0135 | Candy | Hard | Two passes L→R, R→L | TI150 | ⬜ |

## 16. Intervals

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0228 | Summary Ranges | Easy | Linear scan of runs | TI150 | ⬜ |
| 0252 | Meeting Rooms | Easy | Sort + check overlap | NC150 | ⬜ |
| 0056 | Merge Intervals | Medium | Sort by start + merge | NC150, TI150 | ⬜ |
| 0057 | Insert Interval | Medium | Merge on the fly | NC150, TI150 | ⬜ |
| 0253 | Meeting Rooms II | Medium | Sorted starts/ends or min-heap | NC150 | ⬜ |
| 0435 | Non-overlapping Intervals | Medium | Sort by end, greedy | NC150 | ⬜ |
| 0452 | Minimum Number of Arrows to Burst Balloons | Medium | Sort by end, greedy | TI150 | ⬜ |
| 1851 | Minimum Interval to Include Each Query | Hard | Sort queries + min-heap | NC150 | ⬜ |

## 17. Math & Geometry

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0009 | Palindrome Number | Easy | Reverse half the number | TI150 | ⬜ |
| 0066 | Plus One | Easy | Carry from the end | NC150, TI150 | ⬜ |
| 0202 | Happy Number | Easy | Cycle detection (fast/slow) | NC150, TI150 | ⬜ |
| 0043 | Multiply Strings | Medium | Grade-school multiplication | NC150 | ⬜ |
| 0048 | Rotate Image | Medium | Transpose + reverse rows | NC150, TI150 | ⬜ |
| 0050 | Pow(x, n) | Medium | Fast exponentiation | NC150, TI150 | ⬜ |
| 0054 | Spiral Matrix | Medium | Shrinking boundaries | NC150, TI150 | ⬜ |
| 0073 | Set Matrix Zeroes | Medium | First row/col as markers | NC150, TI150 | ⬜ |
| 0172 | Factorial Trailing Zeroes | Medium | Count factors of 5 | TI150 | ⬜ |
| 0289 | Game of Life | Medium | In-place state encoding | TI150 | ⬜ |
| 2013 | Detect Squares | Medium | Point counts + diagonal | NC150 | ⬜ |
| 0149 | Max Points on a Line | Hard | Slope hashmap (gcd) | TI150 | ⬜ |

## 18. Bit Manipulation

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0067 | Add Binary | Easy | Carry addition | TI150 | ⬜ |
| 0136 | Single Number | Easy | XOR | NC150, TI150 | ⬜ |
| 0190 | Reverse Bits | Easy | Shift and build | NC150, TI150 | ⬜ |
| 0191 | Number of 1 Bits | Easy | n & (n-1) | NC150, TI150 | ⬜ |
| 0268 | Missing Number | Easy | XOR / sum formula | NC150 | ⬜ |
| 0338 | Counting Bits | Easy | DP on bits | NC150 | ⬜ |
| 0007 | Reverse Integer | Medium | Digit pop with overflow check | NC150 | ⬜ |
| 0137 | Single Number II | Medium | Bit counting mod 3 | TI150 | ⬜ |
| 0201 | Bitwise AND of Numbers Range | Medium | Common prefix | TI150 | ⬜ |
| 0371 | Sum of Two Integers | Medium | XOR + carry | NC150 | ⬜ |
