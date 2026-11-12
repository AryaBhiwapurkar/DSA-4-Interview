"""Regenerate the root README.md index. Status comes from the filesystem:
a problem is done if topics/<topic>/<NNNN>-*/ exists.

Usage: python3 scripts/gen_readme.py
"""

import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

TOPICS = [
    ("01-arrays-hashing", "Arrays & Hashing"),
    ("02-two-pointers", "Two Pointers"),
    ("03-sliding-window", "Sliding Window"),
    ("04-stack", "Stack"),
    ("05-binary-search", "Binary Search"),
    ("06-linked-list", "Linked List"),
    ("07-trees", "Trees"),
    ("08-tries", "Tries"),
    ("09-heap-priority-queue", "Heap / Priority Queue"),
    ("10-backtracking", "Backtracking"),
    ("11-graphs", "Graphs"),
    ("12-advanced-graphs", "Advanced Graphs"),
    ("13-1d-dp", "1-D Dynamic Programming"),
    ("14-2d-dp", "2-D Dynamic Programming"),
    ("15-greedy", "Greedy"),
    ("16-intervals", "Intervals"),
    ("17-math-geometry", "Math & Geometry"),
    ("18-bit-manipulation", "Bit Manipulation"),
    ("19-design", "Design"),
    ("20-advanced-data-structures", "Advanced Data Structures"),
]


def find_done() -> dict[int, str]:
    """LC number -> relative folder path, for every problem folder on disk."""
    done: dict[int, str] = {}
    for d in sorted((ROOT / "topics").glob("*/[0-9][0-9][0-9][0-9]-*")):
        if (d / "README.md").is_file():  # empty placeholder folders don't count
            done[int(d.name[:4])] = d.relative_to(ROOT).as_posix() + "/"
    return done


DONE = find_done()

