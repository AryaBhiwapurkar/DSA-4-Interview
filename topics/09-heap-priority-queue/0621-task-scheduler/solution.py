"""
0621. Task Scheduler  |  Medium  |  Heap / Priority Queue
Link: https://leetcode.com/problems/task-scheduler/

Problem: Unit-time tasks A-Z; equal tasks must be >= n units apart (idle
         allowed). Minimum total time.

Examples:
  [A,A,A,B,B,B], n 2                  -> 8
  [A,C,A,B,D,B], n 1                  -> 6
  [A,A,A,B,B,B], n 3                  -> 10
  [A,A,A,A,A,A,B,C,D,E,F,G], n 2      -> 16
  [A,B,A], n 0                        -> 3

Approaches:
  1. Max-heap + cooldown queue   O(T log 26) time, O(26) space
  2. Counting formula  ⭐         O(T) time, O(1) space   <- go-to
"""

import heapq
from collections import Counter, deque


# ---------- Approach 1: Max-Heap + Cooldown Queue ----------
def least_interval_heap(tasks: list[str], n: int) -> int:
    h = [-c for c in Counter(tasks).values()]  # negated counts: max-heap
    heapq.heapify(h)
    cool: deque[tuple[int, int]] = deque()  # (negated remaining, ready time)
    time = 0
    while h or cool:
        time += 1
        if h:  # run the most frequent available task
            c = heapq.heappop(h) + 1  # one fewer remaining (still negated)
            if c < 0:
                cool.append((c, time + n))
        # else: idle this unit
        if cool and cool[0][1] == time:
            heapq.heappush(h, cool.popleft()[0])
    return time


# ---------- Approach 2: Counting Formula ⭐ ----------
def least_interval(tasks: list[str], n: int) -> int:
    cnt = Counter(tasks)
    maxc = max(cnt.values())
    tied = sum(1 for c in cnt.values() if c == maxc)  # tasks sharing the max count
    return max(len(tasks), (maxc - 1) * (n + 1) + tied)  # enough variety -> no idling


# ---------- Driver ----------
if __name__ == "__main__":
    for s, n in [("AAABBB", 2), ("ACABDB", 1), ("AAABBB", 3), ("AAAAAABCDEFG", 2), ("ABA", 0)]:
        tasks = list(s)
        print("heap   :", least_interval_heap(tasks, n))
        print("formula:", least_interval(tasks, n))
        print("---")

"""
Syntax notes (Python):
- Counter(iterable).values() gives the frequencies.
- Negated counts turn heapq's min-heap into a max-heap; "+1" on a negated
  count means one fewer remaining.
"""
