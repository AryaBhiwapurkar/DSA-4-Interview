# DSA-4-Interview

Personal DSA interview revision repo. Each problem has an interview-style README plus C++ and Python solutions (Go too for problems added before November 2026). See [CLAUDE.md](CLAUDE.md) for conventions.

## Progress

| List | Problems | Done |
|------|---------:|-----:|
| NeetCode 150 (NC150) | 150 | 150 |
| LeetCode Top Interview 150 (TI150) | 150 | 150 |
| In both lists | 77 | 77 |
| Wave 2: Interview Extras ([plan](PLAN-wave2.md)) | 185 | 44 |
| **Unique total** | **408** | **267** |

Cheatsheets: [patterns](cheatsheets/patterns.md) · [syntax](cheatsheets/syntax.md)

## Topics

| Topic | Core (NC150/TI150) | Core done | Wave 2 | Wave 2 done |
|-------|---------:|-----:|---------:|-----:|
| [01. Arrays & Hashing](topics/01-arrays-hashing/) | 24 | 24 | 16 | 16 |
| [02. Two Pointers](topics/02-two-pointers/) | 10 | 10 | 7 | 7 |
| [03. Sliding Window](topics/03-sliding-window/) | 9 | 9 | 9 | 9 |
| [04. Stack](topics/04-stack/) | 9 | 9 | 12 | 12 |
| [05. Binary Search](topics/05-binary-search/) | 11 | 11 | 12 | 0 |
| [06. Linked List](topics/06-linked-list/) | 16 | 16 | 10 | 0 |
| [07. Trees](topics/07-trees/) | 29 | 29 | 24 | 0 |
| [08. Tries](topics/08-tries/) | 3 | 3 | 3 | 0 |
| [09. Heap / Priority Queue](topics/09-heap-priority-queue/) | 9 | 9 | 10 | 0 |
| [10. Backtracking](topics/10-backtracking/) | 11 | 11 | 8 | 0 |
| [11. Graphs](topics/11-graphs/) | 16 | 16 | 13 | 0 |
| [12. Advanced Graphs](topics/12-advanced-graphs/) | 6 | 6 | 4 | 0 |
| [13. 1-D Dynamic Programming](topics/13-1d-dp/) | 12 | 12 | 11 | 0 |
| [14. 2-D Dynamic Programming](topics/14-2d-dp/) | 17 | 17 | 13 | 0 |
| [15. Greedy](topics/15-greedy/) | 11 | 11 | 4 | 0 |
| [16. Intervals](topics/16-intervals/) | 8 | 8 | 6 | 0 |
| [17. Math & Geometry](topics/17-math-geometry/) | 12 | 12 | 8 | 0 |
| [18. Bit Manipulation](topics/18-bit-manipulation/) | 10 | 10 | 4 | 0 |
| 19. Design | – | – | 6 | 0 |
| 20. Advanced Data Structures | – | – | 5 | 0 |

Status: ✅ done · ⬜ not added yet. Within each table, problems are sorted Easy → Hard, then by number.

## 01. Arrays & Hashing

**Core (NC150 / TI150):** 24/24 done

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

**Wave 2 extras:** 16/16 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0303 | [Range Sum Query - Immutable](topics/01-arrays-hashing/0303-range-sum-query-immutable/) | Easy | Prefix sums | Extra | ✅ |
| 0448 | [Find All Numbers Disappeared in an Array](topics/01-arrays-hashing/0448-find-all-numbers-disappeared-in-an-array/) | Easy | Sign marking (index as hash) | Extra | ✅ |
| 0459 | [Repeated Substring Pattern](topics/01-arrays-hashing/0459-repeated-substring-pattern/) | Easy | Divisor check / KMP period | Extra | ✅ |
| 0557 | [Reverse Words in a String III](topics/01-arrays-hashing/0557-reverse-words-in-a-string-iii/) | Easy | Reverse each word in place | Extra | ✅ |
| 0031 | [Next Permutation](topics/01-arrays-hashing/0031-next-permutation/) | Medium | Pivot, swap, reverse suffix | Extra | ✅ |
| 0187 | [Repeated DNA Sequences](topics/01-arrays-hashing/0187-repeated-dna-sequences/) | Medium | Fixed window + set / 2-bit rolling | Extra | ✅ |
| 0229 | [Majority Element II](topics/01-arrays-hashing/0229-majority-element-ii/) | Medium | Boyer-Moore, two candidates | Extra | ✅ |
| 0249 | [Group Shifted Strings](topics/01-arrays-hashing/0249-group-shifted-strings/) | Medium | Canonical gap key | Extra | ✅ |
| 0304 | [Range Sum Query 2D - Immutable](topics/01-arrays-hashing/0304-range-sum-query-2d-immutable/) | Medium | 2-D prefix sums | Extra | ✅ |
| 0418 | [Sentence Screen Fitting](topics/01-arrays-hashing/0418-sentence-screen-fitting/) | Medium | Joined-sentence pointer | Extra | ✅ |
| 0525 | [Contiguous Array](topics/01-arrays-hashing/0525-contiguous-array/) | Medium | Prefix balance + first-index map | Extra | ✅ |
| 0560 | [Subarray Sum Equals K](topics/01-arrays-hashing/0560-subarray-sum-equals-k/) | Medium | Prefix sum + count map | Extra | ✅ |
| 0890 | [Find and Replace Pattern](topics/01-arrays-hashing/0890-find-and-replace-pattern/) | Medium | Bijection, two maps | Extra | ✅ |
| 0974 | [Subarray Sums Divisible by K](topics/01-arrays-hashing/0974-subarray-sums-divisible-by-k/) | Medium | Prefix remainder counts | Extra | ✅ |
| 0041 | [First Missing Positive](topics/01-arrays-hashing/0041-first-missing-positive/) | Hard | Cyclic placement (index as hash) | Extra | ✅ |
| 0214 | [Shortest Palindrome](topics/01-arrays-hashing/0214-shortest-palindrome/) | Hard | KMP on s + # + reverse(s) | Extra | ✅ |

