# 10. Backtracking

## Core Idea
Backtracking is DFS over a tree of choices: at each step **choose** an option, **explore** the rest recursively, then **unchoose** so the next option starts from a clean state. Shared mutable state (a path, a `used[]` array, a marked grid) keeps memory at O(depth). The art is in two things: a rule that generates each answer **exactly once** (start index, sorted skip, fixed row order) and **pruning** that abandons a branch as soon as it can't succeed.

## When to Use
- "Return all ..." combinations, subsets, permutations, partitions (0078, 0077, 0046, 0131).
- Pick items to hit a target sum, with or without reuse (0039, 0040).
- Placing things under constraints on a board (0051, 0052, Sudoku).
- Find a path in a grid where cells can't repeat (0079).
- Inputs are small (n ≤ ~20, or output-bound), so exponential time is expected.

## Templates

### Subsets / combinations (start index)
```cpp
void dfs(int start, vector<int>& path) {
    res.push_back(path);                       // subsets: save at every node
    for (int i = start; i < n; i++) {
        if (i > start && a[i] == a[i - 1]) continue;   // only if input has duplicates (sorted)
        path.push_back(a[i]);
        dfs(i + 1, path);                      // i for unlimited reuse
        path.pop_back();
    }
}
```
```python
def dfs(start: int) -> None:
    res.append(path[:])                        # copy!
    for i in range(start, len(a)):
        if i > start and a[i] == a[i - 1]:
            continue
        path.append(a[i])
        dfs(i + 1)
        path.pop()
```
```go
var dfs func(start int)
dfs = func(start int) {
	res = append(res, slices.Clone(path)) // copy!
	for i := start; i < len(a); i++ {
		if i > start && a[i] == a[i-1] {
			continue
		}
		path = append(path, a[i])
		dfs(i + 1)
		path = path[:len(path)-1]
	}
}
```

### Permutations (used[])
```python
def dfs() -> None:
    if len(path) == n:
        res.append(path[:])
        return
    for i in range(n):
        if used[i]:
            continue
        used[i] = True; path.append(a[i])
        dfs()
        path.pop(); used[i] = False
```

### Grid path (mark in place)
```python
def dfs(r, c, i):
    if not (0 <= r < m and 0 <= c < n) or board[r][c] != word[i]:
        return False
    if i == len(word) - 1:
        return True
    board[r][c] = "#"
    found = any(dfs(r + dr, c + dc, i + 1) for dr, dc in DIRS)
    board[r][c] = word[i]
    return found
```

## Common Variations
- **Reuse allowed:** recurse with `i`, not `i + 1` (0039).
- **Duplicates in input:** sort + skip `i > start && a[i] == a[i-1]` (0040, 0090); for permutations skip `a[i] == a[i-1] && !used[i-1]`.
- **Fixed size k:** stop at `len == k`, loop only while enough elements remain (0077).
- **Partition a string:** choose the next cut end, recurse only on valid pieces (0131).
- **Constraint sets:** O(1) checks with column / `r-c` / `r+c` sets, or bitmasks (0051, 0052).
- **Prune with sorting:** `break` once a sorted candidate overshoots the target (0039, 0040).

## ⚠️ Pitfalls
- **Saving a reference instead of a copy:** Python `path[:]`, Go `slices.Clone(path)`. C++ `push_back(path)` copies already.
- **Forgetting to undo** (pop, unmark, reset the cell) after the recursive call.
- **`i > 0` instead of `i > start`** in the duplicate skip removes valid answers like [1,1,6].
- **Wrong loop start:** combinations loop from `start`, permutations from 0.
- **Go slice aliasing:** appending to a shared slice and saving it without cloning corrupts earlier results.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0017 | [Letter Combinations of a Phone Number](0017-letter-combinations-of-a-phone-number/) | Medium | Backtrack over digit map | ✅ |
| 0039 | [Combination Sum](0039-combination-sum/) | Medium | Backtrack with reuse | ✅ |
| 0040 | [Combination Sum II](0040-combination-sum-ii/) | Medium | Sort + skip duplicates, no reuse | ✅ |
| 0046 | [Permutations](0046-permutations/) | Medium | Backtrack with used[] | ✅ |
| 0077 | [Combinations](0077-combinations/) | Medium | Backtrack choose k | ✅ |
| 0078 | [Subsets](0078-subsets/) | Medium | Include/exclude | ✅ |
| 0079 | [Word Search](0079-word-search/) | Medium | Grid DFS backtracking | ✅ |
| 0090 | [Subsets II](0090-subsets-ii/) | Medium | Sort + skip duplicates | ✅ |
| 0131 | [Palindrome Partitioning](0131-palindrome-partitioning/) | Medium | Backtrack on cut points | ✅ |
| 0051 | [N-Queens](0051-n-queens/) | Hard | Backtrack with col/diag sets | ✅ |
| 0052 | [N-Queens II](0052-n-queens-ii/) | Hard | Backtrack with col/diag sets (count) | ✅ |
