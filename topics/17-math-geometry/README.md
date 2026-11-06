# 17. Math & Geometry

## Core Idea
No single algorithm, just a toolbox of small, exact tricks. **Digits:** pop with `% 10` and `/ 10`, build with `r * 10 + d`, and carry from the right. **Number theory:** gcd for exact ratios, counting prime factors (Legendre), and exponentiation by squaring. **Matrices:** derive the index mapping first, e.g. (r, c) → (c, n−1−r), then find in-place moves, or spare bits and cells, that realise it. **Geometry on integers:** use reduced integer pairs and cross products, never floats. Most bugs here are overflow, rounding, or off-by-one edges, not the idea.

## When to Use
- Integer read as digits (palindrome, reverse, digit sums): pop digits, often only half (0009, 0202).
- Number stored as digits or a string: grade-school carry, right to left (0066, 0043).
- Huge exponent: squaring, O(log n) (0050).
- "How many trailing zeros / factors of p": count multiples of p, p², … (0172).
- Rotate or traverse a matrix: index mapping, transpose + reflect, or shrinking boundaries (0048, 0054).
- In-place matrix update with a simultaneous rule: encode flags in row 0 / col 0 or in spare bits (0073, 0289).
- Points and shapes: hash points or exact slopes, and fix one "anchor" or "diagonal" (2013, 0149).

## Templates

### Digits
```cpp
while (x) { int d = x % 10; x /= 10; /* use d */ }
// overflow-safe push: if (r > INT_MAX / 10 || (r == INT_MAX / 10 && d > 7)) overflow
```
```python
while x:
    x, d = divmod(x, 10)
```

### Fast power
```cpp
long long N = n; if (N < 0) x = 1 / x, N = -N;
double r = 1;
for (; N; N >>= 1, x *= x) if (N & 1) r *= x;
```
```python
r = 1
while n:
    if n & 1: r = r * x % MOD
    x = x * x % MOD; n >>= 1           # or just pow(x, n, MOD)
```

### Matrix transforms
```python
# clockwise:         transpose, then reverse each row
# counter-clockwise: transpose, then reverse the row order
for r in range(n):
    for c in range(r + 1, n):
        m[r][c], m[c][r] = m[c][r], m[r][c]
```

### Spiral / boundaries
```python
t, b, l, r = 0, m - 1, 0, n - 1
while t <= b and l <= r:
    # top row l..r, t++; right col t..b, r--
    # if t <= b: bottom row r..l, b--
    # if l <= r: left col b..t, l++
```

### Exact slope key
```python
g = gcd(dx, dy); dx, dy = dx // g, dy // g
if dx < 0 or (dx == 0 and dy < 0): dx, dy = -dx, -dy
```

## Common Variations
- **Palindrome without strings:** reverse only half, and reject trailing zeros (0009).
- **Implicit sequences that might loop:** cycle detection with a set or Floyd (0202).
- **Modular exponentiation:** the same squaring loop with `% MOD`.
- **Counter-clockwise or 180° rotation:** a different pair of reflections.
- **Infinite Game of Life:** a set of live cells instead of a grid.
- **Rectangles instead of squares:** fix the diagonal and check the other two corners in a set.

## ⚠️ Pitfalls
- **Overflow:** `-INT_MIN`, `r * 10 + d`, intermediate products. Widen to `long long` or pre-check.
- **Floats for slopes or equality:** rounding merges distinct values. Use integer pairs or cross products.
- **Negative `%` and `/`:** C++ truncates towards 0, Python floors. Handle the sign first.
- **In-place matrix updates** that read already-overwritten cells. Encode, or order the passes carefully.
- **Edge shapes:** single row or column, 1×1, n = 0 or 1.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0009 | [Palindrome Number](0009-palindrome-number/) | Easy | Reverse half the number | ✅ |
| 0066 | [Plus One](0066-plus-one/) | Easy | Carry from the end | ✅ |
| 0202 | [Happy Number](0202-happy-number/) | Easy | Cycle detection (fast/slow) | ✅ |
| 0043 | [Multiply Strings](0043-multiply-strings/) | Medium | Grade-school multiplication | ✅ |
| 0048 | [Rotate Image](0048-rotate-image/) | Medium | Transpose + reverse rows | ✅ |
| 0050 | [Pow(x, n)](0050-powx-n/) | Medium | Fast exponentiation | ✅ |
| 0054 | [Spiral Matrix](0054-spiral-matrix/) | Medium | Shrinking boundaries | ✅ |
| 0073 | [Set Matrix Zeroes](0073-set-matrix-zeroes/) | Medium | First row/col as markers | ✅ |
| 0172 | [Factorial Trailing Zeroes](0172-factorial-trailing-zeroes/) | Medium | Count factors of 5 | ✅ |
| 0289 | [Game of Life](0289-game-of-life/) | Medium | In-place state encoding | ✅ |
| 2013 | [Detect Squares](2013-detect-squares/) | Medium | Point counts + diagonal | ✅ |
| 0149 | [Max Points on a Line](0149-max-points-on-a-line/) | Hard | Slope hashmap (gcd) | ✅ |