# topic | number | title | difficulty | pattern | lists (N = NeetCode 150, T = Top Interview 150, X = Interview Extras / wave 2)
DATA = """
1|217|Contains Duplicate|E|Hash set|N
1|242|Valid Anagram|E|Frequency count|NT
1|1|Two Sum|E|Hashmap complement lookup|NT
1|49|Group Anagrams|M|Hashmap with canonical key|NT
1|347|Top K Frequent Elements|M|Bucket sort / heap|N
1|271|Encode and Decode Strings|M|Length-prefix encoding|N
1|238|Product of Array Except Self|M|Prefix & suffix products|NT
1|36|Valid Sudoku|M|Hash sets per row/col/box|NT
1|128|Longest Consecutive Sequence|M|Hash set, start-of-run|NT
1|169|Majority Element|E|Boyer-Moore voting|T
1|189|Rotate Array|M|Reverse in place|T
1|274|H-Index|M|Sort / counting|T
1|380|Insert Delete GetRandom O(1)|M|Hashmap + array, swap-delete|T
1|13|Roman to Integer|E|Hashmap, subtractive rule|T
1|12|Integer to Roman|M|Greedy over value table|T
1|58|Length of Last Word|E|Reverse scan|T
1|14|Longest Common Prefix|E|Vertical scan|T
1|151|Reverse Words in a String|M|Split + reverse|T
1|6|Zigzag Conversion|M|Row simulation|T
1|28|Find the Index of the First Occurrence in a String|E|String matching (KMP optional)|T
1|68|Text Justification|H|Greedy line packing|T
1|383|Ransom Note|E|Frequency count|T
1|205|Isomorphic Strings|E|Two-way mapping|T
1|290|Word Pattern|E|Two-way mapping|T
2|125|Valid Palindrome|E|Converging pointers|NT
2|167|Two Sum II - Input Array Is Sorted|M|Converging pointers on sorted|NT
2|15|3Sum|M|Sort + fix one + two pointers|NT
2|11|Container With Most Water|M|Converging, move shorter side|NT
2|42|Trapping Rain Water|H|Two pointers with running max|NT
2|88|Merge Sorted Array|E|Merge from the back|T
2|27|Remove Element|E|Read/write pointers|T
2|26|Remove Duplicates from Sorted Array|E|Read/write pointers|T
2|80|Remove Duplicates from Sorted Array II|M|Read/write, compare k back|T
2|392|Is Subsequence|E|Two pointers on two strings|T
3|121|Best Time to Buy and Sell Stock|E|Running min|NT
3|3|Longest Substring Without Repeating Characters|M|Variable window + last-seen map|NT
3|424|Longest Repeating Character Replacement|M|Variable window + max freq|N
3|567|Permutation in String|M|Fixed window + counts|N
3|76|Minimum Window Substring|H|Variable window + need/have|NT
3|239|Sliding Window Maximum|H|Monotonic deque|N
3|209|Minimum Size Subarray Sum|M|Variable window, shrink while valid|T
3|30|Substring with Concatenation of All Words|H|Fixed window per offset + counts|T
3|219|Contains Duplicate II|E|Fixed window + set|T
4|20|Valid Parentheses|E|Stack matching|NT
4|155|Min Stack|M|Stack of (val, min)|NT
4|150|Evaluate Reverse Polish Notation|M|Operand stack|NT
4|22|Generate Parentheses|M|Backtracking on open/close counts|NT
4|739|Daily Temperatures|M|Monotonic decreasing stack|N
4|853|Car Fleet|M|Sort by position + stack of arrival times|N
4|84|Largest Rectangle in Histogram|H|Monotonic increasing stack|N
4|71|Simplify Path|M|Stack of directory names|T
4|224|Basic Calculator|H|Stack for sign/paren context|T
5|704|Binary Search|E|Classic binary search|N
5|74|Search a 2D Matrix|M|Treat as flat sorted array|NT
5|875|Koko Eating Bananas|M|Binary search on answer|N
5|153|Find Minimum in Rotated Sorted Array|M|Compare mid with right|NT
5|33|Search in Rotated Sorted Array|M|Find the sorted half|NT
5|981|Time Based Key-Value Store|M|Hashmap + binary search on time|N
5|4|Median of Two Sorted Arrays|H|Binary search on partition|NT
5|35|Search Insert Position|E|Lower bound|T
5|162|Find Peak Element|M|Binary search on slope|T
5|34|Find First and Last Position of Element in Sorted Array|M|Lower & upper bound|T
5|69|Sqrt(x)|E|Binary search on answer|T
6|206|Reverse Linked List|E|Iterative reversal|N
6|21|Merge Two Sorted Lists|E|Dummy head merge|NT
6|143|Reorder List|M|Find mid + reverse + merge|N
6|19|Remove Nth Node From End of List|M|Fast/slow with n gap|NT
6|138|Copy List with Random Pointer|M|Hashmap old→new / interleave|NT
6|2|Add Two Numbers|M|Digit-wise add with carry|NT
6|141|Linked List Cycle|E|Floyd fast/slow|NT
6|287|Find the Duplicate Number|M|Floyd cycle on indices|N
6|146|LRU Cache|M|Hashmap + doubly linked list|NT
6|23|Merge k Sorted Lists|H|Min-heap / divide & conquer|NT
6|25|Reverse Nodes in k-Group|H|Group reversal with dummy|NT
6|92|Reverse Linked List II|M|Sublist reversal|T
6|82|Remove Duplicates from Sorted List II|M|Dummy + skip duplicate runs|T
6|61|Rotate List|M|Close ring, cut at n-k|T
6|86|Partition List|M|Two dummy lists|T
6|148|Sort List|M|Merge sort on list|T
7|226|Invert Binary Tree|E|DFS swap children|NT
7|104|Maximum Depth of Binary Tree|E|DFS height|NT
7|543|Diameter of Binary Tree|E|DFS height, update global|N
7|110|Balanced Binary Tree|E|DFS height with early exit|N
7|100|Same Tree|E|Parallel DFS|NT
7|572|Subtree of Another Tree|E|DFS + same-tree check|N
7|235|Lowest Common Ancestor of a Binary Search Tree|M|BST split point|N
7|102|Binary Tree Level Order Traversal|M|BFS by level|NT
7|199|Binary Tree Right Side View|M|BFS, last per level|NT
7|1448|Count Good Nodes in Binary Tree|M|DFS with path max|N
7|98|Validate Binary Search Tree|M|DFS with bounds|NT
7|230|Kth Smallest Element in a BST|M|Inorder traversal|NT
7|105|Construct Binary Tree from Preorder and Inorder Traversal|M|Recursion + inorder index map|NT
7|124|Binary Tree Maximum Path Sum|H|DFS gain, update global|NT
7|297|Serialize and Deserialize Binary Tree|H|Preorder with null markers|N
7|101|Symmetric Tree|E|Mirror DFS|T
7|106|Construct Binary Tree from Inorder and Postorder Traversal|M|Recursion + inorder index map|T
7|117|Populating Next Right Pointers in Each Node II|M|Level linking with dummy|T
7|114|Flatten Binary Tree to Linked List|M|Reverse preorder / Morris|T
7|112|Path Sum|E|DFS with remaining sum|T
7|129|Sum Root to Leaf Numbers|M|DFS carrying the number|T
7|173|Binary Search Tree Iterator|M|Controlled inorder with stack|T
7|222|Count Complete Tree Nodes|E|Compare left/right heights|T
7|236|Lowest Common Ancestor of a Binary Tree|M|Postorder DFS|T
7|637|Average of Levels in Binary Tree|E|BFS by level|T
7|103|Binary Tree Zigzag Level Order Traversal|M|BFS, alternate direction|T
7|530|Minimum Absolute Difference in BST|E|Inorder, track prev|T
7|108|Convert Sorted Array to Binary Search Tree|E|Divide at middle|T
7|427|Construct Quad Tree|M|Divide & conquer on grid|T
8|208|Implement Trie (Prefix Tree)|M|Trie|NT
8|211|Design Add and Search Words Data Structure|M|Trie + DFS on wildcard|NT
8|212|Word Search II|H|Trie + grid backtracking|NT
9|703|Kth Largest Element in a Stream|E|Min-heap of size k|N
9|1046|Last Stone Weight|E|Max-heap simulation|N
9|973|K Closest Points to Origin|M|Max-heap of size k|N
9|215|Kth Largest Element in an Array|M|Min-heap of size k / quickselect|NT
9|621|Task Scheduler|M|Greedy counting / max-heap|N
9|355|Design Twitter|M|Heap merge of k feeds|N
9|295|Find Median from Data Stream|H|Two heaps|NT
9|502|IPO|H|Sort by capital + max-heap|T
9|373|Find K Pairs with Smallest Sums|M|Min-heap frontier|T
10|78|Subsets|M|Include/exclude|N
10|39|Combination Sum|M|Backtrack with reuse|NT
10|46|Permutations|M|Backtrack with used[]|NT
10|90|Subsets II|M|Sort + skip duplicates|N
10|40|Combination Sum II|M|Sort + skip duplicates, no reuse|N
10|79|Word Search|M|Grid DFS backtracking|NT
10|131|Palindrome Partitioning|M|Backtrack on cut points|N
10|17|Letter Combinations of a Phone Number|M|Backtrack over digit map|NT
10|51|N-Queens|H|Backtrack with col/diag sets|N
10|77|Combinations|M|Backtrack choose k|T
10|52|N-Queens II|H|Backtrack with col/diag sets (count)|T
11|200|Number of Islands|M|Grid DFS/BFS flood fill|NT
11|133|Clone Graph|M|DFS + hashmap old→new|NT
11|695|Max Area of Island|M|Grid DFS|N
11|417|Pacific Atlantic Water Flow|M|Reverse DFS from both oceans|N
11|130|Surrounded Regions|M|DFS from border|NT
11|994|Rotting Oranges|M|Multi-source BFS|N
11|286|Walls and Gates|M|Multi-source BFS|N
11|207|Course Schedule|M|Cycle detection / Kahn's|NT
11|210|Course Schedule II|M|Topological sort|NT
11|684|Redundant Connection|M|Union-Find|N
11|323|Number of Connected Components in an Undirected Graph|M|Union-Find / DFS|N
11|261|Graph Valid Tree|M|n-1 edges + connected|N
11|127|Word Ladder|H|BFS with wildcard buckets|NT
11|399|Evaluate Division|M|Weighted graph DFS / weighted Union-Find|T
11|909|Snakes and Ladders|M|BFS on board|T
11|433|Minimum Genetic Mutation|M|BFS over strings|T
12|332|Reconstruct Itinerary|H|Hierholzer (Eulerian path)|N
12|1584|Min Cost to Connect All Points|M|MST (Prim's)|N
12|743|Network Delay Time|M|Dijkstra|N
12|778|Swim in Rising Water|H|Dijkstra on max edge|N
12|269|Alien Dictionary|H|Topological sort on chars|N
12|787|Cheapest Flights Within K Stops|M|Bellman-Ford, k+1 rounds|N
13|70|Climbing Stairs|E|Fibonacci DP|NT
13|746|Min Cost Climbing Stairs|E|Linear DP|N
13|198|House Robber|M|Take/skip DP|NT
13|213|House Robber II|M|Two passes of House Robber|N
13|5|Longest Palindromic Substring|M|Expand around center|NT
13|647|Palindromic Substrings|M|Expand around center|N
13|91|Decode Ways|M|Linear DP on 1/2 digits|N
13|322|Coin Change|M|Unbounded knapsack (min)|NT
13|152|Maximum Product Subarray|M|Track max & min|N
13|139|Word Break|M|Prefix DP + dictionary|NT
13|300|Longest Increasing Subsequence|M|DP / patience sort + binary search|NT
13|416|Partition Equal Subset Sum|M|0/1 knapsack subset sum|N
14|62|Unique Paths|M|Grid DP|N
14|1143|Longest Common Subsequence|M|Two-string DP|N
14|309|Best Time to Buy and Sell Stock with Cooldown|M|State machine DP|N
14|518|Coin Change II|M|Unbounded knapsack (count)|N
14|494|Target Sum|M|Subset-sum DP / memo|N
14|97|Interleaving String|M|Two-string DP|NT
14|329|Longest Increasing Path in a Matrix|H|DFS + memo|N
14|115|Distinct Subsequences|H|Two-string DP|N
14|72|Edit Distance|M|Two-string DP|NT
14|312|Burst Balloons|H|Interval DP (last to burst)|N
14|10|Regular Expression Matching|H|Two-string DP with star|N
14|120|Triangle|M|Bottom-up DP|T
14|64|Minimum Path Sum|M|Grid DP|T
14|63|Unique Paths II|M|Grid DP with obstacles|T
14|221|Maximal Square|M|Grid DP, min of 3 neighbors|T
14|123|Best Time to Buy and Sell Stock III|H|State machine DP (2 txns)|T
14|188|Best Time to Buy and Sell Stock IV|H|State machine DP (k txns)|T
15|53|Maximum Subarray|M|Kadane|NT
15|55|Jump Game|M|Track farthest reach|NT
15|45|Jump Game II|M|BFS-style level greedy|NT
15|134|Gas Station|M|Reset start on negative tank|NT
15|846|Hand of Straights|M|Sorted counts, build from min|N
15|1899|Merge Triplets to Form Target Triplet|M|Filter valid triplets|N
15|763|Partition Labels|M|Last occurrence + window end|N
15|678|Valid Parenthesis String|M|Track min/max open count|N
15|122|Best Time to Buy and Sell Stock II|M|Sum positive deltas|T
15|135|Candy|H|Two passes L→R, R→L|T
15|918|Maximum Sum Circular Subarray|M|Kadane on max & min|T
16|57|Insert Interval|M|Merge on the fly|NT
16|56|Merge Intervals|M|Sort by start + merge|NT
16|435|Non-overlapping Intervals|M|Sort by end, greedy|N
16|252|Meeting Rooms|E|Sort + check overlap|N
16|253|Meeting Rooms II|M|Sorted starts/ends or min-heap|N
16|1851|Minimum Interval to Include Each Query|H|Sort queries + min-heap|N
16|228|Summary Ranges|E|Linear scan of runs|T
16|452|Minimum Number of Arrows to Burst Balloons|M|Sort by end, greedy|T
17|48|Rotate Image|M|Transpose + reverse rows|NT
17|54|Spiral Matrix|M|Shrinking boundaries|NT
17|73|Set Matrix Zeroes|M|First row/col as markers|NT
17|202|Happy Number|E|Cycle detection (fast/slow)|NT
17|66|Plus One|E|Carry from the end|NT
17|50|Pow(x, n)|M|Fast exponentiation|NT
17|43|Multiply Strings|M|Grade-school multiplication|N
17|2013|Detect Squares|M|Point counts + diagonal|N
17|289|Game of Life|M|In-place state encoding|T
17|9|Palindrome Number|E|Reverse half the number|T
17|172|Factorial Trailing Zeroes|M|Count factors of 5|T
17|149|Max Points on a Line|H|Slope hashmap (gcd)|T
18|136|Single Number|E|XOR|NT
18|191|Number of 1 Bits|E|n & (n-1)|NT
18|338|Counting Bits|E|DP on bits|N
18|190|Reverse Bits|E|Shift and build|NT
18|268|Missing Number|E|XOR / sum formula|N
18|371|Sum of Two Integers|M|XOR + carry|N
18|7|Reverse Integer|M|Digit pop with overflow check|N
18|67|Add Binary|E|Carry addition|T
18|137|Single Number II|M|Bit counting mod 3|T
18|201|Bitwise AND of Numbers Range|M|Common prefix|T
1|560|Subarray Sum Equals K|M|Prefix sum + count map|X
1|303|Range Sum Query - Immutable|E|Prefix sums|X
1|304|Range Sum Query 2D - Immutable|M|2-D prefix sums|X
1|525|Contiguous Array|M|Prefix balance + first-index map|X
1|974|Subarray Sums Divisible by K|M|Prefix remainder counts|X
1|41|First Missing Positive|H|Cyclic placement (index as hash)|X
1|229|Majority Element II|M|Boyer-Moore, two candidates|X
1|448|Find All Numbers Disappeared in an Array|E|Sign marking (index as hash)|X
1|31|Next Permutation|M|Pivot, swap, reverse suffix|X
1|187|Repeated DNA Sequences|M|Fixed window + set / 2-bit rolling|X
1|459|Repeated Substring Pattern|E|Divisor check / KMP period|X
1|214|Shortest Palindrome|H|KMP on s + # + reverse(s)|X
1|249|Group Shifted Strings|M|Canonical gap key|X
1|418|Sentence Screen Fitting|M|Joined-sentence pointer|X
1|557|Reverse Words in a String III|E|Reverse each word in place|X
1|890|Find and Replace Pattern|M|Bijection, two maps|X
2|283|Move Zeroes|E|Read/write pointers|X
2|977|Squares of a Sorted Array|E|Converging, fill from back|X
2|16|3Sum Closest|M|Sort + fix one + two pointers|X
2|18|4Sum|M|Sort + fix two + two pointers|X
2|75|Sort Colors|M|Dutch national flag|X
2|680|Valid Palindrome II|E|Converging, one skip|X
2|792|Number of Matching Subsequences|M|Waiting buckets per next char|X
3|438|Find All Anagrams in a String|M|Fixed window + count match|X
3|1004|Max Consecutive Ones III|M|Window with at most k zeros|X
3|713|Subarray Product Less Than K|M|Window, count ending at r|X
3|340|Longest Substring with At Most K Distinct Characters|M|Window + char counts|X
3|904|Fruit Into Baskets|M|Window, at most 2 distinct|X
3|992|Subarrays with K Different Integers|H|atMost(k) - atMost(k-1)|X
3|862|Shortest Subarray with Sum at Least K|H|Prefix sums + monotonic deque|X
3|220|Contains Duplicate III|H|Window + buckets / ordered set|X
3|727|Minimum Window Subsequence|H|Forward scan + backward shrink|X
4|496|Next Greater Element I|E|Monotonic stack + map|X
4|503|Next Greater Element II|M|Monotonic stack, two passes (circular)|X
4|901|Online Stock Span|M|Monotonic stack with spans|X
4|907|Sum of Subarray Minimums|M|Monotonic stack, contribution counting|X
4|227|Basic Calculator II|M|Stack of terms, apply * / immediately|X
4|772|Basic Calculator III|H|Recursive descent / stack per paren|X
4|32|Longest Valid Parentheses|H|Stack of indices / two counters|X
4|1249|Minimum Remove to Make Valid Parentheses|M|Stack of unmatched indices|X
4|921|Minimum Add to Make Parentheses Valid|M|Balance counter|X
4|402|Remove K Digits|M|Monotonic increasing stack|X
4|316|Remove Duplicate Letters|M|Monotonic stack + last occurrence|X
4|85|Maximal Rectangle|H|Histogram per row + largest rectangle|X
5|278|First Bad Version|E|Binary search for first true|X
5|852|Peak Index in a Mountain Array|M|Binary search on slope|X
5|367|Valid Perfect Square|E|Binary search on answer|X
5|410|Split Array Largest Sum|H|Binary search on answer + greedy check|X
5|1011|Capacity To Ship Packages Within D Days|M|Binary search on answer + greedy check|X
5|1283|Find the Smallest Divisor Given a Threshold|M|Binary search on answer|X
5|240|Search a 2D Matrix II|M|Staircase search from a corner|X
5|81|Search in Rotated Sorted Array II|M|Rotated binary search with duplicates|X
5|154|Find Minimum in Rotated Sorted Array II|H|Rotated min with duplicates (hi--)|X
5|275|H-Index II|M|Binary search on sorted citations|X
5|702|Search in a Sorted Array of Unknown Size|M|Exponential search + binary search|X
5|719|Find K-th Smallest Pair Distance|H|Binary search on answer + two pointers|X
6|142|Linked List Cycle II|M|Floyd, then reset one pointer|X
6|234|Palindrome Linked List|E|Find middle, reverse second half|X
6|876|Middle of the Linked List|E|Slow/fast pointers|X
6|160|Intersection of Two Linked Lists|E|Two pointers switch heads|X
6|24|Swap Nodes in Pairs|M|Dummy node + pointer rewiring|X
6|328|Odd Even Linked List|M|Two chains, then join|X
6|445|Add Two Numbers II|M|Stacks / reverse, add with carry|X
6|83|Remove Duplicates from Sorted List|E|Skip equal next nodes|X
6|147|Insertion Sort List|M|Dummy head + insertion|X
6|430|Flatten a Multilevel Doubly Linked List|M|DFS / stack splice|X
7|863|All Nodes Distance K in Binary Tree|M|Parent map + BFS|X
7|113|Path Sum II|M|DFS with path backtracking|X
7|437|Path Sum III|M|Prefix sums on root paths|X
7|111|Minimum Depth of Binary Tree|E|BFS to first leaf|X
7|257|Binary Tree Paths|E|DFS building paths|X
7|116|Populating Next Right Pointers in Each Node|M|Level links using next pointers|X
7|450|Delete Node in a BST|M|BST delete with successor|X
7|662|Maximum Width of Binary Tree|M|BFS with position indices|X
7|987|Vertical Order Traversal of a Binary Tree|H|DFS with (col, row, val) sort|X
7|958|Check Completeness of a Binary Tree|M|BFS, no node after a gap|X
7|652|Find Duplicate Subtrees|M|Subtree serialization + map|X
7|449|Serialize and Deserialize BST|M|Preorder + bounds|X
7|107|Binary Tree Level Order Traversal II|M|BFS, reverse levels|X
7|109|Convert Sorted List to Binary Search Tree|M|Inorder simulation / middle split|X
7|515|Find Largest Value in Each Tree Row|M|BFS level max|X
7|687|Longest Univalue Path|M|Post-order arm lengths|X
7|783|Minimum Distance Between BST Nodes|E|Inorder, adjacent difference|X
7|889|Construct Binary Tree from Preorder and Postorder Traversal|M|Recursive split by root's left child|X
7|897|Increasing Order Search Tree|E|Inorder relink|X
7|1022|Sum of Root To Leaf Binary Numbers|E|DFS carrying value|X
7|1123|Lowest Common Ancestor of Deepest Leaves|M|Post-order (depth, node)|X
7|1382|Balance a Binary Search Tree|M|Inorder to array, rebuild|X
7|298|Binary Tree Longest Consecutive Sequence|M|DFS carrying run length|X
7|1650|Lowest Common Ancestor of a Binary Tree III|M|Parent pointers, two-pointer switch|X
8|1268|Search Suggestions System|M|Trie / sort + binary search|X
8|421|Maximum XOR of Two Numbers in an Array|M|Binary trie, greedy opposite bit|X
8|648|Replace Words|M|Trie of roots, shortest prefix|X
9|767|Reorganize String|M|Max-heap, place most frequent|X
9|658|Find K Closest Elements|M|Binary search window / heap|X
9|378|Kth Smallest Element in a Sorted Matrix|M|Min-heap of rows / binary search on value|X
9|480|Sliding Window Median|H|Two heaps + lazy deletion|X
9|1834|Single-Threaded CPU|M|Sort by time + min-heap|X
9|632|Smallest Range Covering Elements from K Lists|H|K-way merge heap + running max|X
9|692|Top K Frequent Words|M|Count + heap with custom order|X
9|407|Trapping Rain Water II|H|Min-heap from the border (Dijkstra-like)|X
9|857|Minimum Cost to Hire K Workers|H|Sort by ratio + max-heap of quality|X
9|358|Rearrange String k Distance Apart|H|Max-heap + cooldown queue|X
10|47|Permutations II|M|Backtracking, skip equal siblings|X
10|216|Combination Sum III|M|Backtracking with count and sum|X
10|37|Sudoku Solver|H|Backtracking with row/col/box sets|X
10|93|Restore IP Addresses|M|Backtracking over 4 segments|X
10|301|Remove Invalid Parentheses|H|BFS by removals / DFS with counts|X
10|698|Partition to K Equal Sum Subsets|M|Backtracking buckets / bitmask DP|X
10|980|Unique Paths III|H|DFS covering every cell|X
10|291|Word Pattern II|M|Backtracking with bijection maps|X
11|547|Number of Provinces|M|DFS / union-find components|X
11|542|01 Matrix|M|Multi-source BFS from zeros|X
11|752|Open the Lock|M|BFS over states|X
11|785|Is Graph Bipartite?|M|2-coloring BFS/DFS|X
11|310|Minimum Height Trees|M|Peel leaves (topological trim)|X
11|827|Making A Large Island|H|Label islands, try each zero|X
11|463|Island Perimeter|E|Count edges per land cell|X
11|1462|Course Schedule IV|M|Topological order + reachability sets|X
11|1020|Number of Enclaves|M|Flood fill from the border|X
11|1306|Jump Game III|M|BFS/DFS over indices|X
11|990|Satisfiability of Equality Equations|M|Union-find, then check !=|X
11|305|Number of Islands II|H|Online union-find|X
11|317|Shortest Distance from All Buildings|H|BFS from each building, sum distances|X
12|1631|Path With Minimum Effort|M|Dijkstra on max edge / binary search|X
12|1514|Path with Maximum Probability|M|Dijkstra with max-heap of probability|X
12|1192|Critical Connections in a Network|H|Tarjan bridges (low-link)|X
12|953|Verifying an Alien Dictionary|E|Rank map, compare neighbours|X
13|279|Perfect Squares|M|Unbounded knapsack DP / BFS|X
13|337|House Robber III|M|Tree DP (rob, skip) pairs|X
13|740|Delete and Earn|M|Bucket sums, then House Robber|X
13|377|Combination Sum IV|M|Ordered count DP (amount outer)|X
13|673|Number of Longest Increasing Subsequence|M|LIS DP with counts|X
13|354|Russian Doll Envelopes|H|Sort (w asc, h desc) + LIS|X
13|140|Word Break II|H|Memoized DFS returning sentences|X
13|132|Palindrome Partitioning II|H|Palindrome table + min cuts DP|X
13|472|Concatenated Words|H|Word Break per word (shorter words)|X
13|639|Decode Ways II|H|Decode Ways DP with * cases|X
13|1049|Last Stone Weight II|M|Subset sum closest to half|X
14|516|Longest Palindromic Subsequence|M|Interval DP / LCS with reverse|X
14|583|Delete Operation for Two Strings|M|LCS-based DP|X
14|714|Best Time to Buy and Sell Stock with Transaction Fee|M|Hold/cash state machine|X
14|931|Minimum Falling Path Sum|M|Grid DP from the row above|X
14|174|Dungeon Game|H|Grid DP from the bottom-right|X
14|1277|Count Square Submatrices with All Ones|M|Maximal-square DP, sum of values|X
14|44|Wildcard Matching|H|Two-string DP with *|X
14|1092|Shortest Common Supersequence|H|LCS table + reconstruction|X
14|940|Distinct Subsequences II|H|DP with last-occurrence subtraction|X
14|1039|Minimum Score Triangulation of Polygon|M|Interval DP|X
14|1547|Minimum Cost to Cut a Stick|H|Interval DP over cut positions|X
14|664|Strange Printer|H|Interval DP, merge equal ends|X
14|2328|Number of Increasing Paths in a Grid|H|DFS + memo on a DAG|X
15|659|Split Array into Consecutive Subsequences|M|Greedy with count + "ends at" maps|X
15|1024|Video Stitching|M|Greedy farthest reach (jump game)|X
15|1326|Minimum Number of Taps to Open to Water a Garden|H|Intervals to jumps, greedy reach|X
15|1296|Divide Array in Sets of K Consecutive Numbers|M|Sorted counts, build from min|X
16|986|Interval List Intersections|M|Two pointers over sorted lists|X
16|1094|Car Pooling|M|Difference array / sweep|X
16|646|Maximum Length of Pair Chain|M|Sort by end, greedy|X
16|729|My Calendar I|M|Ordered map, check neighbours|X
16|352|Data Stream as Disjoint Intervals|H|Ordered map merge on insert|X
16|218|The Skyline Problem|H|Sweep line + max-heap|X
17|59|Spiral Matrix II|M|Shrinking boundaries (write)|X
17|415|Add Strings|E|Right-to-left carry|X
17|29|Divide Two Integers|M|Doubling subtraction, overflow care|X
17|204|Count Primes|M|Sieve of Eratosthenes|X
17|168|Excel Sheet Column Title|E|Base-26 with no zero digit|X
17|372|Super Pow|M|Modular exponent digit by digit|X
17|867|Transpose Matrix|E|Index swap into a new matrix|X
17|939|Minimum Area Rectangle|M|Point set, fix the diagonal|X
18|231|Power of Two|E|n & (n - 1) == 0|X
18|260|Single Number III|M|XOR all, split by lowest set bit|X
18|461|Hamming Distance|E|popcount(x ^ y)|X
18|477|Total Hamming Distance|M|Per-bit ones x zeros|X
19|460|LFU Cache|H|Key map + frequency lists|X
19|716|Max Stack|H|Two stacks / list + ordered map|X
19|362|Design Hit Counter|M|Queue / circular buckets|X
19|348|Design Tic-Tac-Toe|M|Row/col/diagonal counters|X
19|622|Design Circular Queue|M|Array ring buffer|X
19|706|Design HashMap|E|Buckets with chaining|X
20|307|Range Sum Query - Mutable|M|Fenwick tree / segment tree|X
20|315|Count of Smaller Numbers After Self|H|Fenwick over ranks / merge sort|X
20|493|Reverse Pairs|H|Merge sort count / Fenwick|X
20|732|My Calendar III|H|Sweep with ordered map / segment tree|X
20|715|Range Module|H|Ordered map of disjoint intervals|X
"""

