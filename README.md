# DSA-4-Interview

Personal DSA interview revision repo. Each problem has an interview-style README plus C++, Python, and Go solutions. See [CLAUDE.md](CLAUDE.md) for conventions.

## Progress

| List | Problems | Done |
|------|---------:|-----:|
| NeetCode 150 (NC150) | 150 | 110 |
| LeetCode Top Interview 150 (TI150) | 150 | 115 |
| In both lists | 77 | 60 |
| **Unique total** | **223** | **165** |

Cheatsheets: [patterns](cheatsheets/patterns.md) · [syntax](cheatsheets/syntax.md)

## Topics

| Topic | Problems | Done |
|-------|---------:|-----:|
| [01. Arrays & Hashing](topics/01-arrays-hashing/) | 24 | 24 |
| [02. Two Pointers](topics/02-two-pointers/) | 10 | 10 |
| [03. Sliding Window](topics/03-sliding-window/) | 9 | 9 |
| [04. Stack](topics/04-stack/) | 9 | 9 |
| [05. Binary Search](topics/05-binary-search/) | 11 | 11 |
| [06. Linked List](topics/06-linked-list/) | 16 | 16 |
| [07. Trees](topics/07-trees/) | 29 | 29 |
| [08. Tries](topics/08-tries/) | 3 | 3 |
| [09. Heap / Priority Queue](topics/09-heap-priority-queue/) | 9 | 9 |
| [10. Backtracking](topics/10-backtracking/) | 11 | 11 |
| [11. Graphs](topics/11-graphs/) | 16 | 16 |
| [12. Advanced Graphs](topics/12-advanced-graphs/) | 6 | 6 |
| [13. 1-D Dynamic Programming](topics/13-1d-dp/) | 12 | 12 |
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
| 0020 | [Valid Parentheses](topics/04-stack/0020-valid-parentheses/) | Easy | Stack matching | NC150, TI150 | ✅ |
| 0022 | [Generate Parentheses](topics/04-stack/0022-generate-parentheses/) | Medium | Backtracking on open/close counts | NC150, TI150 | ✅ |
| 0071 | [Simplify Path](topics/04-stack/0071-simplify-path/) | Medium | Stack of directory names | TI150 | ✅ |
| 0150 | [Evaluate Reverse Polish Notation](topics/04-stack/0150-evaluate-reverse-polish-notation/) | Medium | Operand stack | NC150, TI150 | ✅ |
| 0155 | [Min Stack](topics/04-stack/0155-min-stack/) | Medium | Stack of (val, min) | NC150, TI150 | ✅ |
| 0739 | [Daily Temperatures](topics/04-stack/0739-daily-temperatures/) | Medium | Monotonic decreasing stack | NC150 | ✅ |
| 0853 | [Car Fleet](topics/04-stack/0853-car-fleet/) | Medium | Sort by position + stack of arrival times | NC150 | ✅ |
| 0084 | [Largest Rectangle in Histogram](topics/04-stack/0084-largest-rectangle-in-histogram/) | Hard | Monotonic increasing stack | NC150 | ✅ |
| 0224 | [Basic Calculator](topics/04-stack/0224-basic-calculator/) | Hard | Stack for sign/paren context | TI150 | ✅ |