## 02. Two Pointers

**Core (NC150 / TI150):** 10/10 done

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

**Wave 2 extras:** 7/7 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0283 | [Move Zeroes](topics/02-two-pointers/0283-move-zeroes/) | Easy | Read/write pointers | Extra | ✅ |
| 0680 | [Valid Palindrome II](topics/02-two-pointers/0680-valid-palindrome-ii/) | Easy | Converging, one skip | Extra | ✅ |
| 0977 | [Squares of a Sorted Array](topics/02-two-pointers/0977-squares-of-a-sorted-array/) | Easy | Converging, fill from back | Extra | ✅ |
| 0016 | [3Sum Closest](topics/02-two-pointers/0016-3sum-closest/) | Medium | Sort + fix one + two pointers | Extra | ✅ |
| 0018 | [4Sum](topics/02-two-pointers/0018-4sum/) | Medium | Sort + fix two + two pointers | Extra | ✅ |
| 0075 | [Sort Colors](topics/02-two-pointers/0075-sort-colors/) | Medium | Dutch national flag | Extra | ✅ |
| 0792 | [Number of Matching Subsequences](topics/02-two-pointers/0792-number-of-matching-subsequences/) | Medium | Waiting buckets per next char | Extra | ✅ |

## 03. Sliding Window

**Core (NC150 / TI150):** 9/9 done

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

**Wave 2 extras:** 9/9 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0340 | [Longest Substring with At Most K Distinct Characters](topics/03-sliding-window/0340-longest-substring-with-at-most-k-distinct-characters/) | Medium | Window + char counts | Extra | ✅ |
| 0438 | [Find All Anagrams in a String](topics/03-sliding-window/0438-find-all-anagrams-in-a-string/) | Medium | Fixed window + count match | Extra | ✅ |
| 0713 | [Subarray Product Less Than K](topics/03-sliding-window/0713-subarray-product-less-than-k/) | Medium | Window, count ending at r | Extra | ✅ |
| 0904 | [Fruit Into Baskets](topics/03-sliding-window/0904-fruit-into-baskets/) | Medium | Window, at most 2 distinct | Extra | ✅ |
| 1004 | [Max Consecutive Ones III](topics/03-sliding-window/1004-max-consecutive-ones-iii/) | Medium | Window with at most k zeros | Extra | ✅ |
| 0220 | [Contains Duplicate III](topics/03-sliding-window/0220-contains-duplicate-iii/) | Hard | Window + buckets / ordered set | Extra | ✅ |
| 0727 | [Minimum Window Subsequence](topics/03-sliding-window/0727-minimum-window-subsequence/) | Hard | Forward scan + backward shrink | Extra | ✅ |
| 0862 | [Shortest Subarray with Sum at Least K](topics/03-sliding-window/0862-shortest-subarray-with-sum-at-least-k/) | Hard | Prefix sums + monotonic deque | Extra | ✅ |
| 0992 | [Subarrays with K Different Integers](topics/03-sliding-window/0992-subarrays-with-k-different-integers/) | Hard | atMost(k) - atMost(k-1) | Extra | ✅ |

## 04. Stack

**Core (NC150 / TI150):** 9/9 done

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

