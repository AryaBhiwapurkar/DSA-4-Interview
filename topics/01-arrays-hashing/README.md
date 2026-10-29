# 01. Arrays & Hashing

## Core Idea
Trade memory for time. A hashmap/set answers "have I seen X?" or "how many X?" in O(1) average, turning nested-loop O(n²) scans into one O(n) pass. For fixed small alphabets (a–z, ASCII) a plain count array does the same job with O(1) space. Prefix/suffix accumulations precompute "everything to the left/right of i" so each index is answered in O(1).

## When to Use
- "Find a pair / complement summing to target" in an **unsorted** array.
- "Contains duplicate", "first unique", "is it seen before".
- "Anagram", "same letters", "permutation of", "group by" → frequency count or canonical key.
- "Most frequent / top k" → count, then bucket or heap.
- "Product/sum of everything except i", "range sum" → prefix/suffix arrays.
- O(n) required on unsorted data (sorting would be O(n log n)).
- Bijection between two sequences ("isomorphic", "pattern") → two maps.

## Templates

### Frequency count
```cpp
array<int, 26> cnt{};                       // fixed lowercase alphabet
for (char c : s) cnt[c - 'a']++;
unordered_map<int, int> freq;               // arbitrary values
for (int x : nums) freq[x]++;
```
```python
cnt = [0] * 26
for c in s:
    cnt[ord(c) - ord("a")] += 1
freq = Counter(nums)                        # from collections import Counter
```
```go
var cnt [26]int
for i := 0; i < len(s); i++ {
	cnt[s[i]-'a']++
}
freq := make(map[int]int)
for _, x := range nums {
	freq[x]++
}
```

### Seen-before lookup (check, then insert)
```cpp
unordered_map<int, int> seen;               // value -> index
for (int i = 0; i < (int)nums.size(); i++) {
    auto it = seen.find(target - nums[i]);  // find, never seen[...] for lookups
    if (it != seen.end()) return {it->second, i};
    seen[nums[i]] = i;
}
```
```python
seen: dict[int, int] = {}
for i, x in enumerate(nums):
    if target - x in seen:
        return [seen[target - x], i]
    seen[x] = i
```
```go
seen := make(map[int]int)
for i, x := range nums {
	if j, ok := seen[target-x]; ok { // comma-ok: 0 is a valid index
		return []int{j, i}
	}
	seen[x] = i
}
```

### Group by canonical key
```cpp
unordered_map<string, vector<string>> groups;
for (auto& s : strs) { string k = s; sort(k.begin(), k.end()); groups[k].push_back(s); }
```
```python
groups: defaultdict[str, list[str]] = defaultdict(list)
for s in strs:
    groups["".join(sorted(s))].append(s)
```
```go
groups := make(map[[26]int][]string) // arrays are valid map keys
for _, s := range strs {
	var k [26]int
	for i := 0; i < len(s); i++ {
		k[s[i]-'a']++
	}
	groups[k] = append(groups[k], s)
}
```

### Prefix / suffix pass
```cpp
vector<int> ans(n, 1);
for (int i = 1; i < n; i++) ans[i] = ans[i - 1] * nums[i - 1];   // left of i
for (int i = n - 1, suf = 1; i >= 0; i--) { ans[i] *= suf; suf *= nums[i]; }
```
```python
ans = [1] * n
for i in range(1, n):
    ans[i] = ans[i - 1] * nums[i - 1]
suf = 1
for i in range(n - 1, -1, -1):
    ans[i] *= suf
    suf *= nums[i]
```
```go
ans := make([]int, n)
ans[0] = 1
for i := 1; i < n; i++ {
	ans[i] = ans[i-1] * nums[i-1]
}
for i, suf := n-1, 1; i >= 0; i-- {
	ans[i] *= suf
	suf *= nums[i]
}
```

