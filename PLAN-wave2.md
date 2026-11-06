# Wave 2 Plan: Standard Interview Problems Beyond NC150 / TI150

Status: **approved, not started**. Decisions: new folders 19 and 20 approved; Premium problems included; start with Tier 1.

## Where these come from
1. **Follow-ups already referenced in the repo.** 185 distinct problems appear as `LC NNNN ... (not added yet)` in existing READMEs.
2. **Common interview problems in neither list.** Some aren't referenced anywhere yet, e.g. 0560-style prefix sums, 0863 All Nodes Distance K, 0307 / 0315 (Fenwick or segment tree), 0986 Interval List Intersections.

The tiers below are my judgement of how often a problem comes up in interviews. They're not based on frequency data.
- **Tier 1:** classic, asked a lot, teaches a pattern the repo doesn't yet cover well.
- **Tier 2:** a good variant, for when Tier 1 is done.
- **Tier 3:** niche, Premium-only or near-duplicate. Leave it as "(not added yet)".

`*` = not currently referenced in the repo (new). `P` = LeetCode Premium.

## Proposed new folders (need your OK, per CLAUDE.md)
| Folder | Why it can't live in an existing folder | Tier 1 problems |
|--------|-------------------------------------------|-----------------|
| `19-design` | Design classes (LFU, rate limiters, hit counters) are their own interview round; today they're scattered or missing | 0460 LFU Cache, 0716 Max Stack (P), 0362 Design Hit Counter* (P), 0348 Design Tic-Tac-Toe* (P), 0622 Design Circular Queue*, 0706 Design HashMap* |
| `20-advanced-data-structures` | Fenwick tree / segment tree / ordered-set sweeps aren't in NeetCode at all | 0307 Range Sum Query - Mutable*, 0315 Count of Smaller Numbers After Self*, 0493 Reverse Pairs*, 0732 My Calendar III, 0715 Range Module |

Existing problems stay where they are, so 0146 LRU stays in 06 and 0380 stays in 01. String algorithms (KMP, rolling hash) go into 01, next to 0028. Prefix-sum problems stay in 01.

## Tier 1 (≈ 130 problems)

