# 13. 1-D Dynamic Programming

## Core Idea
DP = recursion over overlapping subproblems, with each answer computed once. The work is choosing a **state** (usually one index or one amount: "the answer for the first i items" or "for amount a"), writing the **recurrence** from the last decision (last step, last coin, take/skip the last house), and fixing the **base cases**. Then pick a direction: top-down (recursion + memo, closest to the reasoning) or bottom-up (a loop over the table, no recursion limit). When dp[i] only reads the last one or two entries, roll it into variables for O(1) space.

## When to Use
- "Count the ways" / "min cost" to reach position n with small moves: dp[i] from dp[i-1], dp[i-2] (0070, 0746, 0091).
- Choose items with a "no two adjacent" rule: take/skip (0198, 0213).
- Fewest items to reach a total, items reusable: unbounded knapsack (0322).
- Reach an exact sum, each item once: 0/1 knapsack, sweep the sum backwards (0416).
- Can a string be cut into valid pieces: prefix DP over split points (0139, 0091).
- Best subarray ending here, with sign flips: track max and min (0152).
- Longest subsequence with an order property: dp ending at i, or tails + binary search (0300).
- Palindromic substrings: expand around 2n-1 centers (0005, 0647).

## Templates

### Rolling two-term recurrence
```cpp
int prev2 = base0, prev1 = base1;
for (int i = 2; i <= n; i++) {
    int cur = combine(prev1, prev2, i);              // e.g. prev1 + prev2, max(prev1, prev2 + x)
    prev2 = prev1;
    prev1 = cur;
}
return prev1;
```
```python
prev2, prev1 = base0, base1
for i in range(2, n + 1):
    prev2, prev1 = prev1, combine(prev1, prev2, i)
return prev1
```

### Unbounded knapsack (min count) vs 0/1 knapsack (reachable)
```cpp
vector<int> dp(amount + 1, amount + 1); dp[0] = 0;  // unbounded: sums ascending
for (int a = 1; a <= amount; a++)
    for (int c : coins) if (c <= a) dp[a] = min(dp[a], dp[a - c] + 1);

vector<bool> can(S + 1, false); can[0] = true;     // 0/1: sums descending
for (int x : nums)
    for (int s = S; s >= x; s--) if (can[s - x]) can[s] = true;
```

### Top-down memo
```python
@cache
def f(i):
    if i >= n:
        return base
    return best(f(i + 1), value(i) + f(i + 2))      # skip i / take i
```

### Expand around center
```python
def expand(l, r):
    while l >= 0 and r < len(s) and s[l] == s[r]:
        l -= 1; r += 1
    return r - l - 1                                 # length of s[l+1:r]
for i in range(len(s)):
    best = max(best, expand(i, i), expand(i, i + 1)) # odd and even centers
```

### LIS with tails
```python
tails = []
for x in nums:
    k = bisect_left(tails, x)                        # bisect_right for non-decreasing
    tails[k:k + 1] = [x]                             # replace or append
return len(tails)
```

## Common Variations
- **Circular array:** solve two lines, without the first and without the last (0213).
- **Validity-gated transitions:** add dp[i-1] or dp[i-2] only when the step is legal, e.g. no '0' alone, pair in 10..26 (0091).
- **Count combinations vs permutations:** coin loop outside = combinations (518); amount loop outside = permutations (377).
- **Bitset subset sum:** `bits |= bits << x` (0416).
- **Max/min pair state:** products, or any recurrence where a sign flip swaps the best and the worst (0152).
- **Reconstruct the answer:** store parent choices next to dp values.

## ⚠️ Pitfalls
- **Fuzzy state definitions:** write "dp[i] = … for the first i items" before coding. Most off-by-ones come from here.
- **Wrong base case:** dp[0] = 1 for counting, 0 for min cost; the "top" in 0746 is index n.
- **Loop direction in knapsack:** ascending reuses items, descending uses each once.
- **C++ infinity overflow:** `INT_MAX + 1` wraps; use amount + 1 or check before adding.
- **Python recursion limit (~1000):** memoized recursion over 10⁴ states can crash; go bottom-up.
- **Greedy temptation:** coin change, house robber and word break all have small greedy counterexamples.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0070 | [Climbing Stairs](0070-climbing-stairs/) | Easy | Fibonacci DP | ✅ |
| 0746 | [Min Cost Climbing Stairs](0746-min-cost-climbing-stairs/) | Easy | Linear DP | ✅ |
| 0005 | [Longest Palindromic Substring](0005-longest-palindromic-substring/) | Medium | Expand around center | ✅ |
| 0091 | [Decode Ways](0091-decode-ways/) | Medium | Linear DP on 1/2 digits | ✅ |
| 0139 | [Word Break](0139-word-break/) | Medium | Prefix DP + dictionary | ✅ |
| 0152 | [Maximum Product Subarray](0152-maximum-product-subarray/) | Medium | Track max & min | ✅ |
| 0198 | [House Robber](0198-house-robber/) | Medium | Take/skip DP | ✅ |
| 0213 | [House Robber II](0213-house-robber-ii/) | Medium | Two passes of House Robber | ✅ |
| 0300 | [Longest Increasing Subsequence](0300-longest-increasing-subsequence/) | Medium | DP / patience sort + binary search | ✅ |
| 0322 | [Coin Change](0322-coin-change/) | Medium | Unbounded knapsack (min) | ✅ |
| 0416 | [Partition Equal Subset Sum](0416-partition-equal-subset-sum/) | Medium | 0/1 knapsack subset sum | ✅ |
| 0647 | [Palindromic Substrings](0647-palindromic-substrings/) | Medium | Expand around center | ✅ |
