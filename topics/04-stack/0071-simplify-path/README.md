---
number: 71
title: Simplify Path
difficulty: Medium
topic: Stack
pattern: Stack of directory names
link: https://leetcode.com/problems/simplify-path/
lists: [LC Top Interview 150]
followup_of: []
related: ["0020 Valid Parentheses", "0150 Evaluate Reverse Polish Notation", "1598 Crawler Log Folder"]
---

# 0071. Simplify Path

## ⚡ 30-Second Summary
**Pattern:** Stack of directory names
**Key insight:** Split on `/`. Empty parts and `.` do nothing, `..` pops the last directory (if any), anything else is a directory name and gets pushed. Join the stack with `/`.
**Go-to:** Split + stack, O(n) time, O(n) space

## Problem
Given an absolute Unix-style path, return its canonical form: one leading `/`, single slashes between names, no trailing slash, and `.`/`..` resolved. Any other name made of dots (like `...`) is a regular directory name. [LeetCode](https://leetcode.com/problems/simplify-path/)

**Examples:**
```
Input:  path = "/home/"
Output: "/home"
Why:    The trailing slash is dropped.

Input:  path = "/home//foo/"
Output: "/home/foo"
Why:    Repeated slashes count as one.

Input:  path = "/home/user/Documents/../Pictures"
Output: "/home/user/Pictures"
Why:    ".." cancels "Documents".

Input:  path = "/../"
Output: "/"
Why:    ".." at the root stays at the root.

Input:  path = "/.../a/../b/c/../d/./"
Output: "/.../b/d"
Why:    "..." is just a name; "a" and "c" are cancelled; "." is ignored.
```

**Constraints:**
- 1 ≤ n ≤ 3000; letters, digits, `.`, `/`, `_`.
- The path is absolute (starts with `/`).

## Hints
<details><summary>Hint 1</summary>
Which pieces between slashes matter, and which can you throw away?
</details>
<details><summary>Hint 2</summary>
`..` undoes the most recent directory. "Most recent" suggests a stack.
</details>
<details><summary>Hint 3</summary>
Split by `/`. Skip "" and ".". On "..", pop if non-empty. Otherwise push. Answer is "/" + join(stack, "/").
</details>

## Clarifying Questions
- Always absolute? (Yes.)
- Is `...` special? (No, it's a normal name.)
- What does `..` at the root do? (Nothing.)
- Do I need to handle symlinks? (No.)

## Example Walkthrough
`"/.../a/../b/c/../d/./"` splits into `["", "...", "a", "..", "b", "c", "..", "d", ".", ""]`.
- "..." push, "a" push, ".." pops a, "b" push, "c" push, ".." pops c, "d" push. "." and "" skipped.
- Stack: [..., b, d], so the answer is "/.../b/d".

## Approaches

### 1. Split + Stack ⭐ Go-to: O(n) time, O(n) space
There's no meaningful brute force here; the stack is the natural model of "current directory".
**Why it's the go-to:** a direct translation of the rules; the only care needed is the special parts.

## Dry Run (Approach 1)
`"/home/user/Documents/../Pictures"`

| part | action | stack after |
|------|--------|-------------|
| "" | skip | [] |
| home | push | [home] |
| user | push | [home, user] |
| Documents | push | [home, user, Documents] |
| .. | pop | [home, user] |
| Pictures | push | [home, user, Pictures] |
| result | "/" + join | **"/home/user/Pictures"** |

## Edge Case Check
- `"/"`: everything skipped, empty stack, "/". ✅
- `"/../"`: pop on empty is ignored, "/". ✅
- `"/a/./b/../../c/"`: [a] → [a,b] → [a] → [] → [c], so "/c". ✅
- `"/..hidden"`: "..hidden" is a name, not "..". ✅

## ⚠️ Pitfalls
- **Popping an empty stack on `..`**: must be a no-op.
- **Treating any dot-name as special**: only exactly "." and ".." are.
- **Returning "" for an empty stack**: the root is "/".
- **C++ `getline(ss, part, '/')`** yields "" for repeated slashes; skip it, don't push it.

## 🎯 What the Interviewer Wants
- A clean rule table: "", ".", "..", name.
- The root and empty-stack edge cases without being prompted.
- Linear time and a short implementation.

## Follow-ups
- **Relative paths with a current working directory:** start the stack from cwd's parts.
- **Only count depth (no names needed):** a counter: LC 1598 Crawler Log Folder (not added yet)
- **Other stack-as-context problems:** [LC 0150 Evaluate Reverse Polish Notation](../0150-evaluate-reverse-polish-notation/)
