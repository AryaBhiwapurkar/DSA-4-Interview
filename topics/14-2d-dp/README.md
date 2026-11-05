# 14. 2-D Dynamic Programming

## Core Idea
Same recipe as 1-D DP, but the state needs two numbers: a grid cell (r, c), two prefix lengths (i, j), an interval (l, r), or a position plus a small mode (day, holding / transactions left). Write the state as a sentence ("dp[i][j] = answer for a[:i] and b[:j]"), take the recurrence from the **last** decision, and fix the empty-prefix / first-row base cases. Most 2-D tables only read the previous row, so they roll down to O(n) space; the loop direction (forward or backward) decides whether a value is "this row" or "last row".

## When to Use
- Moves only right/down in a grid: grid DP from top and left (0062, 0063, 0064, 0221).
- Two strings compared or aligned: dp over prefix pairs (1143, 0072, 0097, 0115, 0010).
- Triangle / pyramid: fold bottom-up so every cell has two children (0120).
- Buy/sell rules (cooldown, k transactions): state machine per day (0309, 0123, 0188).
- Count combinations to reach a sum: knapsack with an item dimension (0518, 0494).
- Merging or bursting where cost depends on neighbours: interval DP, pick the last split (0312).
- Grid with "strictly increasing" moves: DFS + memo on a DAG (0329).

## Templates

### Grid DP, rolling row
```cpp
vector<int> row(n, INF); row[0] = 0;
for (auto& cells : grid) {
    row[0] += cells[0];
    for (int c = 1; c < n; c++) row[c] = cells[c] + min(row[c], row[c - 1]);   // top vs left
}
```
```python
row = [0] + [INF] * (n - 1)
for cells in grid:
    row[0] += cells[0]
    for c in range(1, n):
        row[c] = cells[c] + min(row[c], row[c - 1])
```

### Two strings over prefixes
```cpp
vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));   // row/col 0 = empty prefix
for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
        dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1   // LCS shown; edit distance,
                                        : max(dp[i - 1][j], dp[i][j - 1]);   // counting etc. change this line
```
```python
dp = [[0] * (n + 1) for _ in range(m + 1)]
for i in range(1, m + 1):
    for j in range(1, n + 1):
        dp[i][j] = dp[i-1][j-1] + 1 if a[i-1] == b[j-1] else max(dp[i-1][j], dp[i][j-1])
```

### Stock state machine (k transactions)
```python
buy, sell = [-inf] * (k + 1), [0] * (k + 1)
for p in prices:
    for j in range(1, k + 1):
        buy[j] = max(buy[j], sell[j - 1] - p)
        sell[j] = max(sell[j], buy[j] + p)
return sell[k]
```

### Interval DP (choose the last split)
```python
@cache
def best(l, r):                                   # open interval (l, r)
    return max((cost(l, k, r) + best(l, k) + best(k, r) for k in range(l + 1, r)), default=0)
```

### Memo on suffixes (pattern matching)
```python
@cache
def go(i, j):                                     # s[i:] vs p[j:]
    if j == len(p): return i == len(s)
    first = i < len(s) and p[j] in (s[i], ".")
    if j + 1 < len(p) and p[j + 1] == "*":
        return go(i, j + 2) or (first and go(i + 1, j))
    return first and go(i + 1, j + 1)
```

## Common Variations
- **Obstacles:** a blocked cell is 0 (count) or infinity (cost); don't hardcode the first row (0063).
- **Square / shape ending here:** 1 + min of the three neighbours (0221).
- **Counting matches:** add instead of max, and dp[i][0] = 1 (0115).
- **Algebra first:** turn ± signs into a subset sum, P = (total + target) / 2 (0494).
- **Loop order controls counting:** coins outside = combinations (0518), amount outside = permutations (377).
- **Unbounded k:** if 2k ≥ n, sum every rise (0188).

## ⚠️ Pitfalls
- **Fuzzy state:** say whether dp[i] is "first i" (prefix length) or "index i" before writing code.
- **Base row/column:** edit distance needs i and j, not 0; counting DPs need 1 for the empty target.
- **Rolling arrays:** forward vs backward sweep changes whether a value is this row or last row. Save the diagonal before overwriting.
- **C++ overflow in counting DPs:** intermediates can exceed the guaranteed answer (0063, 0518, 0115). Use `long long` or `unsigned long long`.
- **Python recursion limits** on memo over m + n or m·n depth; raise the limit or go bottom-up.
- **Greedy temptations:** grid paths, triangle and interleaving all have small counterexamples.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0062 | [Unique Paths](0062-unique-paths/) | Medium | Grid DP | ✅ |
| 0063 | [Unique Paths II](0063-unique-paths-ii/) | Medium | Grid DP with obstacles | ✅ |
| 0064 | [Minimum Path Sum](0064-minimum-path-sum/) | Medium | Grid DP | ✅ |
| 0072 | [Edit Distance](0072-edit-distance/) | Medium | Two-string DP | ✅ |
| 0097 | [Interleaving String](0097-interleaving-string/) | Medium | Two-string DP | ✅ |
| 0120 | [Triangle](0120-triangle/) | Medium | Bottom-up DP | ✅ |
| 0221 | [Maximal Square](0221-maximal-square/) | Medium | Grid DP, min of 3 neighbors | ✅ |
| 0309 | [Best Time to Buy and Sell Stock with Cooldown](0309-best-time-to-buy-and-sell-stock-with-cooldown/) | Medium | State machine DP | ✅ |
| 0494 | [Target Sum](0494-target-sum/) | Medium | Subset-sum DP / memo | ✅ |
| 0518 | [Coin Change II](0518-coin-change-ii/) | Medium | Unbounded knapsack (count) | ✅ |
| 1143 | [Longest Common Subsequence](1143-longest-common-subsequence/) | Medium | Two-string DP | ✅ |
| 0010 | [Regular Expression Matching](0010-regular-expression-matching/) | Hard | Two-string DP with star | ✅ |
| 0115 | [Distinct Subsequences](0115-distinct-subsequences/) | Hard | Two-string DP | ✅ |
| 0123 | [Best Time to Buy and Sell Stock III](0123-best-time-to-buy-and-sell-stock-iii/) | Hard | State machine DP (2 txns) | ✅ |
| 0188 | [Best Time to Buy and Sell Stock IV](0188-best-time-to-buy-and-sell-stock-iv/) | Hard | State machine DP (k txns) | ✅ |
| 0312 | [Burst Balloons](0312-burst-balloons/) | Hard | Interval DP (last to burst) | ✅ |
| 0329 | [Longest Increasing Path in a Matrix](0329-longest-increasing-path-in-a-matrix/) | Hard | DFS + memo | ✅ |