DIFF = {"E": "Easy", "M": "Medium", "H": "Hard"}
DORDER = {"E": 0, "M": 1, "H": 2}

rows = []
for line in DATA.strip().splitlines():
    t, num, title, d, pat, lists = line.split("|")
    rows.append((int(t), int(num), title, d, pat, lists))

nums = Counter(r[1] for r in rows)
dups = [n for n, c in nums.items() if c > 1]
nc = sum("N" in r[5] for r in rows)
ti = sum("T" in r[5] for r in rows)
both = sum(r[5] == "NT" for r in rows)
xx = sum("X" in r[5] for r in rows)
if dups or nc != 150 or ti != 150:
    sys.exit(f"bad data: dups={dups} nc={nc} ti={ti}")

total = len(rows)
done = sum(r[1] in DONE for r in rows)
unindexed = sorted(set(DONE) - set(nums))
if unindexed:
    print(f"warning: folders not in the index: {unindexed}", file=sys.stderr)


def lists_str(s):
    return ", ".join(x for x, f in (("NC150", "N"), ("TI150", "T"), ("Extra", "X")) if f in s)


out = []
out.append("# DSA-4-Interview\n")
out.append("Personal DSA interview revision repo. Each problem has an interview-style README plus C++ and Python solutions (Go too for problems added before November 2026). See [CLAUDE.md](CLAUDE.md) for conventions.\n")
out.append("## Progress\n")
out.append("| List | Problems | Done |")
out.append("|------|---------:|-----:|")
out.append(f"| NeetCode 150 (NC150) | {nc} | {sum(1 for r in rows if 'N' in r[5] and r[1] in DONE)} |")
out.append(f"| LeetCode Top Interview 150 (TI150) | {ti} | {sum(1 for r in rows if 'T' in r[5] and r[1] in DONE)} |")
out.append(f"| In both lists | {both} | {sum(1 for r in rows if r[5] == 'NT' and r[1] in DONE)} |")
out.append(f"| Wave 2: Interview Extras ([plan](PLAN-wave2.md)) | {xx} | {sum(1 for r in rows if 'X' in r[5] and r[1] in DONE)} |")
out.append(f"| **Unique total** | **{total}** | **{done}** |")
out.append("")
out.append("Cheatsheets: [patterns](cheatsheets/patterns.md) · [syntax](cheatsheets/syntax.md)\n")
out.append("## Topics\n")
out.append("| Topic | Core (NC150/TI150) | Core done | Wave 2 | Wave 2 done |")
out.append("|-------|---------:|-----:|---------:|-----:|")


