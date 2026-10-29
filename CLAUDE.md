# DSA Revision Repo

## Purpose
Personal DSA interview revision reference. I solve problems myself and open this
repo when stuck or revising. Content must be accurate, interview-oriented, and
quick to scan. No filler.

## Gold Standard
`topics/01-arrays-hashing/0001-two-sum/` is the reference implementation.
Every problem folder must match its structure, section order, tone, and level
of detail. When in doubt, open it and mirror it.

## Structure
```
README.md                  root index of all problems
CLAUDE.md
go.mod
.claude/commands/          solve.md, topic.md
cheatsheets/
  patterns.md              signal -> pattern
  syntax.md                C++ / Python / Go side by side
topics/<NN-topic>/
  README.md                concept refresher
  <NNNN-slug>/
    README.md              interview transcript
    solution.cpp
    solution.py
    solution.go
```

## Topic Folders (NeetCode order)
01-arrays-hashing, 02-two-pointers, 03-sliding-window, 04-stack,
05-binary-search, 06-linked-list, 07-trees, 08-tries, 09-heap-priority-queue,
10-backtracking, 11-graphs, 12-advanced-graphs, 13-1d-dp, 14-2d-dp,
15-greedy, 16-intervals, 17-math-geometry, 18-bit-manipulation

Problems from other lists go into the closest topic. If none fits, ASK me
before creating a new folder. Never rename, merge, or split folders without asking.

## Naming
- Problem folder: 4-digit LeetCode number + slug from the LeetCode URL,
  e.g. `0167-two-sum-ii-input-array-is-sorted`.
- One problem = one folder, ever. Before creating, search the repo for the
  number. If it exists, only update its `lists` tag.
- All four files are mandatory: README.md, solution.cpp, solution.py, solution.go.

## Problem README: Section Order
1. Frontmatter: number, title, difficulty, topic, pattern, link, lists,
   followup_of, related
2. ⚡ 30-Second Summary: pattern, key insight (1-2 lines), go-to + complexity
3. Problem: paraphrase in 1-3 sentences + link. NEVER copy LeetCode text.
4. Hints: exactly 3, progressive, each in its own collapsed `<details>`.
   Hint 3 nearly gives it away but contains no code.
5. Clarifying Questions: including edge cases worth asking about
6. Example Walkthrough
7. Approaches: brute -> optimal. Include intermediate approaches only if
   interview-relevant. Each with idea + time + space. Mark exactly ONE as
   "⭐ Go-to" with a one-line why. The go-to is the best approach to present
   in an interview (optimal AND codeable under pressure), not always the
   asymptotically best one.
8. Dry Run: trace table of the go-to, on an example that hits the tricky part
9. Edge Case Check
10. ⚠️ Pitfalls: 2-5, including language-specific ones (C++ overflow,
    C++ map[] inserting, Go map zero value, Python mutable defaults...)
11. 🎯 What the Interviewer Wants
12. Follow-ups: standard interview follow-ups. If the problem exists in the
    repo, use a relative link. If not: `LC 0167 Two Sum II (not added yet)`.

## Solution Files
- Header comment: `NNNN. Title | Difficulty | Topic`, link, paraphrased
  problem, examples with expected outputs, approaches with complexity and ⭐.
- One function per approach, same order as the README. The go-to uses the
  LeetCode function name; the others get suffixes (Brute, Sorted...).
- Comments: short "why" comments only. Explanations live in the README.
- Driver `main` runs ALL approaches on ALL header examples.
- Footer: "Syntax notes" block, 3-6 bullets on idioms used in that file.
- C++17 with `#include <bits/stdc++.h>`. Python 3.10+ with type hints.
  Go: `package main`, stdlib only, gofmt style.
- Self-contained: if the problem needs ListNode/TreeNode etc., define them in
  the file with small build/print helpers. No shared imports between files.

## Verification (mandatory, never skip)
From inside the problem folder:
- `g++ -std=c++17 -Wall solution.cpp -o /tmp/sol && /tmp/sol`
- `python3 solution.py`
- `go run solution.go`
  (`go run .` fails: Go refuses to build a folder that also contains a .cpp file.)
All approaches must print the expected outputs. Fix until they do. Never
report a problem as done if verification failed.

## After Each Problem
1. Root README.md: set status ✅ and link the folder.
2. cheatsheets/patterns.md: add the signal -> pattern line if new.
3. cheatsheets/syntax.md: add any idiom used that isn't there yet.
4. Backfill: search the repo for "(not added yet)" mentions of this problem's
   number and convert them into relative links.
5. Update README.md by running scripts/gen_readme.py rather than editing the table by hand.

## Cheatsheet Formats
- patterns.md: grouped by topic; lines like
  `**Sorted array + pair/target** -> Two pointers (0167, 0015)`
- syntax.md: one section per operation (array/list/slice, hashmap, set, heap
  with custom comparator, stack, queue/deque, sort with comparator, strings,
  int limits/overflow), each a table with columns C++ | Python | Go.

## Git
Never commit or push. I review and commit myself.
