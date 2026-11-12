# Wave 2 Plan: Interview Problems Beyond NC150 / TI150

Status: **in progress.** 185 problems in 9 batches, worked topic by topic. Batches 1-3 done (2026-11-12).

## Decisions
- One list: the old Tier 1 and Tier 2 are merged. Rare and near-duplicate problems (old Tier 3) are **left out** and stay as "(not added yet)" mentions.
- New folders approved: `19-design`, `20-advanced-data-structures`. Existing problems don't move (0146 LRU stays in 06, 0380 stays in 01).
- Premium problems are included, marked (P). Their folders still carry the LeetCode link.
- Same format as wave 1: README + C++ + Python (no Go), mandatory verification, backfill "(not added yet)" mentions, and `gen_readme.py` for the index.
- Frontmatter `lists: [Interview Extras]`. `gen_readme.py` gets a third list code (`X`) for these.
- `*` = not mentioned anywhere in the repo yet (a new pick).

## Batches

| Batch | Topics | Problems |
|-------|--------|----------|
| 1 ✅ | 01 Arrays & Hashing, 02 Two Pointers | 23 |
| 2 ✅ | 03 Sliding Window, 04 Stack | 21 |
| 3 ✅ | 05 Binary Search, 06 Linked List | 22 |
| 4 | 07 Trees | 24 |
| 5 | 08 Tries, 09 Heap, 10 Backtracking | 21 |
| 6 | 11 Graphs, 12 Advanced Graphs | 17 |
| 7 | 13 1-D DP, 14 2-D DP | 24 |
| 8 | 15 Greedy, 16 Intervals, 17 Math & Geometry, 18 Bit Manipulation | 22 |
| 9 | 19 Design (new), 20 Advanced Data Structures (new) | 11 |
| | **Total** | **185** |

Each batch gets one commit per topic, then one "index, cheatsheets, backfill" commit.

---

## Batch 1

### 01 Arrays & Hashing (16)
- [x] 0560 Subarray Sum Equals K
- [x] 0303 Range Sum Query - Immutable
- [x] 0304 Range Sum Query 2D - Immutable *
- [x] 0525 Contiguous Array *
- [x] 0974 Subarray Sums Divisible by K *
- [x] 0041 First Missing Positive
- [x] 0229 Majority Element II
- [x] 0448 Find All Numbers Disappeared in an Array
- [x] 0031 Next Permutation
- [x] 0187 Repeated DNA Sequences *
- [x] 0459 Repeated Substring Pattern
- [x] 0214 Shortest Palindrome
- [x] 0249 Group Shifted Strings (P)
- [x] 0418 Sentence Screen Fitting (P)
- [x] 0557 Reverse Words in a String III
- [x] 0890 Find and Replace Pattern

### 02 Two Pointers (7)
- [x] 0283 Move Zeroes
- [x] 0977 Squares of a Sorted Array
- [x] 0016 3Sum Closest
- [x] 0018 4Sum
- [x] 0075 Sort Colors
- [x] 0680 Valid Palindrome II
- [x] 0792 Number of Matching Subsequences

## Batch 2

### 03 Sliding Window (9)
- [x] 0438 Find All Anagrams in a String
- [x] 1004 Max Consecutive Ones III
- [x] 0713 Subarray Product Less Than K
- [x] 0340 Longest Substring with At Most K Distinct Characters (P)
- [x] 0904 Fruit Into Baskets *
- [x] 0992 Subarrays with K Different Integers *
- [x] 0862 Shortest Subarray with Sum at Least K
- [x] 0220 Contains Duplicate III
- [x] 0727 Minimum Window Subsequence (P)

### 04 Stack (12)
- [x] 0496 Next Greater Element I
- [x] 0503 Next Greater Element II
- [x] 0901 Online Stock Span
- [x] 0907 Sum of Subarray Minimums *
- [x] 0227 Basic Calculator II
- [x] 0772 Basic Calculator III (P)
- [x] 0032 Longest Valid Parentheses
- [x] 1249 Minimum Remove to Make Valid Parentheses
- [x] 0921 Minimum Add to Make Parentheses Valid
- [x] 0402 Remove K Digits *
- [x] 0316 Remove Duplicate Letters *
- [x] 0085 Maximal Rectangle

## Batch 3