## 05. Binary Search

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0035 | [Search Insert Position](topics/05-binary-search/0035-search-insert-position/) | Easy | Lower bound | TI150 | ✅ |
| 0069 | [Sqrt(x)](topics/05-binary-search/0069-sqrtx/) | Easy | Binary search on answer | TI150 | ✅ |
| 0704 | [Binary Search](topics/05-binary-search/0704-binary-search/) | Easy | Classic binary search | NC150 | ✅ |
| 0033 | [Search in Rotated Sorted Array](topics/05-binary-search/0033-search-in-rotated-sorted-array/) | Medium | Find the sorted half | NC150, TI150 | ✅ |
| 0034 | [Find First and Last Position of Element in Sorted Array](topics/05-binary-search/0034-find-first-and-last-position-of-element-in-sorted-array/) | Medium | Lower & upper bound | TI150 | ✅ |
| 0074 | [Search a 2D Matrix](topics/05-binary-search/0074-search-a-2d-matrix/) | Medium | Treat as flat sorted array | NC150, TI150 | ✅ |
| 0153 | [Find Minimum in Rotated Sorted Array](topics/05-binary-search/0153-find-minimum-in-rotated-sorted-array/) | Medium | Compare mid with right | NC150, TI150 | ✅ |
| 0162 | [Find Peak Element](topics/05-binary-search/0162-find-peak-element/) | Medium | Binary search on slope | TI150 | ✅ |
| 0875 | [Koko Eating Bananas](topics/05-binary-search/0875-koko-eating-bananas/) | Medium | Binary search on answer | NC150 | ✅ |
| 0981 | [Time Based Key-Value Store](topics/05-binary-search/0981-time-based-key-value-store/) | Medium | Hashmap + binary search on time | NC150 | ✅ |
| 0004 | [Median of Two Sorted Arrays](topics/05-binary-search/0004-median-of-two-sorted-arrays/) | Hard | Binary search on partition | NC150, TI150 | ✅ |

## 06. Linked List

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0021 | [Merge Two Sorted Lists](topics/06-linked-list/0021-merge-two-sorted-lists/) | Easy | Dummy head merge | NC150, TI150 | ✅ |
| 0141 | [Linked List Cycle](topics/06-linked-list/0141-linked-list-cycle/) | Easy | Floyd fast/slow | NC150, TI150 | ✅ |
| 0206 | [Reverse Linked List](topics/06-linked-list/0206-reverse-linked-list/) | Easy | Iterative reversal | NC150 | ✅ |
| 0002 | [Add Two Numbers](topics/06-linked-list/0002-add-two-numbers/) | Medium | Digit-wise add with carry | NC150, TI150 | ✅ |
| 0019 | [Remove Nth Node From End of List](topics/06-linked-list/0019-remove-nth-node-from-end-of-list/) | Medium | Fast/slow with n gap | NC150, TI150 | ✅ |
| 0061 | [Rotate List](topics/06-linked-list/0061-rotate-list/) | Medium | Close ring, cut at n-k | TI150 | ✅ |
| 0082 | [Remove Duplicates from Sorted List II](topics/06-linked-list/0082-remove-duplicates-from-sorted-list-ii/) | Medium | Dummy + skip duplicate runs | TI150 | ✅ |
| 0086 | [Partition List](topics/06-linked-list/0086-partition-list/) | Medium | Two dummy lists | TI150 | ✅ |
| 0092 | [Reverse Linked List II](topics/06-linked-list/0092-reverse-linked-list-ii/) | Medium | Sublist reversal | TI150 | ✅ |
| 0138 | [Copy List with Random Pointer](topics/06-linked-list/0138-copy-list-with-random-pointer/) | Medium | Hashmap old→new / interleave | NC150, TI150 | ✅ |
| 0143 | [Reorder List](topics/06-linked-list/0143-reorder-list/) | Medium | Find mid + reverse + merge | NC150 | ✅ |
| 0146 | [LRU Cache](topics/06-linked-list/0146-lru-cache/) | Medium | Hashmap + doubly linked list | NC150, TI150 | ✅ |
| 0148 | [Sort List](topics/06-linked-list/0148-sort-list/) | Medium | Merge sort on list | TI150 | ✅ |
| 0287 | [Find the Duplicate Number](topics/06-linked-list/0287-find-the-duplicate-number/) | Medium | Floyd cycle on indices | NC150 | ✅ |
| 0023 | [Merge k Sorted Lists](topics/06-linked-list/0023-merge-k-sorted-lists/) | Hard | Min-heap / divide & conquer | NC150, TI150 | ✅ |
| 0025 | [Reverse Nodes in k-Group](topics/06-linked-list/0025-reverse-nodes-in-k-group/) | Hard | Group reversal with dummy | NC150, TI150 | ✅ |

