# Syntax: C++ / Python / Go

C++17 (`#include <bits/stdc++.h>`), Python 3.10+, Go (stdlib only).

## Array / List / Slice

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Create n zeros | `vector<int> a(n, 0);` | `a = [0] * n` | `a := make([]int, n)` |
| 2-D grid | `vector<vector<int>> g(r, vector<int>(c));` | `g = [[0] * c for _ in range(r)]` | `g := make([][]int, r)` then `g[i] = make([]int, c)` per row |
| Append | `a.push_back(x);` | `a.append(x)` | `a = append(a, x)` |
| Pop last | `a.pop_back();` | `a.pop()` | `a = a[:len(a)-1]` |
| Length | `a.size()` (unsigned!) | `len(a)` | `len(a)` |
| Slice / subarray | `vector<int>(a.begin()+l, a.begin()+r)` | `a[l:r]` (copy) | `a[l:r]` (shares memory) |
| Copy | `auto b = a;` | `b = a[:]` | `b := slices.Clone(a)` |
| Reverse | `reverse(a.begin(), a.end());` | `a.reverse()` / `a[::-1]` | `slices.Reverse(a)` |
| Index + value loop | `for (int i = 0; i < (int)a.size(); i++)` | `for i, x in enumerate(a):` | `for i, x := range a {` |
| Fixed-size zeroed array | `array<int, 26> c{};` | `c = [0] * 26` | `var c [26]int` |
| Compare whole arrays | `a == b` (vector/array) | `a == b` | `a == b` (arrays only); `slices.Equal(a, b)` |
| Max of range | `*max_element(a.begin(), a.end())` | `max(a)` | `slices.Max(a)` |
| Prefix sums | `partial_sum(a.begin(), a.end(), p.begin()+1)` | `[0, *accumulate(a)]` | loop: `p[i+1] = p[i] + a[i]` |
| Running max | loop | `list(accumulate(a, max))` | loop |
| Drop adjacent duplicates | `a.erase(unique(a.begin(), a.end()), a.end());` | `list(dict.fromkeys(a))` (all dups) | `a = slices.Compact(a)` |
| Remove value in place | `a.erase(remove(a.begin(), a.end(), v), a.end());` | `a[:] = [x for x in a if x != v]` | `a = slices.DeleteFunc(a, func(x int) bool { return x == v })` |
| Replace contents in place | `a = b;` (by-ref param) | `a[:] = b` (not `a = b`) | `copy(a, b)` |

## Hashmap

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Create | `unordered_map<int,int> m;` | `m: dict[int, int] = {}` | `m := make(map[int]int)` |
| Lookup without inserting | `auto it = m.find(k); if (it != m.end())` | `if k in m:` / `m.get(k)` | `v, ok := m[k]` |
| Count up | `m[k]++;` | `m[k] = m.get(k, 0) + 1` / `Counter(a)` | `m[k]++` |
| Delete | `m.erase(k);` | `del m[k]` / `m.pop(k, None)` | `delete(m, k)` |
| Iterate | `for (auto& [k, v] : m)` | `for k, v in m.items():` | `for k, v := range m {` (random order) |
| Default values | `m[k]` inserts `0` if missing | `defaultdict(list)` | missing key returns zero value |
| Insert only if absent | `m.emplace(k, v)` (keeps old) | `m.setdefault(k, v)` | `if _, ok := m[k]; !ok { m[k] = v }` |
| Composite / array key | build a `string` key | `tuple(counts)` key | `map[[26]int][]string` (arrays are comparable) |
| Most common | sort pairs by count | `Counter(a).most_common(k)` | sort keys by count |
| Clear | `m.clear();` | `m.clear()` | `clear(m)` (Go 1.21+) |

## Set

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Create | `unordered_set<int> s;` | `s: set[int] = set()` | `s := make(map[int]struct{})` |
| Add | `s.insert(x);` | `s.add(x)` | `s[x] = struct{}{}` |
| Contains | `s.count(x)` | `x in s` | `_, ok := s[x]` |
| Remove | `s.erase(x);` | `s.discard(x)` | `delete(s, x)` |
| Insert + "was it new?" | `s.insert(x).second` | `if x not in s: s.add(x)` | `if _, ok := s[x]; !ok { s[x] = struct{}{} }` |
| Build from list | `unordered_set<int> s(a.begin(), a.end());` | `set(a)` | loop over `a` |
| Bool set (small domain) | `bool seen[256] = {};` | `[False] * 256` | `var seen [256]bool` |
| Ordered set | `set<int>` (`lower_bound`) | `sorted()` + `bisect` | sorted slice + `sort.SearchInts` |

