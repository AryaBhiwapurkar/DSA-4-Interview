---
number: 207
title: Course Schedule
difficulty: Medium
topic: Graphs
pattern: Cycle detection / Kahn's
link: https://leetcode.com/problems/course-schedule/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0210 Course Schedule II", "0269 Alien Dictionary", "0630 Course Schedule III", "1462 Course Schedule IV"]
---

# 0207. Course Schedule

## ⚡ 30-Second Summary
**Pattern:** Topological sort / cycle detection in a directed graph
**Key insight:** All courses can be finished iff the prerequisite graph has no cycle. Kahn's algorithm repeatedly takes a course with no remaining prerequisites; if it manages to take all n, there's no cycle.
**Go-to:** Kahn's BFS on in-degrees, O(V + E) time, O(V + E) space

## Problem
There are n courses 0..n-1 and a list of pairs [a, b] meaning "b must be taken before a". Decide whether it's possible to take every course. [LeetCode](https://leetcode.com/problems/course-schedule/)

**Examples:**
```
Input:  numCourses = 2, prerequisites = [[1,0]]
Output: true
Why:    Take 0, then 1.

Input:  numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Why:    Each course waits for the other: a cycle.
```

**Constraints:**
- 1 ≤ n ≤ 2000, up to 5000 pairs, all pairs distinct.

## Hints
<details><summary>Hint 1</summary>
Draw courses as nodes and prerequisites as arrows. What shape makes the schedule impossible?
</details>
<details><summary>Hint 2</summary>
Which courses can you take right now? What happens to the others after you take them?
</details>
<details><summary>Hint 3</summary>
Count incoming edges. Queue every course with in-degree 0; pop, count it, decrement its neighbours, queue any that reach 0. Answer: count == n.
</details>

## Clarifying Questions
- Direction of [a, b]? (b → a: b first.)
- Can there be courses with no prerequisites at all? (Yes, they start with in-degree 0.)
- Self-loops like [1,1]? (Would be a cycle; Kahn's handles it naturally.)

## Example Walkthrough
`n = 2, [[1,0]]`: edge 0 → 1. In-degrees [0, 1]. Take 0, which drops 1 to 0; take 1. Took 2 of 2 → true.
`[[1,0],[0,1]]`: in-degrees [1, 1]. Nothing to start with → took 0 → false.

## Approaches

### 1. DFS Three-Color Cycle Detection: O(V + E) time, O(V + E) space
Colors: 0 unvisited, 1 on the current path, 2 done. Reaching a node colored 1 means a back edge, which means a cycle.

### 2. Kahn's Algorithm ⭐ Go-to: O(V + E) time, O(V + E) space
BFS from all in-degree-0 nodes, peeling them off.
**Why it's the go-to:** iterative (no recursion depth), and the same code returns the order for 0210.

## Dry Run (Approach 2)
`n = 4, [[1,0],[2,1],[3,2],[1,3]]` (cycle 1 → 2 → 3 → 1)

| step | queue | pop | taken | in-degree after (0,1,2,3) |
|------|-------|-----|-------|---------------------------|
| init | [0] | | 0 | 0, 2, 1, 1 |
| 1 | [] | 0 | 1 | 0, 1, 1, 1 (1 still waits on 3) |
| end | [] | | 1 | 1 < 4 → **false** |

## Edge Case Check
- No prerequisites: every course has in-degree 0 → true. ✅
- Self-dependency [0,0]: in-degree never reaches 0 → false. ✅
- Disconnected components: Kahn's starts from every in-degree-0 node, so all are covered. ✅

## ⚠️ Pitfalls
- **Edge direction reversed**: [a, b] means b → a. Reversing gives the same yes/no here, but the wrong order in 0210.
- **DFS with only a visited set** (two colors) reports false cycles on diamonds (0→1, 0→2, 1→3, 2→3).
- **Python recursion** on a 2000-long chain: Kahn's avoids it.
- **Go:** `make([][]int, n)` then append per node; a nil inner slice is fine to append to.

## 🎯 What the Interviewer Wants
- Model as a directed graph, reduce to "is there a cycle?".
- One clean method (Kahn's or 3-color DFS) and the reason two colors aren't enough.

## Follow-ups
- **Return an order:** [LC 0210 Course Schedule II](../0210-course-schedule-ii/)
- **Order of letters from a sorted dictionary:** [LC 0269 Alien Dictionary](../../12-advanced-graphs/0269-alien-dictionary/)
- **Answer many "is a a prerequisite of b?" queries:** LC 1462 Course Schedule IV (not added yet), transitive closure.