## 07. Trees

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0100 | [Same Tree](topics/07-trees/0100-same-tree/) | Easy | Parallel DFS | NC150, TI150 | ✅ |
| 0101 | [Symmetric Tree](topics/07-trees/0101-symmetric-tree/) | Easy | Mirror DFS | TI150 | ✅ |
| 0104 | [Maximum Depth of Binary Tree](topics/07-trees/0104-maximum-depth-of-binary-tree/) | Easy | DFS height | NC150, TI150 | ✅ |
| 0108 | [Convert Sorted Array to Binary Search Tree](topics/07-trees/0108-convert-sorted-array-to-binary-search-tree/) | Easy | Divide at middle | TI150 | ✅ |
| 0110 | [Balanced Binary Tree](topics/07-trees/0110-balanced-binary-tree/) | Easy | DFS height with early exit | NC150 | ✅ |
| 0112 | [Path Sum](topics/07-trees/0112-path-sum/) | Easy | DFS with remaining sum | TI150 | ✅ |
| 0222 | [Count Complete Tree Nodes](topics/07-trees/0222-count-complete-tree-nodes/) | Easy | Compare left/right heights | TI150 | ✅ |
| 0226 | [Invert Binary Tree](topics/07-trees/0226-invert-binary-tree/) | Easy | DFS swap children | NC150, TI150 | ✅ |
| 0530 | [Minimum Absolute Difference in BST](topics/07-trees/0530-minimum-absolute-difference-in-bst/) | Easy | Inorder, track prev | TI150 | ✅ |
| 0543 | [Diameter of Binary Tree](topics/07-trees/0543-diameter-of-binary-tree/) | Easy | DFS height, update global | NC150 | ✅ |
| 0572 | [Subtree of Another Tree](topics/07-trees/0572-subtree-of-another-tree/) | Easy | DFS + same-tree check | NC150 | ✅ |
| 0637 | [Average of Levels in Binary Tree](topics/07-trees/0637-average-of-levels-in-binary-tree/) | Easy | BFS by level | TI150 | ✅ |
| 0098 | [Validate Binary Search Tree](topics/07-trees/0098-validate-binary-search-tree/) | Medium | DFS with bounds | NC150, TI150 | ✅ |
| 0102 | [Binary Tree Level Order Traversal](topics/07-trees/0102-binary-tree-level-order-traversal/) | Medium | BFS by level | NC150, TI150 | ✅ |
| 0103 | [Binary Tree Zigzag Level Order Traversal](topics/07-trees/0103-binary-tree-zigzag-level-order-traversal/) | Medium | BFS, alternate direction | TI150 | ✅ |
| 0105 | [Construct Binary Tree from Preorder and Inorder Traversal](topics/07-trees/0105-construct-binary-tree-from-preorder-and-inorder-traversal/) | Medium | Recursion + inorder index map | NC150, TI150 | ✅ |
| 0106 | [Construct Binary Tree from Inorder and Postorder Traversal](topics/07-trees/0106-construct-binary-tree-from-inorder-and-postorder-traversal/) | Medium | Recursion + inorder index map | TI150 | ✅ |
| 0114 | [Flatten Binary Tree to Linked List](topics/07-trees/0114-flatten-binary-tree-to-linked-list/) | Medium | Reverse preorder / Morris | TI150 | ✅ |
| 0117 | [Populating Next Right Pointers in Each Node II](topics/07-trees/0117-populating-next-right-pointers-in-each-node-ii/) | Medium | Level linking with dummy | TI150 | ✅ |
| 0129 | [Sum Root to Leaf Numbers](topics/07-trees/0129-sum-root-to-leaf-numbers/) | Medium | DFS carrying the number | TI150 | ✅ |
| 0173 | [Binary Search Tree Iterator](topics/07-trees/0173-binary-search-tree-iterator/) | Medium | Controlled inorder with stack | TI150 | ✅ |
| 0199 | [Binary Tree Right Side View](topics/07-trees/0199-binary-tree-right-side-view/) | Medium | BFS, last per level | NC150, TI150 | ✅ |
| 0230 | [Kth Smallest Element in a BST](topics/07-trees/0230-kth-smallest-element-in-a-bst/) | Medium | Inorder traversal | NC150, TI150 | ✅ |
| 0235 | [Lowest Common Ancestor of a Binary Search Tree](topics/07-trees/0235-lowest-common-ancestor-of-a-binary-search-tree/) | Medium | BST split point | NC150 | ✅ |
| 0236 | [Lowest Common Ancestor of a Binary Tree](topics/07-trees/0236-lowest-common-ancestor-of-a-binary-tree/) | Medium | Postorder DFS | TI150 | ✅ |
| 0427 | [Construct Quad Tree](topics/07-trees/0427-construct-quad-tree/) | Medium | Divide & conquer on grid | TI150 | ✅ |
| 1448 | [Count Good Nodes in Binary Tree](topics/07-trees/1448-count-good-nodes-in-binary-tree/) | Medium | DFS with path max | NC150 | ✅ |
| 0124 | [Binary Tree Maximum Path Sum](topics/07-trees/0124-binary-tree-maximum-path-sum/) | Hard | DFS gain, update global | NC150, TI150 | ✅ |
| 0297 | [Serialize and Deserialize Binary Tree](topics/07-trees/0297-serialize-and-deserialize-binary-tree/) | Hard | Preorder with null markers | NC150 | ✅ |