**Wave 2 extras:** 12/12 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0496 | [Next Greater Element I](topics/04-stack/0496-next-greater-element-i/) | Easy | Monotonic stack + map | Extra | ✅ |
| 0227 | [Basic Calculator II](topics/04-stack/0227-basic-calculator-ii/) | Medium | Stack of terms, apply * / immediately | Extra | ✅ |
| 0316 | [Remove Duplicate Letters](topics/04-stack/0316-remove-duplicate-letters/) | Medium | Monotonic stack + last occurrence | Extra | ✅ |
| 0402 | [Remove K Digits](topics/04-stack/0402-remove-k-digits/) | Medium | Monotonic increasing stack | Extra | ✅ |
| 0503 | [Next Greater Element II](topics/04-stack/0503-next-greater-element-ii/) | Medium | Monotonic stack, two passes (circular) | Extra | ✅ |
| 0901 | [Online Stock Span](topics/04-stack/0901-online-stock-span/) | Medium | Monotonic stack with spans | Extra | ✅ |
| 0907 | [Sum of Subarray Minimums](topics/04-stack/0907-sum-of-subarray-minimums/) | Medium | Monotonic stack, contribution counting | Extra | ✅ |
| 0921 | [Minimum Add to Make Parentheses Valid](topics/04-stack/0921-minimum-add-to-make-parentheses-valid/) | Medium | Balance counter | Extra | ✅ |
| 1249 | [Minimum Remove to Make Valid Parentheses](topics/04-stack/1249-minimum-remove-to-make-valid-parentheses/) | Medium | Stack of unmatched indices | Extra | ✅ |
| 0032 | [Longest Valid Parentheses](topics/04-stack/0032-longest-valid-parentheses/) | Hard | Stack of indices / two counters | Extra | ✅ |
| 0085 | [Maximal Rectangle](topics/04-stack/0085-maximal-rectangle/) | Hard | Histogram per row + largest rectangle | Extra | ✅ |
| 0772 | [Basic Calculator III](topics/04-stack/0772-basic-calculator-iii/) | Hard | Recursive descent / stack per paren | Extra | ✅ |

## 05. Binary Search

**Core (NC150 / TI150):** 11/11 done

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

**Wave 2 extras:** 0/12 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0278 | First Bad Version | Easy | Binary search for first true | Extra | ⬜ |
| 0367 | Valid Perfect Square | Easy | Binary search on answer | Extra | ⬜ |
| 0081 | Search in Rotated Sorted Array II | Medium | Rotated binary search with duplicates | Extra | ⬜ |
| 0240 | Search a 2D Matrix II | Medium | Staircase search from a corner | Extra | ⬜ |
| 0275 | H-Index II | Medium | Binary search on sorted citations | Extra | ⬜ |
| 0702 | Search in a Sorted Array of Unknown Size | Medium | Exponential search + binary search | Extra | ⬜ |
| 0852 | Peak Index in a Mountain Array | Medium | Binary search on slope | Extra | ⬜ |
| 1011 | Capacity To Ship Packages Within D Days | Medium | Binary search on answer + greedy check | Extra | ⬜ |
| 1283 | Find the Smallest Divisor Given a Threshold | Medium | Binary search on answer | Extra | ⬜ |
| 0154 | Find Minimum in Rotated Sorted Array II | Hard | Rotated min with duplicates (hi--) | Extra | ⬜ |
| 0410 | Split Array Largest Sum | Hard | Binary search on answer + greedy check | Extra | ⬜ |
| 0719 | Find K-th Smallest Pair Distance | Hard | Binary search on answer + two pointers | Extra | ⬜ |

## 06. Linked List

**Core (NC150 / TI150):** 16/16 done

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

**Wave 2 extras:** 0/10 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0083 | Remove Duplicates from Sorted List | Easy | Skip equal next nodes | Extra | ⬜ |
| 0160 | Intersection of Two Linked Lists | Easy | Two pointers switch heads | Extra | ⬜ |
| 0234 | Palindrome Linked List | Easy | Find middle, reverse second half | Extra | ⬜ |
| 0876 | Middle of the Linked List | Easy | Slow/fast pointers | Extra | ⬜ |
| 0024 | Swap Nodes in Pairs | Medium | Dummy node + pointer rewiring | Extra | ⬜ |
| 0142 | Linked List Cycle II | Medium | Floyd, then reset one pointer | Extra | ⬜ |
| 0147 | Insertion Sort List | Medium | Dummy head + insertion | Extra | ⬜ |
| 0328 | Odd Even Linked List | Medium | Two chains, then join | Extra | ⬜ |
| 0430 | Flatten a Multilevel Doubly Linked List | Medium | DFS / stack splice | Extra | ⬜ |
| 0445 | Add Two Numbers II | Medium | Stacks / reverse, add with carry | Extra | ⬜ |

## 07. Trees

**Core (NC150 / TI150):** 29/29 done

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

