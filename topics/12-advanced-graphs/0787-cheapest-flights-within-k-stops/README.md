---
number: 787
title: Cheapest Flights Within K Stops
difficulty: Medium
topic: Advanced Graphs
pattern: Bellman-Ford, k+1 rounds
link: https://leetcode.com/problems/cheapest-flights-within-k-stops/
lists: [NeetCode 150]
followup_of: []
related: ["0743 Network Delay Time", "1928 Minimum Cost to Reach Destination in Time"]
---

# 0787. Cheapest Flights Within K Stops

## ⚡ 30-Second Summary
**Pattern:** Shortest path with a limit on the number of edges
**Key insight:** "At most k stops" = at most k+1 edges. Round i of Bellman-Ford finds the cheapest path using at most i edges, **as long as each round reads only the previous round's prices**.
**Go-to:** Bellman-Ford with k+1 rounds and a copied array, O(k·E) time, O(n) space

## Problem
There are n cities and directed flights `(from, to, price)`. Find the cheapest price from `src` to `dst` with at most `k` stops in between, or -1 if there is no such route. [LeetCode](https://leetcode.com/problems/cheapest-flights-within-k-stops/)

**Examples:**
```
Input:  n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Why:    0→1→2→3 costs only 400 but needs 2 stops. With one stop, 0→1→3 at 700 is the best.

Input:  n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Why:    One stop is allowed, so 0→1→2 beats the direct 500 flight.

Input:  n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Why:    No stops allowed, so only the direct flight counts.
```

**Constraints:**
- 1 ≤ n ≤ 100, prices up to 10⁴, k < n: sums fit in an int.
- No duplicate flights and no self-loops; src ≠ dst.

## Hints
<details><summary>Hint 1</summary>
Plain Dijkstra finds the cheapest path, but that path might use too many stops. What extra information does each path need?
</details>
<details><summary>Hint 2</summary>
Bellman-Ford's i-th round finds shortest paths using at most i edges. How many rounds do you need?
</details>
<details><summary>Hint 3</summary>
Run k+1 rounds. In each, copy the price array and relax every flight reading from the old array but writing to the copy, so a single round can't chain two flights.
</details>

## Clarifying Questions
- Does k count stops or flights? (Stops: k stops = k+1 flights.)
- Directed flights? (Yes.)
- Can prices be zero or negative? (Positive.)
- If there's no route within k stops, return -1? (Yes.)

## Example Walkthrough
Example 1 with k = 1 (2 flights max):
- After 1 flight: reach 1 at 100.
- After 2 flights: reach 2 at 200 (via 1) and 3 at 700 (via 1). The flight 2→3 must **not** use the 200 found in this same round, otherwise 3 would get 400, which is a 3-flight route.

## Approaches

### 1. Dijkstra on (city, flights used): O(E·k·log(E·k)) time, O(n·k + E) space
Heap of (cost, city, flights). Pop cheapest; the first time dst pops, that's the answer. Skip a state if flights > k or if this city was already popped with fewer flights (it was cheaper too, since pops come in cost order). Fast in practice but subtle to get right.

### 2. Bellman-Ford, k+1 Rounds ⭐ Go-to: O(k·E) time, O(n) space
`price` = cheapest with at most i flights. Each round: copy, relax every edge from old into the copy.
**Why it's the go-to:** ten lines, the stop limit maps directly onto the round count, and there's only one trick (the copy) to explain.

## Dry Run (Approach 2)
Example 1, k = 1. price = [p0, p1, p2, p3].

| round | flight | reads price[u] | next after |
|-------|--------|----------------|------------|
| start | | | [0, ∞, ∞, ∞] |
| 1 | 0→1 (100) | 0 | [0, 100, ∞, ∞] |
| 1 | 1→2, 2→0, 1→3, 2→3 | ∞ (old) | no change |
| 2 | 0→1 (100) | 0 | 100 not < 100 |
| 2 | 1→2 (100) | 100 | [0, 100, 200, ∞] |
| 2 | 2→0 (100) | ∞ (old p2) | no change |
| 2 | 1→3 (600) | 100 | [0, 100, 200, 700] |
| 2 | 2→3 (200) | ∞ (old p2) | **stays 700** |

Answer **700**. Without the copy, 2→3 would read p2 = 200 and write 400.

## Edge Case Check
- No route at all (extra case 1→0): price stays ∞ → -1. ✅
- k = 0: one round, only direct flights (example 3). ✅
- Cycles (2→0): they only add cost, and the round cap bounds them. ✅

## ⚠️ Pitfalls
- **Relaxing in place** lets one round chain several flights, which breaks the stop limit (the 400 vs 700 bug).
- **Off-by-one:** k stops means **k+1** rounds.
- **Plain Dijkstra with a visited set** is wrong: a city reached cheaply with many stops can block a pricier path with fewer stops.
- **C++ overflow:** check `price[u] != INT_MAX` before adding.

## 🎯 What the Interviewer Wants
- Spot why plain Dijkstra fails (the stop count is part of the state).
- Bellman-Ford with the round = flights mapping and the snapshot copy.
- Mention the Dijkstra/BFS-by-level alternatives and their trade-offs.

## Follow-ups
- **No stop limit:** plain Dijkstra, [LC 0743 Network Delay Time](../0743-network-delay-time/)
- **Limit on total time instead of stops:** LC 1928 Minimum Cost to Reach Destination in Time (not added yet). Dijkstra with time in the state.
- **BFS by levels:** process one level per stop and relax costs. Also O(k·E), and the same idea as the rounds here.
