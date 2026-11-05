# 18. Bit Manipulation

## Core Idea
Treat an integer as 32 independent switches. A handful of identities do most of the work: `x ^ x = 0` and `x ^ 0 = x` (pairs cancel), `x & (x - 1)` clears the lowest set bit, `x & -x` isolates it, and `(x >> k) & 1` reads bit k. When a whole-number trick doesn't fit (three copies, a range of numbers), work **one bit position at a time**. The language details are where people slip: signed shifts, overflow of `1 << 31`, and Python's unbounded integers with infinite sign bits.

## When to Use
- Every element twice except one: XOR everything (0136); missing value in 0..n: XOR indices and values (0268).
- Every element three times except one: count each bit mod 3 (0137).
- Count set bits: `n & (n - 1)` loop (0191); for all 0..n: DP on `i >> 1` (0338).
- Reverse or rebuild a fixed-width pattern: pop the low bit, push onto the result, 32 times (0190).
- Add without `+`: XOR is the sum without carries, `(a & b) << 1` is the carries (0371).
- Add numbers given as strings: right-to-left with a carry (0067).
- Digits instead of bits, with overflow: pop/push with a pre-check (0007).
- AND over a range: the common binary prefix (0201).

## Templates

### Core identities
```cpp
x & 1            // lowest bit (odd?)
(x >> k) & 1     // bit k
x & (x - 1)      // clear lowest set bit
x & -x           // lowest set bit alone
x | (1u << k)    // set bit k
x & ~(1u << k)   // clear bit k
```
```python
x & 1; (x >> k) & 1; x & (x - 1); x & -x
x & 0xFFFFFFFF                     # force 32-bit view
x if x < 2**31 else x - 2**32      # back to signed
```

### Count / fold bits
```python
while n:                 # popcount
    n &= n - 1; count += 1
for b in range(32):      # per-bit counting
    total = sum((x >> b) & 1 for x in nums)
```

### Add with carry
```python
while b:
    a, b = (a ^ b) & MASK, ((a & b) << 1) & MASK
```

### Overflow-safe digit push (32-bit)
```cpp
if (r > INT_MAX / 10 || (r == INT_MAX / 10 && d > 7)) return 0;
if (r < INT_MIN / 10 || (r == INT_MIN / 10 && d < -8)) return 0;
r = r * 10 + d;
```

## Common Variations
- **k copies except one:** count bits mod k (0137 with k = 3).
- **Two singles:** XOR all, split by the lowest set bit of the XOR (LC 260).
- **Power of two:** `n > 0 && (n & (n - 1)) == 0`.
- **Subsets as bitmasks:** iterate `mask` from 0 to 2ⁿ − 1, test bit j with `mask >> j & 1`.

## ⚠️ Pitfalls
- **Signed right shift** drags the sign bit in C++/Java; use `uint32_t` (or `>>>`).
- **`1 << 31` on int** overflows; use `1u << 31` or `1LL << 31`.
- **Python negatives:** infinite sign bits, so `while n:` never ends and results need 32-bit masking.
- **Precedence:** `x & 1 == 0` is `x & (1 == 0)`; `a + b & 1` is `(a + b) & 1`. Parenthesise.
- **Exactly 32 iterations** when reversing; stopping at n == 0 drops zeros.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0067 | [Add Binary](0067-add-binary/) | Easy | Carry addition | ✅ |
| 0136 | [Single Number](0136-single-number/) | Easy | XOR | ✅ |
| 0190 | [Reverse Bits](0190-reverse-bits/) | Easy | Shift and build | ✅ |
| 0191 | [Number of 1 Bits](0191-number-of-1-bits/) | Easy | n & (n-1) | ✅ |
| 0268 | [Missing Number](0268-missing-number/) | Easy | XOR / sum formula | ✅ |
| 0338 | [Counting Bits](0338-counting-bits/) | Easy | DP on bits | ✅ |
| 0007 | [Reverse Integer](0007-reverse-integer/) | Medium | Digit pop with overflow check | ✅ |
| 0137 | [Single Number II](0137-single-number-ii/) | Medium | Bit counting mod 3 | ✅ |
| 0201 | [Bitwise AND of Numbers Range](0201-bitwise-and-of-numbers-range/) | Medium | Common prefix | ✅ |
| 0371 | [Sum of Two Integers](0371-sum-of-two-integers/) | Medium | XOR + carry | ✅ |
