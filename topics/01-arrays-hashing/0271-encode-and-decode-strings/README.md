---
number: 271
title: Encode and Decode Strings
difficulty: Medium
topic: Arrays & Hashing
pattern: Length-prefix encoding
link: https://leetcode.com/problems/encode-and-decode-strings/
lists: [NeetCode 150]
followup_of: []
related: ["0297 Serialize and Deserialize Binary Tree", "0443 String Compression"]
---

# 0271. Encode and Decode Strings

## ⚡ 30-Second Summary
**Pattern:** Length-prefix (framing) encoding
**Key insight:** Any delimiter can also appear inside a string. Writing each string's length first ("5#Hello") tells the decoder exactly how many characters to read, so the content can contain anything, including '#'.
**Go-to:** Length + '#' + string, O(total chars) time and space

## Problem
Design `encode(list of strings) -> string` and `decode(string) -> list of strings` so that `decode(encode(strs))` returns the original list. Strings may contain any of the 256 ASCII characters. (LeetCode Premium; also on LintCode 659.) [LeetCode](https://leetcode.com/problems/encode-and-decode-strings/)

**Examples:**
```
Input:  ["Hello","World"]
Output: ["Hello","World"]
Why:    Encoded as "5#Hello5#World"; decode reads 5 chars, then 5 chars.

Input:  [""]
Output: [""]
Why:    Encoded as "0#"; the decoder reads a zero-length string.
```

**Constraints:**
- 1 ≤ number of strings ≤ 200; 0 ≤ each length ≤ 200.
- Any of the 256 ASCII characters can appear, so no character is safe as a plain delimiter.
- No serialization libraries (e.g. eval, JSON) allowed.

## Hints
<details><summary>Hint 1</summary>
Why does joining with "," fail? Find an input that breaks it.
</details>
<details><summary>Hint 2</summary>
Either escape the delimiter inside strings, or avoid needing one inside the content.
</details>
<details><summary>Hint 3</summary>
Prefix each string with its length and a separator: the decoder reads digits up to '#', then exactly that many characters.
</details>

## Clarifying Questions
- Which characters can appear? (Any ASCII, including digits and '#'.)
- Can strings or the list be empty? (Strings yes; handle the empty list too.)
- Must the encoding be stateless? (Yes, the decoder only sees the encoded string.)

## Example Walkthrough
`["4#ab", ""]`
- Encode: "4#4#ab" + "0#" = "4#4#ab0#".
- Decode: read "4" until '#', take next 4 chars "4#ab". Then read "0" until '#', take 0 chars "". Done.

## Approaches

### 1. Escaped Delimiter: O(N) time, O(N) space
Double every '/' inside a string ("//"), and end each string with "/;". When decoding, "//" means a literal '/', and "/;" means end of string. Works, but easy to get subtly wrong.

### 2. Length Prefix ⭐ Go-to: O(N) time, O(N) space
For each string write `len(s) + "#" + s`. Decode: read digits up to '#', parse the length, slice that many chars, repeat.
**Why it's the go-to:** no escaping, no special cases, and the content never needs to be inspected. It's how real wire protocols frame messages.

## Dry Run (Approach 2)
Decode `"5#Hello5#World"`

| i (start) | j (at '#') | length | string | next i |
|-----------|------------|--------|--------|--------|
| 0 | 1 | 5 | "Hello" | 7 |
| 7 | 8 | 5 | "World" | 14 = end |

## Edge Case Check
- `[""]`: "0#" decodes to [""]. ✅
- Empty list: "" decodes to []. ✅
- Strings containing '#' or digits, `["1#2", "#"]`: "3#1#21##" decodes correctly because content is read by length. ✅

## ⚠️ Pitfalls
- **Plain delimiter join** breaks as soon as a string contains the delimiter.
- **Searching for '#' from the string start instead of from i:** the first '#' may be inside earlier content.
- **Multi-digit lengths:** read all digits up to '#', not a single char.
- **Non-ASCII (UTF-8):** lengths must be in bytes on both sides (Go `len` is bytes; Python `len` is code points, so encode to bytes if mixing).

## 🎯 What the Interviewer Wants
- Show why a naive delimiter fails.
- A self-describing format (length prefix) and a correct decoder loop.
- Discuss Unicode / byte lengths if prompted.

## Follow-ups
- **Fixed-width length header (e.g. 4 bytes) instead of '#':** no separator needed, decoder reads 4 bytes then the payload.
- **Serialize a tree:** [LC 0297 Serialize and Deserialize Binary Tree](../../07-trees/0297-serialize-and-deserialize-binary-tree/)
- **Arbitrary Unicode:** encode each string to UTF-8 bytes and prefix the byte length.
