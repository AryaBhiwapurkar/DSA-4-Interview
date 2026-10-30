# 04. Stack

## Core Idea
A stack is LIFO: the last thing pushed is the first thing popped. Reach for it whenever the next decision depends on the **most recent unfinished thing**: the latest open bracket, the latest operand, the latest directory, the outer context before a parenthesis. A special case, the **monotonic stack**, keeps elements in increasing or decreasing order by popping everything the new element "beats"; each pop answers a "next greater/smaller" question for the popped element. Every element is pushed and popped at most once, so a full scan is O(n).

## When to Use
- Matching / nesting: brackets, tags, parentheses with context (0020, 0224).
- Evaluate expressions: postfix directly, infix with a stack of saved context (0150, 0224).
- "Undo the most recent": `..` in paths, backspace in strings (0071).
- "Next greater / next smaller / previous smaller" for every element (0739, 0084).
- Keep an aggregate (like the min) that must survive pops (0155).
- Sort, then merge items into groups from one end (0853).

## Templates

### Matching with a stack
```cpp
vector<char> st;
for (char c : s) {
    if (isOpen(c)) st.push_back(c);
    else if (st.empty() || st.back() != matchOf(c)) return false;
    else st.pop_back();
}
return st.empty();
```
```python
st = []
for c in s:
    if c in OPEN:
        st.append(c)
    elif not st or st.pop() != MATCH[c]:
        return False
return not st
```
```go
st := []byte{}
for i := 0; i < len(s); i++ {
	c := s[i]
	if isOpen(c) {
		st = append(st, c)
	} else if len(st) == 0 || st[len(st)-1] != matchOf(c) {
		return false
	} else {
		st = st[:len(st)-1]
	}
}
return len(st) == 0
```

### Monotonic stack (next greater element)
```cpp
vector<int> ans(n, -1), st;                  // st holds indices, values decreasing
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[i] > a[st.back()]) {
        ans[st.back()] = i;                  // a[i] is the next greater of the popped
        st.pop_back();
    }
    st.push_back(i);
}
```
```python
ans, st = [-1] * n, []
for i, x in enumerate(a):
    while st and x > a[st[-1]]:
        ans[st.pop()] = i
    st.append(i)
```
```go
ans, st := make([]int, n), []int{}
for i := range ans {
	ans[i] = -1
}
for i, x := range a {
	for len(st) > 0 && x > a[st[len(st)-1]] {
		ans[st[len(st)-1]] = i
		st = st[:len(st)-1]
	}
	st = append(st, i)
}
```

### Save context on "(" and restore on ")"
```cpp
if (c == '(') { st.push_back({res, sign}); res = 0; sign = 1; }
else if (c == ')') { auto [r, sg] = st.back(); st.pop_back(); res = r + sg * res; }
```
```python
if c == "(":
    st.append((res, sign)); res, sign = 0, 1
elif c == ")":
    r, sg = st.pop(); res = r + sg * res
```
```go
if c == '(' {
	st = append(st, frame{res, sign})
	res, sign = 0, 1
} else if c == ')' {
	top := st[len(st)-1]
	st = st[:len(st)-1]
	res = top.res + top.sign*res
}
```

## Common Variations
- **Flip the comparison:** `>` gives next greater with a decreasing stack; `<` gives next smaller with an increasing stack (0739, 0084).
- **Answer at pop time vs push time:** at pop time you learn the *next* boundary; the new top after a pop is the *previous* boundary (0084).
- **Sentinel at the end:** push a 0 (or -∞) to flush every remaining element without a cleanup loop (0084).
- **Augment each entry:** store (value, min so far) so aggregates survive pops (0155).
- **Stack of frames:** save (result, sign) or (string, count) per nesting level (0224).
- **Only the top is used:** the stack collapses to a single variable (0853).
- **Backtracking with counts** is a stack in disguise: the call stack holds the open brackets (0022).

## ⚠️ Pitfalls
- **Reading the top of an empty stack:** always check empty first (`st.back()` on empty is UB in C++, a panic in Go).
- **Storing values when you need distances:** push indices and read values through them.
- **Strict vs non-strict comparison:** decide how equal elements behave (0739 needs strictly warmer).
- **Forgetting leftovers:** elements still on the stack at the end need a default answer (0, -1) or a final flush.
- **C++ `std::stack::pop()` returns void:** read `top()` first. `vector` as a stack is usually simpler.
- **Python `list.pop(0)`** is O(n): that's a queue, use `collections.deque`.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0020 | [Valid Parentheses](0020-valid-parentheses/) | Easy | Stack matching | ✅ |
| 0022 | [Generate Parentheses](0022-generate-parentheses/) | Medium | Backtracking on open/close counts | ✅ |
| 0071 | [Simplify Path](0071-simplify-path/) | Medium | Stack of directory names | ✅ |
| 0150 | [Evaluate Reverse Polish Notation](0150-evaluate-reverse-polish-notation/) | Medium | Operand stack | ✅ |
| 0155 | [Min Stack](0155-min-stack/) | Medium | Stack of (val, min) | ✅ |
| 0739 | [Daily Temperatures](0739-daily-temperatures/) | Medium | Monotonic decreasing stack | ✅ |
| 0853 | [Car Fleet](0853-car-fleet/) | Medium | Sort by position + stack of arrival times | ✅ |
| 0084 | [Largest Rectangle in Histogram](0084-largest-rectangle-in-histogram/) | Hard | Monotonic increasing stack | ✅ |
| 0224 | [Basic Calculator](0224-basic-calculator/) | Hard | Stack for sign/paren context | ✅ |