**Wave 2 extras:** 0/24 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0111 | Minimum Depth of Binary Tree | Easy | BFS to first leaf | Extra | ⬜ |
| 0257 | Binary Tree Paths | Easy | DFS building paths | Extra | ⬜ |
| 0783 | Minimum Distance Between BST Nodes | Easy | Inorder, adjacent difference | Extra | ⬜ |
| 0897 | Increasing Order Search Tree | Easy | Inorder relink | Extra | ⬜ |
| 1022 | Sum of Root To Leaf Binary Numbers | Easy | DFS carrying value | Extra | ⬜ |
| 0107 | Binary Tree Level Order Traversal II | Medium | BFS, reverse levels | Extra | ⬜ |
| 0109 | Convert Sorted List to Binary Search Tree | Medium | Inorder simulation / middle split | Extra | ⬜ |
| 0113 | Path Sum II | Medium | DFS with path backtracking | Extra | ⬜ |
| 0116 | Populating Next Right Pointers in Each Node | Medium | Level links using next pointers | Extra | ⬜ |
| 0298 | Binary Tree Longest Consecutive Sequence | Medium | DFS carrying run length | Extra | ⬜ |
| 0437 | Path Sum III | Medium | Prefix sums on root paths | Extra | ⬜ |
| 0449 | Serialize and Deserialize BST | Medium | Preorder + bounds | Extra | ⬜ |
| 0450 | Delete Node in a BST | Medium | BST delete with successor | Extra | ⬜ |
| 0515 | Find Largest Value in Each Tree Row | Medium | BFS level max | Extra | ⬜ |
| 0652 | Find Duplicate Subtrees | Medium | Subtree serialization + map | Extra | ⬜ |
| 0662 | Maximum Width of Binary Tree | Medium | BFS with position indices | Extra | ⬜ |
| 0687 | Longest Univalue Path | Medium | Post-order arm lengths | Extra | ⬜ |
| 0863 | All Nodes Distance K in Binary Tree | Medium | Parent map + BFS | Extra | ⬜ |
| 0889 | Construct Binary Tree from Preorder and Postorder Traversal | Medium | Recursive split by root's left child | Extra | ⬜ |
| 0958 | Check Completeness of a Binary Tree | Medium | BFS, no node after a gap | Extra | ⬜ |
| 1123 | Lowest Common Ancestor of Deepest Leaves | Medium | Post-order (depth, node) | Extra | ⬜ |
| 1382 | Balance a Binary Search Tree | Medium | Inorder to array, rebuild | Extra | ⬜ |
| 1650 | Lowest Common Ancestor of a Binary Tree III | Medium | Parent pointers, two-pointer switch | Extra | ⬜ |
| 0987 | Vertical Order Traversal of a Binary Tree | Hard | DFS with (col, row, val) sort | Extra | ⬜ |

## 08. Tries

**Core (NC150 / TI150):** 3/3 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0208 | [Implement Trie (Prefix Tree)](topics/08-tries/0208-implement-trie-prefix-tree/) | Medium | Trie | NC150, TI150 | ✅ |
| 0211 | [Design Add and Search Words Data Structure](topics/08-tries/0211-design-add-and-search-words-data-structure/) | Medium | Trie + DFS on wildcard | NC150, TI150 | ✅ |
| 0212 | [Word Search II](topics/08-tries/0212-word-search-ii/) | Hard | Trie + grid backtracking | NC150, TI150 | ✅ |

**Wave 2 extras:** 0/3 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0421 | Maximum XOR of Two Numbers in an Array | Medium | Binary trie, greedy opposite bit | Extra | ⬜ |
| 0648 | Replace Words | Medium | Trie of roots, shortest prefix | Extra | ⬜ |
| 1268 | Search Suggestions System | Medium | Trie / sort + binary search | Extra | ⬜ |

## 09. Heap / Priority Queue

**Core (NC150 / TI150):** 9/9 done

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

**Wave 2 extras:** 0/10 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0378 | Kth Smallest Element in a Sorted Matrix | Medium | Min-heap of rows / binary search on value | Extra | ⬜ |
| 0658 | Find K Closest Elements | Medium | Binary search window / heap | Extra | ⬜ |
| 0692 | Top K Frequent Words | Medium | Count + heap with custom order | Extra | ⬜ |
| 0767 | Reorganize String | Medium | Max-heap, place most frequent | Extra | ⬜ |
| 1834 | Single-Threaded CPU | Medium | Sort by time + min-heap | Extra | ⬜ |
| 0358 | Rearrange String k Distance Apart | Hard | Max-heap + cooldown queue | Extra | ⬜ |
| 0407 | Trapping Rain Water II | Hard | Min-heap from the border (Dijkstra-like) | Extra | ⬜ |
| 0480 | Sliding Window Median | Hard | Two heaps + lazy deletion | Extra | ⬜ |
| 0632 | Smallest Range Covering Elements from K Lists | Hard | K-way merge heap + running max | Extra | ⬜ |
| 0857 | Minimum Cost to Hire K Workers | Hard | Sort by ratio + max-heap of quality | Extra | ⬜ |

## 10. Backtracking

**Core (NC150 / TI150):** 11/11 done

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

**Wave 2 extras:** 0/8 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0047 | Permutations II | Medium | Backtracking, skip equal siblings | Extra | ⬜ |
| 0093 | Restore IP Addresses | Medium | Backtracking over 4 segments | Extra | ⬜ |
| 0216 | Combination Sum III | Medium | Backtracking with count and sum | Extra | ⬜ |
| 0291 | Word Pattern II | Medium | Backtracking with bijection maps | Extra | ⬜ |
| 0698 | Partition to K Equal Sum Subsets | Medium | Backtracking buckets / bitmask DP | Extra | ⬜ |
| 0037 | Sudoku Solver | Hard | Backtracking with row/col/box sets | Extra | ⬜ |
| 0301 | Remove Invalid Parentheses | Hard | BFS by removals / DFS with counts | Extra | ⬜ |
| 0980 | Unique Paths III | Hard | DFS covering every cell | Extra | ⬜ |

