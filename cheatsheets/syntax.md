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
| Consecutive pairs | `for (i = 1; i < n; i++)` use `a[i-1], a[i]` | `for x, y in zip(a, a[1:]):` | `for i := 1; i < len(a); i++` |
| Any / all match | `any_of(a.begin(), a.end(), pred)` / `all_of` | `any(p(x) for x in a)` / `all(...)` | `slices.ContainsFunc(a, pred)` / loop |
| Transpose / rotate a matrix | `swap(m[r][c], m[c][r])` for `c > r`, then `reverse` each row | `m[:] = [list(r) for r in zip(*m[::-1])]` (clockwise) | swap loop, then `slices.Reverse(row)` |
| 8 neighbours | nested `dr, dc` in `-1..1`, skip `(0, 0)` | `[(dr, dc) for dr in (-1,0,1) for dc in (-1,0,1) if (dr, dc) != (0, 0)]` | nested loops, skip `0, 0` |

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
| Pointer / identity key | `unordered_map<Node*, Node*>` | objects hash by identity; or `id(obj)` | `map[*Node]*Node` |
| Point / pair key | `map<pair<int,int>, int>` (no hash needed) or key `x * K + y` | `Counter[(x, y)]` (reads don't insert) | `map[[2]int]int` |
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
| Multiset: remove ONE copy | `ms.erase(ms.find(x));` (`erase(x)` removes all) | `cnt[x] -= 1` on a `Counter` | `cnt[x]--` on a map |
| Ordered counts, iterate ascending | `map<int,int> cnt;` + `for (auto& [k, c] : cnt)` | `for k in sorted(cnt):` | sort the keys, then loop |

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
| Min-heap of tuples | `priority_queue<T, vector<T>, greater<T>>` with `T = tuple<...>` | push tuples; compared element-wise | struct + `Less` using `cmp.Or(cmp.Compare(...), ...)` |
| Min-heap of fixed arrays | `priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;` | push `(t, r, c)` tuples | struct `{t, r, c int}` + `Less` on `t` |
| Two heaps (median) | `priority_queue<int>` + `greater<int>` version | `low` stores negatives, `high` plain | one min-heap type, negate values for the max side |
| Pop min and push in one step | `pq.pop(); pq.push(x);` | `heapq.heapreplace(h, x)` | `(*h)[0] = x; heap.Fix(h, 0)` |
| Heap of pointers (min by field) | `auto cmp = [](Node* a, Node* b){ return a->val > b->val; };` | `(node.val, i, node)`: unique `i` so nodes are never compared | `type nodeHeap []*Node` with `Less: h[i].Val < h[j].Val` |

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
| Stack of pairs | `vector<pair<int,int>> st;` `st.back().second` | `st.append((v, m))`; `st[-1][1]` | `type e struct{ v, m int }`; `st[len(st)-1].m` |
| Second from top | `st[st.size() - 2]` | `st[-2]` | `st[len(st)-2]` |
| Pop and read | `int x = st.back(); st.pop_back();` | `x = st.pop()` | `x := st[len(st)-1]; st = st[:len(st)-1]` |

## Queue / Deque

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Create | `queue<int> q;` / `deque<int> dq;` | `q = deque()` (`from collections import deque`) | `q := []int{}` |
| Push back | `q.push(x);` / `dq.push_back(x);` | `q.append(x)` | `q = append(q, x)` |
| Pop front | `q.front(); q.pop();` / `dq.pop_front();` | `q.popleft()` | `x := q[0]; q = q[1:]` |
| Push front | `dq.push_front(x);` | `q.appendleft(x)` | `q = append([]int{x}, q...)` (O(n)) |
| Pop back | `dq.pop_back();` | `q.pop()` | `q = q[:len(q)-1]` |
| BFS level size | `int sz = q.size();` | `for _ in range(len(q)):` | `for sz := len(q); sz > 0; sz-- {` |

## Linked List

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Node type | `struct ListNode { int val; ListNode* next; };` | `class ListNode: val, next` | `type ListNode struct { Val int; Next *ListNode }` |
| New node | `new ListNode(x)` | `ListNode(x)` | `&ListNode{Val: x}` |
| Dummy head | `ListNode dummy; ListNode* tail = &dummy;` | `dummy = tail = ListNode()` | `dummy := &ListNode{}; tail := dummy` |
| Append + advance | `tail = tail->next = p;` | `tail.next = p; tail = p` | `tail.Next = p; tail = p` |
| Null check | `if (!p)` / `while (p)` | `if not p:` / `while p:` | `if p == nil` / `for p != nil` |
| Walk | `for (auto p = head; p; p = p->next)` | `while p: ...; p = p.next` | `for p := head; p != nil; p = p.Next {` |
| Reverse step (one line) | n/a (use a temp) | `c.next, prev, c = prev, c, c.next` | `c.Next, prev, c = prev, c, c.Next` |
| Identity compare | `a == b` (pointers) | `a is b` | `a == b` (pointers) |
| Node as map key | `unordered_map<ListNode*, ListNode*>` | `dict[ListNode, ListNode]` / `id(node)` | `map[*ListNode]*ListNode` |
| Free a removed node | `delete p;` | automatic (GC) | automatic (GC) |
| Built-in DLL | `list<T>` + `splice` | `collections.OrderedDict` (`move_to_end`) | `container/list` (`MoveToFront`) |

## Binary Tree

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Node type | `struct TreeNode { int val; TreeNode *left, *right; };` | `class TreeNode: val, left, right` | `type TreeNode struct { Val int; Left, Right *TreeNode }` |
| Leaf test | `!n->left && !n->right` | `not n.left and not n.right` | `n.Left == nil && n.Right == nil` |
| Shared answer in DFS | `int& best` parameter | `nonlocal best` in a nested def | closure captures `best` |
| Recursive helper | free function / member | nested `def dfs(n):` | `var dfs func(*TreeNode) int; dfs = func(...)` |
| BFS level snapshot | `for (int sz = q.size(); sz > 0; sz--)` | `for _ in range(len(q)):` | `for sz := len(q); sz > 0; sz-- {` |
| Pair queue item | `queue<pair<TreeNode*, int>>` | `deque([(node, x)])` | local `type item struct{ n *TreeNode; x int }` |
| Both children | `for (auto c : {n->left, n->right})` | `for c in (n.left, n.right):` | `for _, c := range []*TreeNode{n.Left, n.Right}` |
| Type alias | `using TreeNode = Node;` | `TreeNode = Node` | `type TreeNode = Node` |
| "No bound yet" | `LLONG_MIN` / `LLONG_MAX` | `float("-inf")` / `float("inf")` | nil pointer bound (`*TreeNode`) |

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
| First index where pred is true | `partition_point(b, e, notPred)` or hand-written | `bisect_left(range(n), True, key=pred)` (3.10+) | `sort.Search(n, pred)` |
| Both bounds at once | `auto [lo, hi] = equal_range(b, e, x);` | `bisect_left`, `bisect_right` | `sort.SearchInts(a, x)`, `sort.SearchInts(a, x+1)` |
| Found + index | `binary_search(b, e, x)` (bool only) | `i < len(a) and a[i] == x` | `i, ok := slices.BinarySearch(a, x)` |
| Merge two sorted | `merge(a.., b.., back_inserter(out))` | `list(heapq.merge(a, b))` | manual two-pointer loop |
| Sort slice of slices | `sort(v.begin(), v.end());` | `sorted(v)` | `slices.SortFunc(v, func(x, y []int) int { return slices.Compare(x, y) })` |
| Count matching | `count_if(a.begin(), a.end(), pred)` | `sum(pred(x) for x in a)` | loop |
| Sort indices by another array (offline queries) | `iota(idx.begin(), idx.end(), 0); sort(..., [&](int i, int j){ return q[i] < q[j]; });` | `sorted(range(n), key=q.__getitem__)` or sort `(q, i)` pairs | `slices.SortFunc(idx, func(i, j int) int { return cmp.Compare(q[i], q[j]) })` |
| Compare without overflow | `a[1] < b[1]` (never `a[1] - b[1] < 0`) | not an issue | `cmp.Compare(a[1], b[1])` |

C++ comparators must be strict (`<`, never `<=`) or sort can crash.

## Strings

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Char at i | `s[i]` (`char`) | `s[i]` (str) | `s[i]` (byte) |
| Char -> index | `c - 'a'` | `ord(c) - ord('a')` | `int(s[i] - 'a')` |
| Mutable build | `string t; t += c;` | `parts.append(c)` then `"".join(parts)` | `var sb strings.Builder; sb.WriteByte(c); sb.String()` |
| Substring | `s.substr(start, len)` | `s[l:r]` | `s[l:r]` |
| Split | `stringstream ss(s); while (ss >> w)` | `s.split()` | `strings.Fields(s)` |
| Split on a char (keep empties) | `while (getline(ss, part, '/'))` | `s.split("/")` | `strings.Split(s, "/")` |
| Int <-> string | `stoi(s)`, `to_string(x)` | `int(s)`, `str(x)` | `strconv.Atoi(s)`, `strconv.Itoa(x)` |
| Is digit / alnum | `isdigit(c)`, `isalnum(c)` | `c.isdigit()`, `c.isalnum()` | `unicode.IsDigit(r)`, `unicode.IsLetter(r)` |
| Sort chars | `sort(s.begin(), s.end());` | `"".join(sorted(s))` | `b := []byte(s); slices.Sort(b); string(b)` |
| Find (from pos) | `s.find(t, pos)` (`string::npos` if absent) | `s.find(t, pos)` (-1) / `s.index` (raises) | `strings.Index(s[pos:], t)` (+pos; -1 if absent) |
| Starts with | `s.compare(0, p.size(), p) == 0` | `s.startswith(p)` | `strings.HasPrefix(s, p)` |
| Match word at position i | `s.compare(i, w.size(), w) == 0` | `s.startswith(w, i)` | `strings.HasPrefix(s[i:], w)` |
| Join | loop with `" "` separator | `" ".join(words)` | `strings.Join(words, " ")` |
| Repeat / pad | `string(k, ' ')` | `" " * k`, `s.ljust(w)` | `strings.Repeat(" ", k)` |
| Lower / upper | `tolower(c)` | `c.lower()` | `unicode.ToLower(r)` / `strings.ToLower(s)` |
| Reverse | `reverse(s.begin(), s.end());` | `s[::-1]` | `b := []byte(s); slices.Reverse(b)` |
| Char safety | cast `(unsigned char)c` before `isalnum` / array index | n/a | `s[i]` is a byte; `range s` yields runes |
| Print quoted | `"\"" << s << "\""` | `f'"{s}"'` / `repr(s)` | `fmt.Printf("%q", s)` |
| Bool to 0/1 | `int(b)` or implicit | `int(b)` | helper `b2i(b)` (no conversion) |
| Print bool as word | `cout << boolalpha << b` | `str(b).lower()` (prints `True`) | `fmt.Println(b)` / `%t` |
| Fixed decimals | `printf("%.5f", x)` | `f"{x:.5f}"` | `fmt.Printf("%.5f", x)` |

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
| Overflow pre-check for r*10 + d | `r > INT_MAX / 10 \|\| (r == INT_MAX / 10 && d > 7)` | not needed (check range at the end) | same as C++ with `math.MaxInt32` |
| Min / max | `min(a, b)`, `max({a, b, c})` | `min(a, b, c)` | `min(a, b, c)` (built-in, Go 1.21+) |
| Quotient + remainder | `a / b`, `a % b` | `q, r = divmod(a, b)` | `a / b`, `a % b` |
| Ceil division (positive) | `(a + b - 1) / b` (widen first) | `(a + b - 1) // b` or `-(-a // b)` | `(a + b - 1) / b` |
| Truncating division | `a / b` | `int(a / b)` (`//` floors!) | `a / b` |
| Float division of ints | `double(a) / b` | `a / b` | `float64(a) / float64(b)` |
| Counting down safely | use `int i`, not `size_t` (wraps below 0) | n/a | `len()` is a signed `int` |
| "Not found" sentinel | `INT_MAX`, convert to 0/-1 at the end | `math.inf` (float!) → `int()` | `math.MaxInt` |
| Counting DP whose intermediates overflow | `unsigned long long` (wraps, defined) when the final answer is guaranteed small | not needed | `uint64` (wraps) |
| Binomial C(n, k) | loop `r = r * (n - k + i) / i` in `long long` | `math.comb(n, k)` | same loop with `int` |
| GCD | `gcd(a, b)` (`<numeric>`, non-negative) | `math.gcd(a, b)` (non-negative) | write Euclid: `for b != 0 { a, b = b, a%b }` |
| Modular / fast power | squaring loop with `% MOD` in `long long` | `pow(b, e, MOD)` | squaring loop |
| Negate a possibly-INT_MIN int | `long long N = n; N = -N;` | not needed | `int64(n)` first |

## Recursion / Loops

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Recursive helper with shared state | pass by reference: `void dfs(..., vector<string>& res)` | nested `def` + `nonlocal x` to rebind | `var dfs func(int); dfs = func(i int) { ... }` |
| Do-while | `do { ... } while (cond);` | `while True: ...; if not cond: break` | `for { ...; if !cond { break } }` |
| Loop with "no break happened" branch | bool flag | `for ...: ... break` / `else:` | bool flag or labeled `continue` |
| Infinite loop | `while (true)` / `for (;;)` | `while True:` | `for { }` |
| Recursion depth | ~10⁴-10⁵ frames (8 MB default stack) | default limit ~1000 (`sys.setrecursionlimit`) | stacks grow dynamically |
| Recursive lambda | `function<void(int)> f = [&](int i) { ... f(i + 1); };` | nested `def` | `var f func(int); f = func(i int) { ... }` |
| Snapshot a backtracking path | `res.push_back(path)` (copies) | `res.append(path[:])` | `res = append(res, slices.Clone(path))` |
| 4-direction neighbours | `const int DR[4] = {1,-1,0,0}, DC[4] = {0,0,1,-1};` | `DIRS = ((1,0),(-1,0),(0,1),(0,-1))` | `var dirs = [4][2]int{{1,0},{-1,0},{0,1},{0,-1}}` |
| In-bounds check | `r >= 0 && c >= 0 && r < m && c < n` | `0 <= r < m and 0 <= c < n` | `r >= 0 && c >= 0 && r < m && c < n` |
| Iterative DFS (no recursion limit) | `vector<int> st{s}; while (!st.empty()) { int u = st.back(); st.pop_back(); ... }` | `st = [s]` + `while st: u = st.pop()` | `st := []int{s}; for len(st) > 0 { u := st[len(st)-1]; st = st[:len(st)-1] }` |

## DP / Memoization

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Memoize a function | `vector<int> memo(n, -1);` + `if (memo[i] != -1) return memo[i];` | `@cache` (from `functools`) on a nested `def` | `memo := make([]int, n)` + sentinel check |
| Store and return | `return memo[i] = res;` | (automatic with `@cache`) | `memo[i] = res; return res` |
| dp with base dp[0] | `vector<int> dp(n + 1, INF); dp[0] = 0;` | `dp = [0] + [INF] * n` | `dp := make([]int, n+1)` + fill loop |
| Rolling two values | `int c = f(a, b); a = b; b = c;` | `a, b = b, f(a, b)` | `a, b = b, f(a, b)` |
| Safe "infinity" for min-count | `amount + 1` (not `INT_MAX`: `+1` wraps) | `float("inf")` or `amount + 1` | `amount + 1` |
| Min over possibly empty set | init `best = INF`, loop | `min(gen, default=INF)` | init `best := math.MaxInt`, loop |
| Subset-sum bitset | `bitset<10001> b(1); b \|= b << x; b[t]` | `b = 1; b \|= b << x; b >> t & 1` | `math/big`: `b.Or(b, new(big.Int).Lsh(b, x))` |
| 0/1 knapsack sweep | `for (int s = S; s >= x; s--)` | `for s in range(S, x - 1, -1):` | `for s := S; s >= x; s-- {` |
| Countdown sentinel memo (0 is valid) | fill with -1 or -2 | `@cache` avoids sentinels | fill with -1 |
| Cache slot by reference | `int& m = memo[i][j]; if (m != -1) return m; ... return m = res;` | n/a (`@cache`) | `p := &memo[i][j]` |
| Small extra state dimension | `vector<array<int, 2>> memo(n, {-1, -1});` | `@cache def f(i, holding)` | `memo := make([][2]int, n)` |
| Two rolling rows | `swap(prev, cur);` (O(1)) | build a fresh `cur` each row, then `prev = cur` | `prev, cur = cur, prev` |
| Negative state index | `memo[i][s + offset]` | `@cache` takes negative keys | `memo[i][s+offset]` |

## Graph / Union-Find

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Adjacency list | `vector<vector<int>> adj(n);` `adj[u].push_back(v);` | `adj = [[] for _ in range(n)]` | `adj := make([][]int, n)`; `adj[u] = append(adj[u], v)` |
| String-keyed graph | `unordered_map<string, vector<pair<string,double>>> adj;` | `defaultdict(list)` | `map[string][]edge{}` |
| DSU init | `vector<int> p(n); iota(p.begin(), p.end(), 0);` | `parent = list(range(n))` | loop `parent[i] = i` |
| Find with compression | `return p[x] == x ? x : p[x] = find(p[x]);` | `while p[x] != x: p[x] = p[p[x]]; x = p[x]` | `if p[x] != x { p[x] = find(p[x]) }; return p[x]` |
| Flatten a cell | `r * n + c` | `r * n + c` / `divmod(id, n)` | `r*n + c` |
| Multi-source BFS seed | push every source before the loop | `deque((r, c) for ... if g[r][c] == 0)` | append every source to `q` first |
| Pointer-identity map (clone) | `unordered_map<Node*, Node*>` | `dict[Node, Node]` (identity hash) | `map[*Node]*Node` |

## Bits

| Operation | C++ | Python | Go |
|-----------|-----|--------|----|
| Test bit j | `mask >> j & 1` | `mask >> j & 1` | `mask>>j&1 == 1` |
| Lowest set bit | `x & -x` | `x & -x` | `x & -x` |
| Low n bits mask | `(1 << n) - 1` | `(1 << n) - 1` | `1<<n - 1` |
| Clear bits of y in x | `x & ~y` | `x & ~y` (mask result: `~` is negative) | `x &^ y` |
| Clear lowest set bit | `x & (x - 1)` | `x & (x - 1)` | `x & (x - 1)` |
| Count set bits | `__builtin_popcount(x)` / `bitset<32>(x).count()` | `x.bit_count()` (3.10+) | `bits.OnesCount(uint(x))` |
| Unsigned 32-bit work | `uint32_t x = n;` (logical `>>`, defined wraparound) | `x & 0xFFFFFFFF` after every shift/add | `uint32(n)` |
| 32-bit pattern back to signed | `(int)x` | `x - (1 << 32) if x >> 31 else x` | `int32(x)` |
| Set bit k safely | `x \| (1u << k)` (`1 << 31` on int overflows) | `x \| (1 << k)` | `x \| (1 << k)` |
| Parse / print binary | `stoull(s, nullptr, 2)` (≤ 64 bits), `bitset<32>(x).to_string()` | `int(s, 2)`, `bin(x)[2:]` | `strconv.ParseInt(s, 2, 64)`, `strconv.FormatInt(x, 2)` |