## 08. Tries

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0208 | [Implement Trie (Prefix Tree)](topics/08-tries/0208-implement-trie-prefix-tree/) | Medium | Trie | NC150, TI150 | ✅ |
| 0211 | [Design Add and Search Words Data Structure](topics/08-tries/0211-design-add-and-search-words-data-structure/) | Medium | Trie + DFS on wildcard | NC150, TI150 | ✅ |
| 0212 | [Word Search II](topics/08-tries/0212-word-search-ii/) | Hard | Trie + grid backtracking | NC150, TI150 | ✅ |

## 09. Heap / Priority Queue

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0703 | [Kth Largest Element in a Stream](topics/09-heap-priority-queue/0703-kth-largest-element-in-a-stream/) | Easy | Min-heap of size k | NC150 | ✅ |
| 1046 | [Last Stone Weight](topics/09-heap-priority-queue/1046-last-stone-weight/) | Easy | Max-heap simulation | NC150 | ✅ |
| 0215 | [Kth Largest Element in an Array](topics/09-heap-priority-queue/0215-kth-largest-element-in-an-array/) | Medium | Min-heap of size k / quickselect | NC150, TI150 | ✅ |
| 0355 | [Design Twitter](topics/09-heap-priority-queue/0355-design-twitter/) | Medium | Heap merge of k feeds | NC150 | ✅ |
| 0373 | [Find K Pairs with Smallest Sums](topics/09-heap-priority-queue/0373-find-k-pairs-with-smallest-sums/) | Medium | Min-heap frontier | TI150 | ✅ |
| 0621 | [Task Scheduler](topics/09-heap-priority-queue/0621-task-scheduler/) | Medium | Greedy counting / max-heap | NC150 | ✅ |
| 0973 | [K Closest Points to Origin](topics/09-heap-priority-queue/0973-k-closest-points-to-origin/) | Medium | Max-heap of size k | NC150 | ✅ |
| 0295 | [Find Median from Data Stream](topics/09-heap-priority-queue/0295-find-median-from-data-stream/) | Hard | Two heaps | NC150, TI150 | ✅ |
| 0502 | [IPO](topics/09-heap-priority-queue/0502-ipo/) | Hard | Sort by capital + max-heap | TI150 | ✅ |

