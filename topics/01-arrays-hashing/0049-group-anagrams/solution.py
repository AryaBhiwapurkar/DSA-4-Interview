"""
0049. Group Anagrams  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/group-anagrams/

Problem: Group the strings that are anagrams of each other.
         Any order of groups / words is accepted.

Examples (printed with groups sorted for stable output):
  ["eat","tea","tan","ate","nat","bat"] -> [["ate","eat","tea"],["bat"],["nat","tan"]]
  [""]                                  -> [[""]]
  ["a"]                                 -> [["a"]]

Approaches:
  1. Pairwise compare        O(n^2 * k) time, O(n) space
  2. Sorted-string key  ⭐    O(n * k log k) time, O(n * k) space   <- go-to
  3. Letter-count key        O(n * k) time, O(n * k) space
"""

from collections import Counter, defaultdict


# ---------- Approach 1: Pairwise Compare ----------
def group_anagrams_brute(strs: list[str]) -> list[list[str]]:
    res: list[list[str]] = []
    used = [False] * len(strs)
    for i, s in enumerate(strs):
        if used[i]:
            continue
        group = [s]
        for j in range(i + 1, len(strs)):
            if not used[j] and Counter(s) == Counter(strs[j]):
                used[j] = True
                group.append(strs[j])
        res.append(group)
    return res


# ---------- Approach 2: Sorted-String Key ⭐ ----------
def group_anagrams(strs: list[str]) -> list[list[str]]:
    groups: defaultdict[str, list[str]] = defaultdict(list)
    for s in strs:
        groups["".join(sorted(s))].append(s)  # all anagrams share this key
    return list(groups.values())


# ---------- Approach 3: Letter-Count Key ----------
def group_anagrams_count(strs: list[str]) -> list[list[str]]:
    groups: defaultdict[tuple[int, ...], list[str]] = defaultdict(list)
    for s in strs:
        cnt = [0] * 26
        for c in s:
            cnt[ord(c) - ord("a")] += 1
        groups[tuple(cnt)].append(s)  # lists aren't hashable; tuples are
    return list(groups.values())


# ---------- Driver ----------
def show(label: str, groups: list[list[str]]) -> None:
    print(f"{label}:", sorted(sorted(g) for g in groups))  # normalize: order is unspecified


if __name__ == "__main__":
    tests = [["eat", "tea", "tan", "ate", "nat", "bat"], [""], ["a"]]
    for strs in tests:
        show("brute ", group_anagrams_brute(strs))
        show("sorted", group_anagrams(strs))
        show("count ", group_anagrams_count(strs))
        print("---")

"""
Syntax notes (Python):
- defaultdict(list) creates an empty list on first access to a key.
- Dict keys must be hashable: str and tuple work, list doesn't.
- "".join(sorted(s)) turns a string into its sorted-letters form.
- dict.values() is a view; wrap in list() to return it.
"""