## 11. Graphs

**Core (NC150 / TI150):** 16/16 done

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

**Wave 2 extras:** 0/13 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0463 | Island Perimeter | Easy | Count edges per land cell | Extra | ⬜ |
| 0310 | Minimum Height Trees | Medium | Peel leaves (topological trim) | Extra | ⬜ |
| 0542 | 01 Matrix | Medium | Multi-source BFS from zeros | Extra | ⬜ |
| 0547 | Number of Provinces | Medium | DFS / union-find components | Extra | ⬜ |
| 0752 | Open the Lock | Medium | BFS over states | Extra | ⬜ |
| 0785 | Is Graph Bipartite? | Medium | 2-coloring BFS/DFS | Extra | ⬜ |
| 0990 | Satisfiability of Equality Equations | Medium | Union-find, then check != | Extra | ⬜ |
| 1020 | Number of Enclaves | Medium | Flood fill from the border | Extra | ⬜ |
| 1306 | Jump Game III | Medium | BFS/DFS over indices | Extra | ⬜ |
| 1462 | Course Schedule IV | Medium | Topological order + reachability sets | Extra | ⬜ |
| 0305 | Number of Islands II | Hard | Online union-find | Extra | ⬜ |
| 0317 | Shortest Distance from All Buildings | Hard | BFS from each building, sum distances | Extra | ⬜ |
| 0827 | Making A Large Island | Hard | Label islands, try each zero | Extra | ⬜ |

## 12. Advanced Graphs

