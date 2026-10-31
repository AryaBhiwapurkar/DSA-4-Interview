---
number: 210
title: Course Schedule II
difficulty: Medium
topic: Graphs
pattern: Topological sort
link: https://leetcode.com/problems/course-schedule-ii/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0207 Course Schedule"]
related: ["0207 Course Schedule", "0269 Alien Dictionary", "0310 Minimum Height Trees"]
---

# 0210. Course Schedule II

## ⚡ 30-Second Summary
**Pattern:** Topological sort
**Key insight:** 0207's Kahn's algorithm already takes courses in a valid order; record the pop order. If fewer than n courses get popped, a cycle blocks the rest, so return [].
**Go-to:** Kahn's BFS recording pops, O(V + E) time, O(V + E) space

## Problem
n courses 0..n-1 and pairs [a, b] meaning "b before a". Return any order that takes every course, or [] if impossible. [LeetCode](https://leetcode.com/problems/course-schedule-ii/)

**Examples:**
```
Input:  numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Why:    0 has no prerequisite; 1 needs 0.

Input:  numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]   (or [0,1,2,3])
Why:    0 first, then 1 and 2 in either order, then 3, which needs both.

Input:  numCourses = 1, prerequisites = []
Output: [0]
Why:    One course, nothing blocks it.
```

**Constraints:**
- 1 ≤ n ≤ 2000, up to n(n-1) distinct pairs.

## Hints
<details><summary>Hint 1</summary>
You already know how to detect whether an order exists (0207). Where is the order hiding in that algorithm?
</details>
<details><summary>Hint 2</summary>
In Kahn's algorithm, when is it safe to "take" a course?
</details>
<details><summary>Hint 3</summary>
Append each popped node to the result. At the end return the result if its length is n, else [].
</details>

## Clarifying Questions
- Any valid order accepted? (Yes.)
- What to return on a cycle? (Empty list.)

## Example Walkthrough
Example 2 with Kahn's: in-degrees [0,1,1,2]. Pop 0 → 1 and 2 drop to 0. Pop 1 → 3 drops to 1. Pop 2 → 3 drops to 0. Pop 3. Order [0,1,2,3].

## Approaches

### 1. DFS Post-Order: O(V + E) time, O(V + E) space
Three-color DFS; append a node *after* all its descendants finish, then reverse. A back edge (color 1) means a cycle → [].

### 2. Kahn's Algorithm ⭐ Go-to: O(V + E) time, O(V + E) space
Record the order in which in-degree-0 nodes are popped.
**Why it's the go-to:** iterative, the order is produced directly, and cycle detection is a single length check.

## Dry Run (Approach 2)
`n = 4, [[1,0],[2,0],[3,1],[3,2]]`

| pop | order | in-degree changes | queue after |
|-----|-------|-------------------|-------------|
| init | [] | [0,1,1,2] | [0] |
| 0 | [0] | 1 → 0, 2 → 0 | [1, 2] |
| 1 | [0,1] | 3 → 1 | [2] |
| 2 | [0,1,2] | 3 → 0 | [3] |
| 3 | [0,1,2,3] | | [] |

Length 4 = n → return [0,1,2,3]. (DFS post-order gives [0,2,1,3]; both are valid.)

## Edge Case Check
- Cycle (`2, [[1,0],[0,1]]`): nothing has in-degree 0 → []. ✅
- No prerequisites: Kahn's returns 0..n-1. ✅
- Several valid answers: any is accepted. ✅

## ⚠️ Pitfalls
- **Wrong edge direction** gives the reverse of a valid order.
- **DFS: forgetting to reverse** the post-order.
- **Returning the partial order** when there's a cycle instead of [].

## 🎯 What the Interviewer Wants
- Small step from 0207, producing the actual order.
- Both methods known; explain why post-order reversed is a topological order.

## Follow-ups
- **Order of an unknown alphabet:** [LC 0269 Alien Dictionary](../../12-advanced-graphs/0269-alien-dictionary/)
- **Lexicographically smallest order:** Kahn's with a min-heap instead of a queue.
- **Minimum number of semesters (parallel courses):** BFS level count in Kahn's, LC 1136 (not added yet).