## 10. Backtracking

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0017 | [Letter Combinations of a Phone Number](topics/10-backtracking/0017-letter-combinations-of-a-phone-number/) | Medium | Backtrack over digit map | NC150, TI150 | ✅ |
| 0039 | [Combination Sum](topics/10-backtracking/0039-combination-sum/) | Medium | Backtrack with reuse | NC150, TI150 | ✅ |
| 0040 | [Combination Sum II](topics/10-backtracking/0040-combination-sum-ii/) | Medium | Sort + skip duplicates, no reuse | NC150 | ✅ |
| 0046 | [Permutations](topics/10-backtracking/0046-permutations/) | Medium | Backtrack with used[] | NC150, TI150 | ✅ |
| 0077 | [Combinations](topics/10-backtracking/0077-combinations/) | Medium | Backtrack choose k | TI150 | ✅ |
| 0078 | [Subsets](topics/10-backtracking/0078-subsets/) | Medium | Include/exclude | NC150 | ✅ |
| 0079 | [Word Search](topics/10-backtracking/0079-word-search/) | Medium | Grid DFS backtracking | NC150, TI150 | ✅ |
| 0090 | [Subsets II](topics/10-backtracking/0090-subsets-ii/) | Medium | Sort + skip duplicates | NC150 | ✅ |
| 0131 | [Palindrome Partitioning](topics/10-backtracking/0131-palindrome-partitioning/) | Medium | Backtrack on cut points | NC150 | ✅ |
| 0051 | [N-Queens](topics/10-backtracking/0051-n-queens/) | Hard | Backtrack with col/diag sets | NC150 | ✅ |
| 0052 | [N-Queens II](topics/10-backtracking/0052-n-queens-ii/) | Hard | Backtrack with col/diag sets (count) | TI150 | ✅ |

## 11. Graphs

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0130 | [Surrounded Regions](topics/11-graphs/0130-surrounded-regions/) | Medium | DFS from border | NC150, TI150 | ✅ |
| 0133 | [Clone Graph](topics/11-graphs/0133-clone-graph/) | Medium | DFS + hashmap old→new | NC150, TI150 | ✅ |
| 0200 | [Number of Islands](topics/11-graphs/0200-number-of-islands/) | Medium | Grid DFS/BFS flood fill | NC150, TI150 | ✅ |
| 0207 | [Course Schedule](topics/11-graphs/0207-course-schedule/) | Medium | Cycle detection / Kahn's | NC150, TI150 | ✅ |
| 0210 | [Course Schedule II](topics/11-graphs/0210-course-schedule-ii/) | Medium | Topological sort | NC150, TI150 | ✅ |
| 0261 | [Graph Valid Tree](topics/11-graphs/0261-graph-valid-tree/) | Medium | n-1 edges + connected | NC150 | ✅ |
| 0286 | [Walls and Gates](topics/11-graphs/0286-walls-and-gates/) | Medium | Multi-source BFS | NC150 | ✅ |
| 0323 | [Number of Connected Components in an Undirected Graph](topics/11-graphs/0323-number-of-connected-components-in-an-undirected-graph/) | Medium | Union-Find / DFS | NC150 | ✅ |
| 0399 | [Evaluate Division](topics/11-graphs/0399-evaluate-division/) | Medium | Weighted graph DFS / weighted Union-Find | TI150 | ✅ |
| 0417 | [Pacific Atlantic Water Flow](topics/11-graphs/0417-pacific-atlantic-water-flow/) | Medium | Reverse DFS from both oceans | NC150 | ✅ |
| 0433 | [Minimum Genetic Mutation](topics/11-graphs/0433-minimum-genetic-mutation/) | Medium | BFS over strings | TI150 | ✅ |
| 0684 | [Redundant Connection](topics/11-graphs/0684-redundant-connection/) | Medium | Union-Find | NC150 | ✅ |
| 0695 | [Max Area of Island](topics/11-graphs/0695-max-area-of-island/) | Medium | Grid DFS | NC150 | ✅ |
| 0909 | [Snakes and Ladders](topics/11-graphs/0909-snakes-and-ladders/) | Medium | BFS on board | TI150 | ✅ |
| 0994 | [Rotting Oranges](topics/11-graphs/0994-rotting-oranges/) | Medium | Multi-source BFS | NC150 | ✅ |
| 0127 | [Word Ladder](topics/11-graphs/0127-word-ladder/) | Hard | BFS with wildcard buckets | NC150, TI150 | ✅ |

