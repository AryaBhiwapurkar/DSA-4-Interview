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
]


def find_done() -> dict[int, str]:
    """LC number -> relative folder path, for every problem folder on disk."""
    done: dict[int, str] = {}
    for d in sorted((ROOT / "topics").glob("*/[0-9][0-9][0-9][0-9]-*")):
        if d.is_dir():
            done[int(d.name[:4])] = d.relative_to(ROOT).as_posix() + "/"
    return done


DONE = find_done()

# topic | number | title | difficulty | pattern | lists (N = NeetCode 150, T = Top Interview 150)
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
if dups or nc != 150 or ti != 150:
    sys.exit(f"bad data: dups={dups} nc={nc} ti={ti}")

total = len(rows)
done = sum(r[1] in DONE for r in rows)
unindexed = sorted(set(DONE) - set(nums))
if unindexed:
    print(f"warning: folders not in the index: {unindexed}", file=sys.stderr)


def lists_str(s):
    return ", ".join(x for x, f in (("NC150", "N"), ("TI150", "T")) if f in s)


out = []
out.append("# DSA-4-Interview\n")
out.append("Personal DSA interview revision repo. Each problem has an interview-style README plus C++, Python, and Go solutions. See [CLAUDE.md](CLAUDE.md) for conventions.\n")
out.append("## Progress\n")
out.append("| List | Problems | Done |")
out.append("|------|---------:|-----:|")
out.append(f"| NeetCode 150 (NC150) | {nc} | {sum(1 for r in rows if 'N' in r[5] and r[1] in DONE)} |")
out.append(f"| LeetCode Top Interview 150 (TI150) | {ti} | {sum(1 for r in rows if 'T' in r[5] and r[1] in DONE)} |")
out.append(f"| In both lists | {both} | {sum(1 for r in rows if r[5] == 'NT' and r[1] in DONE)} |")
out.append(f"| **Unique total** | **{total}** | **{done}** |")
out.append("")
out.append("Cheatsheets: [patterns](cheatsheets/patterns.md) · [syntax](cheatsheets/syntax.md)\n")
out.append("## Topics\n")
out.append("| Topic | Problems | Done |")
out.append("|-------|---------:|-----:|")
for i, (folder, name) in enumerate(TOPICS, 1):
    tr = [r for r in rows if r[0] == i]
    out.append(f"| [{folder[:2]}. {name}](topics/{folder}/) | {len(tr)} | {sum(r[1] in DONE for r in tr)} |")
out.append("")
out.append("Status: ✅ done · ⬜ not added yet. Within each topic, problems are sorted Easy → Hard, then by number.\n")

for i, (folder, name) in enumerate(TOPICS, 1):
    tr = sorted((r for r in rows if r[0] == i), key=lambda r: (DORDER[r[3]], r[1]))
    out.append(f"## {folder[:2]}. {name}\n")
    out.append("| # | Problem | Difficulty | Pattern | Lists | Status |")
    out.append("|---|---------|------------|---------|-------|--------|")
    for _, num, title, d, pat, lists in tr:
        prob = f"[{title}]({DONE[num]})" if num in DONE else title
        status = "✅" if num in DONE else "⬜"
        out.append(f"| {num:04d} | {prob} | {DIFF[d]} | {pat} | {lists_str(lists)} | {status} |")
    out.append("")

(ROOT / "README.md").write_text("\n".join(out))
print(f"README.md: nc={nc} ti={ti} both={both} total={total} done={done}")