### 05 Binary Search (12)
- [x] 0278 First Bad Version
- [x] 0852 Peak Index in a Mountain Array
- [x] 0367 Valid Perfect Square
- [x] 0410 Split Array Largest Sum
- [x] 1011 Capacity To Ship Packages Within D Days
- [x] 1283 Find the Smallest Divisor Given a Threshold
- [x] 0240 Search a 2D Matrix II
- [x] 0081 Search in Rotated Sorted Array II
- [x] 0154 Find Minimum in Rotated Sorted Array II
- [x] 0275 H-Index II
- [x] 0702 Search in a Sorted Array of Unknown Size (P)
- [x] 0719 Find K-th Smallest Pair Distance

### 06 Linked List (10)
- [x] 0142 Linked List Cycle II
- [x] 0234 Palindrome Linked List
- [x] 0876 Middle of the Linked List
- [x] 0160 Intersection of Two Linked Lists *
- [x] 0024 Swap Nodes in Pairs
- [x] 0328 Odd Even Linked List
- [x] 0445 Add Two Numbers II
- [x] 0083 Remove Duplicates from Sorted List
- [x] 0147 Insertion Sort List
- [x] 0430 Flatten a Multilevel Doubly Linked List

## Batch 4

### 07 Trees (24)
- [ ] 0863 All Nodes Distance K in Binary Tree *
- [ ] 0113 Path Sum II
- [ ] 0437 Path Sum III
- [ ] 0111 Minimum Depth of Binary Tree
- [ ] 0257 Binary Tree Paths
- [ ] 0116 Populating Next Right Pointers in Each Node
- [ ] 0450 Delete Node in a BST *
- [ ] 0662 Maximum Width of Binary Tree *
- [ ] 0987 Vertical Order Traversal of a Binary Tree *
- [ ] 0958 Check Completeness of a Binary Tree
- [ ] 0652 Find Duplicate Subtrees
- [ ] 0449 Serialize and Deserialize BST
- [ ] 0107 Binary Tree Level Order Traversal II
- [ ] 0109 Convert Sorted List to Binary Search Tree
- [ ] 0515 Find Largest Value in Each Tree Row
- [ ] 0687 Longest Univalue Path
- [ ] 0783 Minimum Distance Between BST Nodes
- [ ] 0889 Construct Binary Tree from Preorder and Postorder Traversal
- [ ] 0897 Increasing Order Search Tree
- [ ] 1022 Sum of Root To Leaf Binary Numbers
- [ ] 1123 Lowest Common Ancestor of Deepest Leaves
- [ ] 1382 Balance a Binary Search Tree
- [ ] 0298 Binary Tree Longest Consecutive Sequence (P)
- [ ] 1650 Lowest Common Ancestor of a Binary Tree III (P)

## Batch 5

### 08 Tries (3)
- [ ] 1268 Search Suggestions System
- [ ] 0421 Maximum XOR of Two Numbers in an Array *
- [ ] 0648 Replace Words *

### 09 Heap / Priority Queue (10)
- [ ] 0767 Reorganize String
- [ ] 0658 Find K Closest Elements
- [ ] 0378 Kth Smallest Element in a Sorted Matrix
- [ ] 0480 Sliding Window Median
- [ ] 1834 Single-Threaded CPU
- [ ] 0632 Smallest Range Covering Elements from K Lists *
- [ ] 0692 Top K Frequent Words
- [ ] 0407 Trapping Rain Water II
- [ ] 0857 Minimum Cost to Hire K Workers
- [ ] 0358 Rearrange String k Distance Apart (P)

### 10 Backtracking (8)
- [ ] 0047 Permutations II
- [ ] 0216 Combination Sum III
- [ ] 0037 Sudoku Solver
- [ ] 0093 Restore IP Addresses
- [ ] 0301 Remove Invalid Parentheses
- [ ] 0698 Partition to K Equal Sum Subsets
- [ ] 0980 Unique Paths III
- [ ] 0291 Word Pattern II (P)

## Batch 6