## 12. Advanced Graphs

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0743 | [Network Delay Time](topics/12-advanced-graphs/0743-network-delay-time/) | Medium | Dijkstra | NC150 | ✅ |
| 0787 | [Cheapest Flights Within K Stops](topics/12-advanced-graphs/0787-cheapest-flights-within-k-stops/) | Medium | Bellman-Ford, k+1 rounds | NC150 | ✅ |
| 1584 | [Min Cost to Connect All Points](topics/12-advanced-graphs/1584-min-cost-to-connect-all-points/) | Medium | MST (Prim's) | NC150 | ✅ |
| 0269 | [Alien Dictionary](topics/12-advanced-graphs/0269-alien-dictionary/) | Hard | Topological sort on chars | NC150 | ✅ |
| 0332 | [Reconstruct Itinerary](topics/12-advanced-graphs/0332-reconstruct-itinerary/) | Hard | Hierholzer (Eulerian path) | NC150 | ✅ |
| 0778 | [Swim in Rising Water](topics/12-advanced-graphs/0778-swim-in-rising-water/) | Hard | Dijkstra on max edge | NC150 | ✅ |

## 13. 1-D Dynamic Programming

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0070 | [Climbing Stairs](topics/13-1d-dp/0070-climbing-stairs/) | Easy | Fibonacci DP | NC150, TI150 | ✅ |
| 0746 | [Min Cost Climbing Stairs](topics/13-1d-dp/0746-min-cost-climbing-stairs/) | Easy | Linear DP | NC150 | ✅ |
| 0005 | [Longest Palindromic Substring](topics/13-1d-dp/0005-longest-palindromic-substring/) | Medium | Expand around center | NC150, TI150 | ✅ |
| 0091 | [Decode Ways](topics/13-1d-dp/0091-decode-ways/) | Medium | Linear DP on 1/2 digits | NC150 | ✅ |
| 0139 | [Word Break](topics/13-1d-dp/0139-word-break/) | Medium | Prefix DP + dictionary | NC150, TI150 | ✅ |
| 0152 | [Maximum Product Subarray](topics/13-1d-dp/0152-maximum-product-subarray/) | Medium | Track max & min | NC150 | ✅ |
| 0198 | [House Robber](topics/13-1d-dp/0198-house-robber/) | Medium | Take/skip DP | NC150, TI150 | ✅ |
| 0213 | [House Robber II](topics/13-1d-dp/0213-house-robber-ii/) | Medium | Two passes of House Robber | NC150 | ✅ |
| 0300 | [Longest Increasing Subsequence](topics/13-1d-dp/0300-longest-increasing-subsequence/) | Medium | DP / patience sort + binary search | NC150, TI150 | ✅ |
| 0322 | [Coin Change](topics/13-1d-dp/0322-coin-change/) | Medium | Unbounded knapsack (min) | NC150, TI150 | ✅ |
| 0416 | [Partition Equal Subset Sum](topics/13-1d-dp/0416-partition-equal-subset-sum/) | Medium | 0/1 knapsack subset sum | NC150 | ✅ |
| 0647 | [Palindromic Substrings](topics/13-1d-dp/0647-palindromic-substrings/) | Medium | Expand around center | NC150 | ✅ |

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