## Common Variations
- **Count array vs hashmap:** fixed alphabet → array (O(1) space); arbitrary values → map.
- **Bucket by frequency:** counts are ≤ n, so `buckets[count]` gives an O(n) "sort by frequency" (0347, 0274).
- **Start-of-run trick:** with a set, only start counting from x when x-1 is absent (0128).
- **Two maps for a bijection:** forward and reverse mapping (0205, 0290).
- **Swap-with-last delete:** map + array for O(1) remove and random access (0380).
- **Voting / cancellation:** O(1)-space majority (0169).
- **String building:** split/join or a builder; in-place reversal tricks (0151, 0189).

## ⚠️ Pitfalls
- **C++ `map[key]` inserts** a default on read; use `find`/`count` for lookups.
- **Go map zero value:** a missing key returns 0/""/false, which may be valid data; use comma-ok.
- **Python unhashable keys:** lists can't be dict keys; use tuples or strings.
- **Insert-before-check** lets an element match itself (Two Sum style).
- **Hashing is average O(1)**; mention worst case if asked, and prefer arrays for small fixed domains.
- **Iteration order:** C++ `unordered_map` and Go maps are unordered (Go is randomized); sort before printing or comparing.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0001 | [Two Sum](0001-two-sum/) | Easy | Hashmap complement lookup | ✅ |
| 0013 | [Roman to Integer](0013-roman-to-integer/) | Easy | Hashmap, subtractive rule | ✅ |
| 0014 | [Longest Common Prefix](0014-longest-common-prefix/) | Easy | Vertical scan | ✅ |
| 0028 | [Find the Index of the First Occurrence in a String](0028-find-the-index-of-the-first-occurrence-in-a-string/) | Easy | String matching (KMP optional) | ✅ |
| 0058 | [Length of Last Word](0058-length-of-last-word/) | Easy | Reverse scan | ✅ |
| 0169 | [Majority Element](0169-majority-element/) | Easy | Boyer-Moore voting | ✅ |
| 0205 | [Isomorphic Strings](0205-isomorphic-strings/) | Easy | Two-way mapping | ✅ |
| 0217 | [Contains Duplicate](0217-contains-duplicate/) | Easy | Hash set | ✅ |
| 0242 | [Valid Anagram](0242-valid-anagram/) | Easy | Frequency count | ✅ |
| 0290 | [Word Pattern](0290-word-pattern/) | Easy | Two-way mapping | ✅ |
| 0383 | [Ransom Note](0383-ransom-note/) | Easy | Frequency count | ✅ |
| 0006 | [Zigzag Conversion](0006-zigzag-conversion/) | Medium | Row simulation | ✅ |
| 0012 | [Integer to Roman](0012-integer-to-roman/) | Medium | Greedy over value table | ✅ |
| 0036 | [Valid Sudoku](0036-valid-sudoku/) | Medium | Hash sets per row/col/box | ✅ |
| 0049 | [Group Anagrams](0049-group-anagrams/) | Medium | Hashmap with canonical key | ✅ |
| 0128 | [Longest Consecutive Sequence](0128-longest-consecutive-sequence/) | Medium | Hash set, start-of-run | ✅ |
| 0151 | [Reverse Words in a String](0151-reverse-words-in-a-string/) | Medium | Split + reverse | ✅ |
| 0189 | [Rotate Array](0189-rotate-array/) | Medium | Reverse in place | ✅ |
| 0238 | [Product of Array Except Self](0238-product-of-array-except-self/) | Medium | Prefix & suffix products | ✅ |
| 0271 | [Encode and Decode Strings](0271-encode-and-decode-strings/) | Medium | Length-prefix encoding | ✅ |
| 0274 | [H-Index](0274-h-index/) | Medium | Sort / counting | ✅ |
| 0347 | [Top K Frequent Elements](0347-top-k-frequent-elements/) | Medium | Bucket sort / heap | ✅ |
| 0380 | [Insert Delete GetRandom O(1)](0380-insert-delete-getrandom-o1/) | Medium | Hashmap + array, swap-delete | ✅ |
| 0068 | [Text Justification](0068-text-justification/) | Hard | Greedy line packing | ✅ |