### 11 Graphs (13)
- [ ] 0547 Number of Provinces
- [ ] 0542 01 Matrix
- [ ] 0752 Open the Lock
- [ ] 0785 Is Graph Bipartite? *
- [ ] 0310 Minimum Height Trees *
- [ ] 0827 Making A Large Island
- [ ] 0463 Island Perimeter
- [ ] 1462 Course Schedule IV
- [ ] 1020 Number of Enclaves
- [ ] 1306 Jump Game III
- [ ] 0990 Satisfiability of Equality Equations
- [ ] 0305 Number of Islands II (P)
- [ ] 0317 Shortest Distance from All Buildings (P)

### 12 Advanced Graphs (4)
- [ ] 1631 Path With Minimum Effort
- [ ] 1514 Path with Maximum Probability
- [ ] 1192 Critical Connections in a Network *
- [ ] 0953 Verifying an Alien Dictionary

## Batch 7

### 13 1-D DP (11)
- [ ] 0279 Perfect Squares
- [ ] 0337 House Robber III
- [ ] 0740 Delete and Earn
- [ ] 0377 Combination Sum IV
- [ ] 0673 Number of Longest Increasing Subsequence
- [ ] 0354 Russian Doll Envelopes
- [ ] 0140 Word Break II
- [ ] 0132 Palindrome Partitioning II
- [ ] 0472 Concatenated Words
- [ ] 0639 Decode Ways II
- [ ] 1049 Last Stone Weight II

### 14 2-D DP (13)
- [ ] 0516 Longest Palindromic Subsequence
- [ ] 0583 Delete Operation for Two Strings
- [ ] 0714 Best Time to Buy and Sell Stock with Transaction Fee
- [ ] 0931 Minimum Falling Path Sum
- [ ] 0174 Dungeon Game
- [ ] 1277 Count Square Submatrices with All Ones
- [ ] 0044 Wildcard Matching
- [ ] 1092 Shortest Common Supersequence
- [ ] 0940 Distinct Subsequences II
- [ ] 1039 Minimum Score Triangulation of Polygon
- [ ] 1547 Minimum Cost to Cut a Stick
- [ ] 0664 Strange Printer
- [ ] 2328 Number of Increasing Paths in a Grid

## Batch 8

### 15 Greedy (4)
- [ ] 0659 Split Array into Consecutive Subsequences
- [ ] 1024 Video Stitching
- [ ] 1326 Minimum Number of Taps to Open to Water a Garden
- [ ] 1296 Divide Array in Sets of K Consecutive Numbers

### 16 Intervals (6)
- [ ] 0986 Interval List Intersections *
- [ ] 1094 Car Pooling
- [ ] 0646 Maximum Length of Pair Chain
- [ ] 0729 My Calendar I *
- [ ] 0352 Data Stream as Disjoint Intervals
- [ ] 0218 The Skyline Problem

### 17 Math & Geometry (8)
- [ ] 0059 Spiral Matrix II
- [ ] 0415 Add Strings
- [ ] 0029 Divide Two Integers
- [ ] 0204 Count Primes *
- [ ] 0168 Excel Sheet Column Title *
- [ ] 0372 Super Pow
- [ ] 0867 Transpose Matrix
- [ ] 0939 Minimum Area Rectangle

### 18 Bit Manipulation (4)
- [ ] 0231 Power of Two
- [ ] 0260 Single Number III
- [ ] 0461 Hamming Distance
- [ ] 0477 Total Hamming Distance *

## Batch 9

### 19 Design (new folder, 6)
- [ ] 0460 LFU Cache
- [ ] 0716 Max Stack (P)
- [ ] 0362 Design Hit Counter (P) *
- [ ] 0348 Design Tic-Tac-Toe (P) *
- [ ] 0622 Design Circular Queue *
- [ ] 0706 Design HashMap *

### 20 Advanced Data Structures (new folder, 5)
- [ ] 0307 Range Sum Query - Mutable *
- [ ] 0315 Count of Smaller Numbers After Self *
- [ ] 0493 Reverse Pairs *
- [ ] 0732 My Calendar III
- [ ] 0715 Range Module

---

## Left out on purpose
Rare, Premium-only niche or near-duplicate problems. They stay as "(not added yet)" mentions: 0159, 0161, 0163, 0186, 0273, 0558, 0685, 0694, 0753, 0793, 0885, 1135, 1232, 1245, 1485, 1598, 1721, 1776, 1793, 1836, 1871, 1901, 1928, 2024, 2034, 2089, 2097, 2161, 2251.