**Core (NC150 / TI150):** 6/6 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0743 | [Network Delay Time](topics/12-advanced-graphs/0743-network-delay-time/) | Medium | Dijkstra | NC150 | ✅ |
| 0787 | [Cheapest Flights Within K Stops](topics/12-advanced-graphs/0787-cheapest-flights-within-k-stops/) | Medium | Bellman-Ford, k+1 rounds | NC150 | ✅ |
| 1584 | [Min Cost to Connect All Points](topics/12-advanced-graphs/1584-min-cost-to-connect-all-points/) | Medium | MST (Prim's) | NC150 | ✅ |
| 0269 | [Alien Dictionary](topics/12-advanced-graphs/0269-alien-dictionary/) | Hard | Topological sort on chars | NC150 | ✅ |
| 0332 | [Reconstruct Itinerary](topics/12-advanced-graphs/0332-reconstruct-itinerary/) | Hard | Hierholzer (Eulerian path) | NC150 | ✅ |
| 0778 | [Swim in Rising Water](topics/12-advanced-graphs/0778-swim-in-rising-water/) | Hard | Dijkstra on max edge | NC150 | ✅ |

**Wave 2 extras:** 0/4 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0953 | Verifying an Alien Dictionary | Easy | Rank map, compare neighbours | Extra | ⬜ |
| 1514 | Path with Maximum Probability | Medium | Dijkstra with max-heap of probability | Extra | ⬜ |
| 1631 | Path With Minimum Effort | Medium | Dijkstra on max edge / binary search | Extra | ⬜ |
| 1192 | Critical Connections in a Network | Hard | Tarjan bridges (low-link) | Extra | ⬜ |

## 13. 1-D Dynamic Programming

**Core (NC150 / TI150):** 12/12 done

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

**Wave 2 extras:** 0/11 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0279 | Perfect Squares | Medium | Unbounded knapsack DP / BFS | Extra | ⬜ |
| 0337 | House Robber III | Medium | Tree DP (rob, skip) pairs | Extra | ⬜ |
| 0377 | Combination Sum IV | Medium | Ordered count DP (amount outer) | Extra | ⬜ |
| 0673 | Number of Longest Increasing Subsequence | Medium | LIS DP with counts | Extra | ⬜ |
| 0740 | Delete and Earn | Medium | Bucket sums, then House Robber | Extra | ⬜ |
| 1049 | Last Stone Weight II | Medium | Subset sum closest to half | Extra | ⬜ |
| 0132 | Palindrome Partitioning II | Hard | Palindrome table + min cuts DP | Extra | ⬜ |
| 0140 | Word Break II | Hard | Memoized DFS returning sentences | Extra | ⬜ |
| 0354 | Russian Doll Envelopes | Hard | Sort (w asc, h desc) + LIS | Extra | ⬜ |
| 0472 | Concatenated Words | Hard | Word Break per word (shorter words) | Extra | ⬜ |
| 0639 | Decode Ways II | Hard | Decode Ways DP with * cases | Extra | ⬜ |

## 14. 2-D Dynamic Programming

**Core (NC150 / TI150):** 17/17 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0062 | [Unique Paths](topics/14-2d-dp/0062-unique-paths/) | Medium | Grid DP | NC150 | ✅ |
| 0063 | [Unique Paths II](topics/14-2d-dp/0063-unique-paths-ii/) | Medium | Grid DP with obstacles | TI150 | ✅ |
| 0064 | [Minimum Path Sum](topics/14-2d-dp/0064-minimum-path-sum/) | Medium | Grid DP | TI150 | ✅ |
| 0072 | [Edit Distance](topics/14-2d-dp/0072-edit-distance/) | Medium | Two-string DP | NC150, TI150 | ✅ |
| 0097 | [Interleaving String](topics/14-2d-dp/0097-interleaving-string/) | Medium | Two-string DP | NC150, TI150 | ✅ |
| 0120 | [Triangle](topics/14-2d-dp/0120-triangle/) | Medium | Bottom-up DP | TI150 | ✅ |
| 0221 | [Maximal Square](topics/14-2d-dp/0221-maximal-square/) | Medium | Grid DP, min of 3 neighbors | TI150 | ✅ |
| 0309 | [Best Time to Buy and Sell Stock with Cooldown](topics/14-2d-dp/0309-best-time-to-buy-and-sell-stock-with-cooldown/) | Medium | State machine DP | NC150 | ✅ |
| 0494 | [Target Sum](topics/14-2d-dp/0494-target-sum/) | Medium | Subset-sum DP / memo | NC150 | ✅ |
| 0518 | [Coin Change II](topics/14-2d-dp/0518-coin-change-ii/) | Medium | Unbounded knapsack (count) | NC150 | ✅ |
| 1143 | [Longest Common Subsequence](topics/14-2d-dp/1143-longest-common-subsequence/) | Medium | Two-string DP | NC150 | ✅ |
| 0010 | [Regular Expression Matching](topics/14-2d-dp/0010-regular-expression-matching/) | Hard | Two-string DP with star | NC150 | ✅ |
| 0115 | [Distinct Subsequences](topics/14-2d-dp/0115-distinct-subsequences/) | Hard | Two-string DP | NC150 | ✅ |
| 0123 | [Best Time to Buy and Sell Stock III](topics/14-2d-dp/0123-best-time-to-buy-and-sell-stock-iii/) | Hard | State machine DP (2 txns) | TI150 | ✅ |
| 0188 | [Best Time to Buy and Sell Stock IV](topics/14-2d-dp/0188-best-time-to-buy-and-sell-stock-iv/) | Hard | State machine DP (k txns) | TI150 | ✅ |
| 0312 | [Burst Balloons](topics/14-2d-dp/0312-burst-balloons/) | Hard | Interval DP (last to burst) | NC150 | ✅ |
| 0329 | [Longest Increasing Path in a Matrix](topics/14-2d-dp/0329-longest-increasing-path-in-a-matrix/) | Hard | DFS + memo | NC150 | ✅ |

**Wave 2 extras:** 0/13 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0516 | Longest Palindromic Subsequence | Medium | Interval DP / LCS with reverse | Extra | ⬜ |
| 0583 | Delete Operation for Two Strings | Medium | LCS-based DP | Extra | ⬜ |
| 0714 | Best Time to Buy and Sell Stock with Transaction Fee | Medium | Hold/cash state machine | Extra | ⬜ |
| 0931 | Minimum Falling Path Sum | Medium | Grid DP from the row above | Extra | ⬜ |
| 1039 | Minimum Score Triangulation of Polygon | Medium | Interval DP | Extra | ⬜ |
| 1277 | Count Square Submatrices with All Ones | Medium | Maximal-square DP, sum of values | Extra | ⬜ |
| 0044 | Wildcard Matching | Hard | Two-string DP with * | Extra | ⬜ |
| 0174 | Dungeon Game | Hard | Grid DP from the bottom-right | Extra | ⬜ |
| 0664 | Strange Printer | Hard | Interval DP, merge equal ends | Extra | ⬜ |
| 0940 | Distinct Subsequences II | Hard | DP with last-occurrence subtraction | Extra | ⬜ |
| 1092 | Shortest Common Supersequence | Hard | LCS table + reconstruction | Extra | ⬜ |
| 1547 | Minimum Cost to Cut a Stick | Hard | Interval DP over cut positions | Extra | ⬜ |
| 2328 | Number of Increasing Paths in a Grid | Hard | DFS + memo on a DAG | Extra | ⬜ |

## 15. Greedy

**Core (NC150 / TI150):** 11/11 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0045 | [Jump Game II](topics/15-greedy/0045-jump-game-ii/) | Medium | BFS-style level greedy | NC150, TI150 | ✅ |
| 0053 | [Maximum Subarray](topics/15-greedy/0053-maximum-subarray/) | Medium | Kadane | NC150, TI150 | ✅ |
| 0055 | [Jump Game](topics/15-greedy/0055-jump-game/) | Medium | Track farthest reach | NC150, TI150 | ✅ |
| 0122 | [Best Time to Buy and Sell Stock II](topics/15-greedy/0122-best-time-to-buy-and-sell-stock-ii/) | Medium | Sum positive deltas | TI150 | ✅ |
| 0134 | [Gas Station](topics/15-greedy/0134-gas-station/) | Medium | Reset start on negative tank | NC150, TI150 | ✅ |
| 0678 | [Valid Parenthesis String](topics/15-greedy/0678-valid-parenthesis-string/) | Medium | Track min/max open count | NC150 | ✅ |
| 0763 | [Partition Labels](topics/15-greedy/0763-partition-labels/) | Medium | Last occurrence + window end | NC150 | ✅ |
| 0846 | [Hand of Straights](topics/15-greedy/0846-hand-of-straights/) | Medium | Sorted counts, build from min | NC150 | ✅ |
| 0918 | [Maximum Sum Circular Subarray](topics/15-greedy/0918-maximum-sum-circular-subarray/) | Medium | Kadane on max & min | TI150 | ✅ |
| 1899 | [Merge Triplets to Form Target Triplet](topics/15-greedy/1899-merge-triplets-to-form-target-triplet/) | Medium | Filter valid triplets | NC150 | ✅ |
| 0135 | [Candy](topics/15-greedy/0135-candy/) | Hard | Two passes L→R, R→L | TI150 | ✅ |

**Wave 2 extras:** 0/4 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0659 | Split Array into Consecutive Subsequences | Medium | Greedy with count + "ends at" maps | Extra | ⬜ |
| 1024 | Video Stitching | Medium | Greedy farthest reach (jump game) | Extra | ⬜ |
| 1296 | Divide Array in Sets of K Consecutive Numbers | Medium | Sorted counts, build from min | Extra | ⬜ |
| 1326 | Minimum Number of Taps to Open to Water a Garden | Hard | Intervals to jumps, greedy reach | Extra | ⬜ |

## 16. Intervals

**Core (NC150 / TI150):** 8/8 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0228 | [Summary Ranges](topics/16-intervals/0228-summary-ranges/) | Easy | Linear scan of runs | TI150 | ✅ |
| 0252 | [Meeting Rooms](topics/16-intervals/0252-meeting-rooms/) | Easy | Sort + check overlap | NC150 | ✅ |
| 0056 | [Merge Intervals](topics/16-intervals/0056-merge-intervals/) | Medium | Sort by start + merge | NC150, TI150 | ✅ |
| 0057 | [Insert Interval](topics/16-intervals/0057-insert-interval/) | Medium | Merge on the fly | NC150, TI150 | ✅ |
| 0253 | [Meeting Rooms II](topics/16-intervals/0253-meeting-rooms-ii/) | Medium | Sorted starts/ends or min-heap | NC150 | ✅ |
| 0435 | [Non-overlapping Intervals](topics/16-intervals/0435-non-overlapping-intervals/) | Medium | Sort by end, greedy | NC150 | ✅ |
| 0452 | [Minimum Number of Arrows to Burst Balloons](topics/16-intervals/0452-minimum-number-of-arrows-to-burst-balloons/) | Medium | Sort by end, greedy | TI150 | ✅ |
| 1851 | [Minimum Interval to Include Each Query](topics/16-intervals/1851-minimum-interval-to-include-each-query/) | Hard | Sort queries + min-heap | NC150 | ✅ |

**Wave 2 extras:** 0/6 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0646 | Maximum Length of Pair Chain | Medium | Sort by end, greedy | Extra | ⬜ |
| 0729 | My Calendar I | Medium | Ordered map, check neighbours | Extra | ⬜ |
| 0986 | Interval List Intersections | Medium | Two pointers over sorted lists | Extra | ⬜ |
| 1094 | Car Pooling | Medium | Difference array / sweep | Extra | ⬜ |
| 0218 | The Skyline Problem | Hard | Sweep line + max-heap | Extra | ⬜ |
| 0352 | Data Stream as Disjoint Intervals | Hard | Ordered map merge on insert | Extra | ⬜ |

## 17. Math & Geometry

**Core (NC150 / TI150):** 12/12 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0009 | [Palindrome Number](topics/17-math-geometry/0009-palindrome-number/) | Easy | Reverse half the number | TI150 | ✅ |
| 0066 | [Plus One](topics/17-math-geometry/0066-plus-one/) | Easy | Carry from the end | NC150, TI150 | ✅ |
| 0202 | [Happy Number](topics/17-math-geometry/0202-happy-number/) | Easy | Cycle detection (fast/slow) | NC150, TI150 | ✅ |
| 0043 | [Multiply Strings](topics/17-math-geometry/0043-multiply-strings/) | Medium | Grade-school multiplication | NC150 | ✅ |
| 0048 | [Rotate Image](topics/17-math-geometry/0048-rotate-image/) | Medium | Transpose + reverse rows | NC150, TI150 | ✅ |
| 0050 | [Pow(x, n)](topics/17-math-geometry/0050-powx-n/) | Medium | Fast exponentiation | NC150, TI150 | ✅ |
| 0054 | [Spiral Matrix](topics/17-math-geometry/0054-spiral-matrix/) | Medium | Shrinking boundaries | NC150, TI150 | ✅ |
| 0073 | [Set Matrix Zeroes](topics/17-math-geometry/0073-set-matrix-zeroes/) | Medium | First row/col as markers | NC150, TI150 | ✅ |
| 0172 | [Factorial Trailing Zeroes](topics/17-math-geometry/0172-factorial-trailing-zeroes/) | Medium | Count factors of 5 | TI150 | ✅ |
| 0289 | [Game of Life](topics/17-math-geometry/0289-game-of-life/) | Medium | In-place state encoding | TI150 | ✅ |
| 2013 | [Detect Squares](topics/17-math-geometry/2013-detect-squares/) | Medium | Point counts + diagonal | NC150 | ✅ |
| 0149 | [Max Points on a Line](topics/17-math-geometry/0149-max-points-on-a-line/) | Hard | Slope hashmap (gcd) | TI150 | ✅ |

**Wave 2 extras:** 0/8 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0168 | Excel Sheet Column Title | Easy | Base-26 with no zero digit | Extra | ⬜ |
| 0415 | Add Strings | Easy | Right-to-left carry | Extra | ⬜ |
| 0867 | Transpose Matrix | Easy | Index swap into a new matrix | Extra | ⬜ |
| 0029 | Divide Two Integers | Medium | Doubling subtraction, overflow care | Extra | ⬜ |
| 0059 | Spiral Matrix II | Medium | Shrinking boundaries (write) | Extra | ⬜ |
| 0204 | Count Primes | Medium | Sieve of Eratosthenes | Extra | ⬜ |
| 0372 | Super Pow | Medium | Modular exponent digit by digit | Extra | ⬜ |
| 0939 | Minimum Area Rectangle | Medium | Point set, fix the diagonal | Extra | ⬜ |

## 18. Bit Manipulation

**Core (NC150 / TI150):** 10/10 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0067 | [Add Binary](topics/18-bit-manipulation/0067-add-binary/) | Easy | Carry addition | TI150 | ✅ |
| 0136 | [Single Number](topics/18-bit-manipulation/0136-single-number/) | Easy | XOR | NC150, TI150 | ✅ |
| 0190 | [Reverse Bits](topics/18-bit-manipulation/0190-reverse-bits/) | Easy | Shift and build | NC150, TI150 | ✅ |
| 0191 | [Number of 1 Bits](topics/18-bit-manipulation/0191-number-of-1-bits/) | Easy | n & (n-1) | NC150, TI150 | ✅ |
| 0268 | [Missing Number](topics/18-bit-manipulation/0268-missing-number/) | Easy | XOR / sum formula | NC150 | ✅ |
| 0338 | [Counting Bits](topics/18-bit-manipulation/0338-counting-bits/) | Easy | DP on bits | NC150 | ✅ |
| 0007 | [Reverse Integer](topics/18-bit-manipulation/0007-reverse-integer/) | Medium | Digit pop with overflow check | NC150 | ✅ |
| 0137 | [Single Number II](topics/18-bit-manipulation/0137-single-number-ii/) | Medium | Bit counting mod 3 | TI150 | ✅ |
| 0201 | [Bitwise AND of Numbers Range](topics/18-bit-manipulation/0201-bitwise-and-of-numbers-range/) | Medium | Common prefix | TI150 | ✅ |
| 0371 | [Sum of Two Integers](topics/18-bit-manipulation/0371-sum-of-two-integers/) | Medium | XOR + carry | NC150 | ✅ |

**Wave 2 extras:** 0/4 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0231 | Power of Two | Easy | n & (n - 1) == 0 | Extra | ⬜ |
| 0461 | Hamming Distance | Easy | popcount(x ^ y) | Extra | ⬜ |
| 0260 | Single Number III | Medium | XOR all, split by lowest set bit | Extra | ⬜ |
| 0477 | Total Hamming Distance | Medium | Per-bit ones x zeros | Extra | ⬜ |

## 19. Design

**Wave 2 extras:** 0/6 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0706 | Design HashMap | Easy | Buckets with chaining | Extra | ⬜ |
| 0348 | Design Tic-Tac-Toe | Medium | Row/col/diagonal counters | Extra | ⬜ |
| 0362 | Design Hit Counter | Medium | Queue / circular buckets | Extra | ⬜ |
| 0622 | Design Circular Queue | Medium | Array ring buffer | Extra | ⬜ |
| 0460 | LFU Cache | Hard | Key map + frequency lists | Extra | ⬜ |
| 0716 | Max Stack | Hard | Two stacks / list + ordered map | Extra | ⬜ |

## 20. Advanced Data Structures

**Wave 2 extras:** 0/5 done

| # | Problem | Difficulty | Pattern | Lists | Status |
|---|---------|------------|---------|-------|--------|
| 0307 | Range Sum Query - Mutable | Medium | Fenwick tree / segment tree | Extra | ⬜ |
| 0315 | Count of Smaller Numbers After Self | Hard | Fenwick over ranks / merge sort | Extra | ⬜ |
| 0493 | Reverse Pairs | Hard | Merge sort count / Fenwick | Extra | ⬜ |
| 0715 | Range Module | Hard | Ordered map of disjoint intervals | Extra | ⬜ |
| 0732 | My Calendar III | Hard | Sweep with ordered map / segment tree | Extra | ⬜ |
