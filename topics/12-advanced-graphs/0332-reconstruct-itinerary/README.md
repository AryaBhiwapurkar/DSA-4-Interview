---
number: 332
title: Reconstruct Itinerary
difficulty: Hard
topic: Advanced Graphs
pattern: Hierholzer (Eulerian path)
link: https://leetcode.com/problems/reconstruct-itinerary/
lists: [NeetCode 150]
followup_of: []
related: ["2097 Valid Arrangement of Pairs", "0753 Cracking the Safe"]
---

# 0332. Reconstruct Itinerary

## ⚡ 30-Second Summary
**Pattern:** Eulerian path (use every edge exactly once)
**Key insight:** Greedy "always fly to the smallest airport" can strand you. Hierholzer fixes it: DFS that takes the smallest edge each time, and adds an airport to the route only **after** all its edges are used (post-order). Dead ends land at the end of the reversed route, which is exactly where they belong.
**Go-to:** Hierholzer with sorted adjacency lists, O(E log E) time, O(E) space

## Problem
Each ticket is `[from, to]`. All tickets belong to one traveller who starts at "JFK". Reconstruct the itinerary that uses every ticket exactly once. If several are valid, return the one that is smallest when read as a sequence of strings. At least one valid itinerary is guaranteed. [LeetCode](https://leetcode.com/problems/reconstruct-itinerary/)

**Examples:**
```
Input:  tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
Why:    Every airport has at most one outgoing ticket, so there's only one chain.

Input:  tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Why:    JFK→SFO→ATL→JFK→ATL→SFO also uses every ticket, but ATL < SFO at the second position.
```

**Constraints:**
- Up to 300 tickets; airport codes are 3 uppercase letters.
- A valid itinerary using all tickets always exists. Duplicate tickets are possible.

## Hints
<details><summary>Hint 1</summary>
Airports are nodes, tickets are edges, and you must use every edge once. What is that kind of path called?
</details>
<details><summary>Hint 2</summary>
Try tickets `JFK→KUL, JFK→NRT, NRT→JFK`. Greedy smallest-first goes to KUL and gets stuck. Where in the itinerary must a dead end like KUL go?
</details>
<details><summary>Hint 3</summary>
DFS from JFK: while the current airport has unused tickets, take the smallest and recurse. When an airport has none left, append it to the route. Reverse the route at the end.
</details>

## Clarifying Questions
- Is a valid itinerary guaranteed? (Yes.)
- Can the same ticket appear twice? (Yes, use each copy once.)
- "Smallest" means comparing the airport sequence lexicographically? (Yes.)
- Always start at JFK? (Yes.)

## Example Walkthrough
Extra case: `[["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]`.
Greedy: JFK→KUL, then stuck with two tickets unused. The right answer flies to NRT first, comes back, then ends at KUL: JFK→NRT→JFK→KUL. Hierholzer gets there automatically: KUL finishes first (it's a dead end), so it ends up **last** after reversing.

## Approaches

### 1. Backtracking: exponential worst case, O(E) space
Sort destinations; DFS tries the smallest unused ticket first and undoes it if it can't complete a full path. The first complete path is the answer. Fine for 300 tickets in practice, but the worst case blows up.

### 2. Hierholzer ⭐ Go-to: O(E log E) time, O(E) space
Post-order DFS with destinations popped in sorted order. Each ticket is used once, and the sort dominates.
**Why it's the go-to:** no undo logic, provably linear after sorting, and the code is about 8 lines.

## Dry Run (Approach 2)
Extra case. Lists sorted descending so `pop()` gives the smallest: JFK: [NRT, KUL], NRT: [JFK].

| call | action | JFK list | NRT list | route |
|------|--------|----------|----------|-------|
| visit(JFK) | pop KUL | [NRT] | [JFK] | [] |
| visit(KUL) | no tickets, append | [NRT] | [JFK] | [KUL] |
| back in JFK | pop NRT | [] | [JFK] | [KUL] |
| visit(NRT) | pop JFK | [] | [] | [KUL] |
| visit(JFK) | no tickets, append | [] | [] | [KUL, JFK] |
| back in NRT | done, append | | | [KUL, JFK, NRT] |
| back in JFK | done, append | | | [KUL, JFK, NRT, JFK] |

Reversed: **[JFK, NRT, JFK, KUL]**.

## Edge Case Check
- Single chain (example 1): each pop has one option → straight path. ✅
- Duplicate tickets (`JFK→A` twice): both copies sit in the list and get popped once each. ✅
- Dead end reached first (extra case): post-order places it last. ✅

## ⚠️ Pitfalls
- **Appending on entry (pre-order)** instead of after the while loop gives the greedy answer, which can be invalid.
- **Forgetting to reverse** the route.
- **C++ reference to `dests.back()`** dangles after `pop_back()`: copy the string first.
- **Using a set for destinations** drops duplicate tickets; use a sorted list or multiset.

## 🎯 What the Interviewer Wants
- Model it as an Eulerian path.
- Explain why greedy fails (the dead-end example) and why post-order fixes it.
- Clean Hierholzer code with the sorted-descending + pop trick.

## Follow-ups
- **Find any Eulerian path given arbitrary pairs:** LC 2097 Valid Arrangement of Pairs (not added yet). Pick the start node with out - in = 1.
- **De Bruijn sequence via Eulerian circuit:** LC 0753 Cracking the Safe (not added yet)
- **When does an Eulerian path exist?** Connected, and all nodes have in = out except possibly a start (out - in = 1) and an end (in - out = 1).
