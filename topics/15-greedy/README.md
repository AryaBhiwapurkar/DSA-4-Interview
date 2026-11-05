# 15. Greedy

## Core Idea
A greedy algorithm makes the locally best choice at each step and never revisits it. It's correct only when you can argue that some optimal answer agrees with that choice. The usual arguments are an **exchange argument** (swapping your choice into any optimal solution doesn't make it worse) or an **invariant** (the "reachable prefix" stays a prefix, a negative running sum never helps). Most greedy problems here are one linear pass tracking one or two running values; the hard part is the proof, not the code.

## When to Use
- Best contiguous sum: drop a negative running prefix (Kadane: 0053, 0918).
- "Can I reach / how few steps": track the farthest reach, or BFS levels without a queue (0055, 0045).
- Circular route with a running balance: reset the start when the balance goes negative (0134).
- Grouping sorted values into runs: the smallest remaining item must start a group (0846).
- Cut a sequence as early as possible: extend a boundary to each element's last occurrence (0763).
- Wildcards with many interpretations: track the range of possible states (0678).
- Unlimited trades: collect every rise (0122).
- Two-sided neighbour constraints: one pass per side, combine with max (0135).
- Filter-then-merge with monotone operations: discard anything that overshoots (1899).

## Templates

### Kadane
```cpp
int best = nums[0], cur = nums[0];
for (int i = 1; i < n; i++) {
    cur = max(nums[i], cur + nums[i]);   // extend or restart
    best = max(best, cur);
}
```
```python
best = cur = nums[0]
for x in nums[1:]:
    cur = max(x, cur + x)
    best = max(best, cur)
```

### Farthest reach / BFS levels
```python
jumps = end = farthest = 0
for i in range(len(nums) - 1):
    farthest = max(farthest, i + nums[i])
    if i == end:                          # level finished
        jumps += 1
        end = farthest
```

### Running balance with reset
```python
start = tank = 0
for i, d in enumerate(deltas):
    tank += d
    if tank < 0:
        start, tank = i + 1, 0
return start if sum(deltas) >= 0 else -1
```

### Range of possible states
```python
lo = hi = 0
for ch in s:
    lo += 1 if ch == "(" else -1
    hi += -1 if ch == ")" else 1
    if hi < 0: return False
    lo = max(lo, 0)
return lo == 0
```

## Common Variations
- **Circular arrays:** total minus the worst block (0918) or a total-balance check (0134).
- **Greedy + sort:** sort first so the "smallest/earliest" choice is cheap to find (0846, intervals).
- **Two passes:** left-to-right and right-to-left, combined with max/min (0135, also 0042 and 0238).
- **Greedy vs DP:** when a greedy fails (caps, fees, cooldowns), fall back to a state-machine DP (0122 vs 0309/0188).

## ⚠️ Pitfalls
- **No proof:** if you can't sketch an exchange argument or invariant, try a small counterexample before coding.
- **Seeding with 0** in Kadane-style code breaks all-negative inputs; seed with the first element.
- **Off-by-one at the end:** Jump Game II must not count a jump from the last index.
- **Forgetting the global feasibility check** (gas total, divisibility in 0846) before the greedy pass.
- **C++ `map[]` insertion** while iterating an ordered map; use `find`.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0045 | [Jump Game II](0045-jump-game-ii/) | Medium | BFS-style level greedy | ✅ |
| 0053 | [Maximum Subarray](0053-maximum-subarray/) | Medium | Kadane | ✅ |
| 0055 | [Jump Game](0055-jump-game/) | Medium | Track farthest reach | ✅ |
| 0122 | [Best Time to Buy and Sell Stock II](0122-best-time-to-buy-and-sell-stock-ii/) | Medium | Sum positive deltas | ✅ |
| 0134 | [Gas Station](0134-gas-station/) | Medium | Reset start on negative tank | ✅ |
| 0678 | [Valid Parenthesis String](0678-valid-parenthesis-string/) | Medium | Track min/max open count | ✅ |
| 0763 | [Partition Labels](0763-partition-labels/) | Medium | Last occurrence + window end | ✅ |
| 0846 | [Hand of Straights](0846-hand-of-straights/) | Medium | Sorted counts, build from min | ✅ |
| 0918 | [Maximum Sum Circular Subarray](0918-maximum-sum-circular-subarray/) | Medium | Kadane on max & min | ✅ |
| 1899 | [Merge Triplets to Form Target Triplet](1899-merge-triplets-to-form-target-triplet/) | Medium | Filter valid triplets | ✅ |
| 0135 | [Candy](0135-candy/) | Hard | Two passes L→R, R→L | ✅ |