## Heap (Priority Queue) with Custom Comparator

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Max-heap | `priority_queue<int> pq;` | push `-x` into a min-heap | `container/heap`, `Less` returns `h[i] > h[j]` |
| Min-heap | `priority_queue<int, vector<int>, greater<int>> pq;` | `heapq` on a list | `container/heap`, `Less` returns `h[i] < h[j]` |
| Custom order | `auto cmp = [](const T& a, const T& b){ return a.d > b.d; };` `priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);` (min by `d`) | push tuples `(key, tiebreak, item)` | custom `Less` on a struct slice |
| Push | `pq.push(x);` | `heapq.heappush(h, x)` | `heap.Push(h, x)` |
| Pop top | `pq.top(); pq.pop();` | `heapq.heappop(h)` | `heap.Pop(h).(int)` |
| Peek | `pq.top()` | `h[0]` | `(*h)[0]` |
| Heapify list | `priority_queue<int> pq(a.begin(), a.end());` | `heapq.heapify(a)` | `heap.Init(h)` |

C++ comparator is "inverted": returning `a > b` gives a **min**-heap.

Go min-heap boilerplate:

```go
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] } // > for max-heap
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *IntHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *IntHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

// h := &IntHeap{3, 1, 2}; heap.Init(h); heap.Push(h, 0); heap.Pop(h).(int)
```

## Stack

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Create | `stack<int> st;` (or `vector<int>`) | `st: list[int] = []` | `st := []int{}` |
| Push | `st.push(x);` | `st.append(x)` | `st = append(st, x)` |
| Top | `st.top()` | `st[-1]` | `st[len(st)-1]` |
| Pop | `st.pop();` (returns void) | `st.pop()` | `st = st[:len(st)-1]` |
| Empty | `st.empty()` | `not st` | `len(st) == 0` |

## Queue / Deque

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Create | `queue<int> q;` / `deque<int> dq;` | `q = deque()` (`from collections import deque`) | `q := []int{}` |
| Push back | `q.push(x);` / `dq.push_back(x);` | `q.append(x)` | `q = append(q, x)` |
| Pop front | `q.front(); q.pop();` / `dq.pop_front();` | `q.popleft()` | `x := q[0]; q = q[1:]` |
| Push front | `dq.push_front(x);` | `q.appendleft(x)` | `q = append([]int{x}, q...)` (O(n)) |
| Pop back | `dq.pop_back();` | `q.pop()` | `q = q[:len(q)-1]` |
| BFS level size | `int sz = q.size();` | `for _ in range(len(q)):` | `for sz := len(q); sz > 0; sz-- {` |

## Sort with Comparator

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Ascending | `sort(a.begin(), a.end());` | `a.sort()` / `sorted(a)` | `slices.Sort(a)` |
| Descending | `sort(a.rbegin(), a.rend());` | `a.sort(reverse=True)` | `slices.Sort(a); slices.Reverse(a)` |
| By key | `sort(a.begin(), a.end(), [](auto& x, auto& y){ return x[0] < y[0]; });` | `a.sort(key=lambda x: x[0])` | `sort.Slice(a, func(i, j int) bool { return a[i][0] < a[j][0] })` |
| Multi-key | compare `tie(x[0], y[1]) < tie(y[0], x[1])` | `key=lambda x: (x[0], -x[1])` | `slices.SortFunc(a, func(x, y T) int { return cmp.Or(cmp.Compare(x.a, y.a), cmp.Compare(y.b, x.b)) })` |
| Stable | `stable_sort(...)` | `sort` is always stable | `sort.SliceStable(...)` / `slices.SortStableFunc` |
| Binary search | `lower_bound(a.begin(), a.end(), x) - a.begin()` | `bisect.bisect_left(a, x)` | `sort.SearchInts(a, x)` |
| First > x (upper bound) | `upper_bound(a.begin(), a.end(), x)` | `bisect.bisect_right(a, x)` | `sort.SearchInts(a, x+1)` (ints) |
| Search a sub-range | `lower_bound(a.begin()+lo, a.end(), x)` | `bisect_left(a, x, lo)` | `lo + sort.SearchInts(a[lo:], x)` |
| Sort slice of slices | `sort(v.begin(), v.end());` | `sorted(v)` | `slices.SortFunc(v, func(x, y []int) int { return slices.Compare(x, y) })` |
| Count matching | `count_if(a.begin(), a.end(), pred)` | `sum(pred(x) for x in a)` | loop |