| Topic | Problems |
|-------|----------|
| 01 Arrays & Hashing | 0560 Subarray Sum Equals K, 0303 Range Sum Query - Immutable, 0304 Range Sum Query 2D*, 0525 Contiguous Array*, 0974 Subarray Sums Divisible by K*, 0041 First Missing Positive, 0229 Majority Element II, 0448 Find All Numbers Disappeared, 0031 Next Permutation, 0187 Repeated DNA Sequences*, 0459 Repeated Substring Pattern |
| 02 Two Pointers | 0283 Move Zeroes, 0977 Squares of a Sorted Array, 0016 3Sum Closest, 0018 4Sum, 0075 Sort Colors, 0680 Valid Palindrome II |
| 03 Sliding Window | 0438 Find All Anagrams, 1004 Max Consecutive Ones III, 0713 Subarray Product Less Than K, 0340 Longest Substring with At Most K Distinct (P), 0904 Fruit Into Baskets*, 0992 Subarrays with K Different Integers*, 0862 Shortest Subarray with Sum at Least K |
| 04 Stack | 0496 Next Greater Element I, 0503 Next Greater Element II, 0901 Online Stock Span, 0907 Sum of Subarray Minimums*, 0227 Basic Calculator II, 0032 Longest Valid Parentheses, 1249 Minimum Remove to Make Valid Parentheses, 0402 Remove K Digits*, 0316 Remove Duplicate Letters*, 0085 Maximal Rectangle |
| 05 Binary Search | 0278 First Bad Version, 0852 Peak Index in a Mountain Array, 0410 Split Array Largest Sum, 1011 Capacity To Ship Packages, 0240 Search a 2D Matrix II, 0081 Search in Rotated Sorted Array II |
| 06 Linked List | 0142 Linked List Cycle II, 0234 Palindrome Linked List, 0876 Middle of the Linked List, 0160 Intersection of Two Linked Lists*, 0024 Swap Nodes in Pairs, 0328 Odd Even Linked List, 0445 Add Two Numbers II |
| 07 Trees | 0863 All Nodes Distance K*, 0113 Path Sum II, 0437 Path Sum III, 0111 Minimum Depth, 0257 Binary Tree Paths, 0116 Populating Next Right Pointers, 0450 Delete Node in a BST*, 0662 Maximum Width of Binary Tree*, 0987 Vertical Order Traversal*, 0958 Check Completeness, 0652 Find Duplicate Subtrees, 0449 Serialize and Deserialize BST |
| 08 Tries | 1268 Search Suggestions System, 0421 Maximum XOR of Two Numbers*, 0648 Replace Words* |
| 09 Heap | 0767 Reorganize String, 0658 Find K Closest Elements, 0378 Kth Smallest in a Sorted Matrix, 0480 Sliding Window Median, 1834 Single-Threaded CPU, 0632 Smallest Range Covering K Lists*, 0692 Top K Frequent Words |
| 10 Backtracking | 0047 Permutations II, 0216 Combination Sum III, 0037 Sudoku Solver, 0093 Restore IP Addresses, 0301 Remove Invalid Parentheses, 0698 Partition to K Equal Sum Subsets |
| 11 Graphs | 0547 Number of Provinces, 0542 01 Matrix, 0752 Open the Lock, 0785 Is Graph Bipartite?*, 0310 Minimum Height Trees*, 0827 Making A Large Island, 0463 Island Perimeter, 1462 Course Schedule IV |
| 12 Advanced Graphs | 1631 Path With Minimum Effort, 1514 Path with Maximum Probability, 1192 Critical Connections (Tarjan)*, 0953 Verifying an Alien Dictionary |
| 13 1-D DP | 0279 Perfect Squares, 0337 House Robber III, 0740 Delete and Earn, 0377 Combination Sum IV, 0673 Number of LIS, 0354 Russian Doll Envelopes, 0140 Word Break II |
| 14 2-D DP | 0516 Longest Palindromic Subsequence, 0583 Delete Operation for Two Strings, 0714 Stock with Transaction Fee, 0931 Minimum Falling Path Sum, 0174 Dungeon Game, 1277 Count Square Submatrices, 0044 Wildcard Matching |
| 15 Greedy | 0659 Split Array into Consecutive Subsequences, 1024 Video Stitching, 1326 Minimum Taps to Water a Garden |
| 16 Intervals | 0986 Interval List Intersections*, 1094 Car Pooling, 0646 Maximum Length of Pair Chain, 0729 My Calendar I*, 0218 The Skyline Problem |
| 17 Math & Geometry | 0059 Spiral Matrix II, 0415 Add Strings, 0029 Divide Two Integers, 0204 Count Primes*, 0168 Excel Sheet Column Title* |
| 18 Bit Manipulation | 0231 Power of Two, 0260 Single Number III, 0461 Hamming Distance, 0477 Total Hamming Distance* |
| 19 Design (new) | see table above (6) |
| 20 Advanced DS (new) | see table above (5) |

## Tier 2 (do after Tier 1, ≈ 55)
0083, 0107, 0109, 0132, 0147, 0154, 0214, 0220, 0249 (P), 0275, 0291 (P), 0298 (P), 0305 (P), 0317 (P), 0352, 0358 (P), 0367, 0372, 0407, 0418 (P), 0430, 0472, 0515, 0557, 0639, 0664, 0687, 0702 (P), 0719, 0727 (P), 0772 (P), 0783, 0792, 0857, 0867, 0889, 0890, 0897, 0921, 0939, 0940, 0980, 0990, 1020, 1022, 1039, 1049, 1092, 1123, 1283, 1296, 1306, 1382, 1547, 1650 (P), 2328

## Tier 3 (leave as "(not added yet)")
Near-duplicates and niche or Premium-only problems, such as 0159, 0161, 0163, 0186, 0273, 0558, 0685, 0694, 0753, 0793, 0885, 1135, 1232, 1245, 1485, 1598, 1721, 1776, 1793, 1836, 1871, 1901, 1928, 2024, 2034, 2089, 2097, 2161, 2251.

## Mechanics
- Same gold-standard format: README + C++ + Python (no Go, per the 2026-10-30 rule). Mandatory verification run.
- Frontmatter `lists: [Interview Extras]`. `gen_readme.py` gets a third list code (e.g. `X`) so the root index shows them separately from NC150 / TI150.
- Each new problem backfills its "(not added yet)" mentions automatically.
- Order: topic by topic, like wave 1. Two topics per session works well, with one commit per topic.