def is_x(r):
    return r[5] == "X"


def topic_link(folder, name):
    label = f"{folder[:2]}. {name}"
    return f"[{label}](topics/{folder}/)" if (ROOT / "topics" / folder).is_dir() else label


for i, (folder, name) in enumerate(TOPICS, 1):
    core = [r for r in rows if r[0] == i and not is_x(r)]
    ext = [r for r in rows if r[0] == i and is_x(r)]
    core_done = sum(r[1] in DONE for r in core)
    ext_done = sum(r[1] in DONE for r in ext)
    out.append(f"| {topic_link(folder, name)} | {len(core) or '–'} | {core_done if core else '–'} | {len(ext)} | {ext_done} |")
out.append("")
out.append("Status: ✅ done · ⬜ not added yet. Within each table, problems are sorted Easy → Hard, then by number.\n")


def table(tr):
    lines = ["| # | Problem | Difficulty | Pattern | Lists | Status |",
             "|---|---------|------------|---------|-------|--------|"]
    for _, num, title, d, pat, lists in sorted(tr, key=lambda r: (DORDER[r[3]], r[1])):
        prob = f"[{title}]({DONE[num]})" if num in DONE else title
        status = "✅" if num in DONE else "⬜"
        lines.append(f"| {num:04d} | {prob} | {DIFF[d]} | {pat} | {lists_str(lists)} | {status} |")
    return lines


for i, (folder, name) in enumerate(TOPICS, 1):
    core = [r for r in rows if r[0] == i and not is_x(r)]
    ext = [r for r in rows if r[0] == i and is_x(r)]
    out.append(f"## {folder[:2]}. {name}\n")
    if core:
        out.append(f"**Core (NC150 / TI150):** {sum(r[1] in DONE for r in core)}/{len(core)} done\n")
        out += table(core)
        out.append("")
    if ext:
        out.append(f"**Wave 2 extras:** {sum(r[1] in DONE for r in ext)}/{len(ext)} done\n")
        out += table(ext)
        out.append("")

(ROOT / "README.md").write_text("\n".join(out))
print(f"README.md: nc={nc} ti={ti} both={both} extras={xx} total={total} done={done}")