C++ comparators must be strict (`<`, never `<=`) or sort can crash.

## Strings

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Char at i | `s[i]` (`char`) | `s[i]` (str) | `s[i]` (byte) |
| Char -> index | `c - 'a'` | `ord(c) - ord('a')` | `int(s[i] - 'a')` |
| Mutable build | `string t; t += c;` | `parts.append(c)` then `"".join(parts)` | `var sb strings.Builder; sb.WriteByte(c); sb.String()` |
| Substring | `s.substr(start, len)` | `s[l:r]` | `s[l:r]` |
| Split | `stringstream ss(s); while (ss >> w)` | `s.split()` | `strings.Fields(s)` |
| Int <-> string | `stoi(s)`, `to_string(x)` | `int(s)`, `str(x)` | `strconv.Atoi(s)`, `strconv.Itoa(x)` |
| Is digit / alnum | `isdigit(c)`, `isalnum(c)` | `c.isdigit()`, `c.isalnum()` | `unicode.IsDigit(r)`, `unicode.IsLetter(r)` |
| Sort chars | `sort(s.begin(), s.end());` | `"".join(sorted(s))` | `b := []byte(s); slices.Sort(b); string(b)` |
| Find (from pos) | `s.find(t, pos)` (`string::npos` if absent) | `s.find(t, pos)` (-1) / `s.index` (raises) | `strings.Index(s[pos:], t)` (+pos; -1 if absent) |
| Starts with | `s.compare(0, p.size(), p) == 0` | `s.startswith(p)` | `strings.HasPrefix(s, p)` |
| Join | loop with `" "` separator | `" ".join(words)` | `strings.Join(words, " ")` |
| Repeat / pad | `string(k, ' ')` | `" " * k`, `s.ljust(w)` | `strings.Repeat(" ", k)` |
| Lower / upper | `tolower(c)` | `c.lower()` | `unicode.ToLower(r)` / `strings.ToLower(s)` |
| Reverse | `reverse(s.begin(), s.end());` | `s[::-1]` | `b := []byte(s); slices.Reverse(b)` |
| Char safety | cast `(unsigned char)c` before `isalnum` / array index | n/a | `s[i]` is a byte; `range s` yields runes |
| Print quoted | `"\"" << s << "\""` | `f'"{s}"'` / `repr(s)` | `fmt.Printf("%q", s)` |

Python and Go strings are immutable; C++ `std::string` is mutable.

## Int Limits / Overflow

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Max / min int | `INT_MAX`, `INT_MIN`, `LLONG_MAX` | `float('inf')`, `-float('inf')` | `math.MaxInt`, `math.MinInt` (also `math.MaxInt32`) |
| 64-bit int | `long long` | unbounded `int` | `int` is 64-bit on 64-bit platforms; `int64` to be explicit |
| Safe midpoint | `l + (r - l) / 2` | `(l + r) // 2` | `l + (r-l)/2` |
| Avoid overflow in product/sum | `(long long)a * b` | not needed | `int64(a) * int64(b)` if using `int32` |
| Integer division toward | zero (`-7/2 == -3`) | floor (`-7//2 == -4`) | zero (`-7/2 == -3`) |
| Modulo of negative | `-7 % 3 == -1` | `-7 % 3 == 2` | `-7 % 3 == -1` |
| Min / max | `min(a, b)`, `max({a, b, c})` | `min(a, b, c)` | `min(a, b, c)` (built-in, Go 1.21+) |
| Quotient + remainder | `a / b`, `a % b` | `q, r = divmod(a, b)` | `a / b`, `a % b` |
| Counting down safely | use `int i`, not `size_t` (wraps below 0) | n/a | `len()` is a signed `int` |
| "Not found" sentinel | `INT_MAX`, convert to 0/-1 at the end | `math.inf` (float!) → `int()` | `math.MaxInt` |
