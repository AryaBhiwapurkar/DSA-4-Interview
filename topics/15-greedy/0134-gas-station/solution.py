"""
0134. Gas Station  |  Medium  |  Greedy
Link: https://leetcode.com/problems/gas-station/

Problem: Stations on a circle give gas[i]; driving to the next costs cost[i].
         Return the unique start index that completes the loop, or -1.

Examples:
  gas=[1,2,3,4,5], cost=[3,4,5,1,2]   -> 3
  gas=[2,3,4], cost=[3,4,3]           -> -1
  gas=[5], cost=[4]                   -> 0
  gas=[3,1,1], cost=[1,2,2]           -> 0
  gas=[5,1,2,3,4], cost=[4,4,1,5,1]   -> 4

Approaches:
  1. Simulate from every start    O(n^2) time, O(1) space
  2. One pass, reset on negative tank  ⭐   O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Simulate Every Start ----------
def can_complete_circuit_brute(gas: list[int], cost: list[int]) -> int:
    n = len(gas)
    for s in range(n):
        tank = 0
        for k in range(n):
            i = (s + k) % n
            tank += gas[i] - cost[i]
            if tank < 0:
                break
        else:  # never ran dry
            return s
    return -1


# ---------- Approach 2: One Pass ⭐ ----------
def can_complete_circuit(gas: list[int], cost: list[int]) -> int:
    if sum(gas) < sum(cost):  # not enough gas overall
        return -1
    start, tank = 0, 0
    for i in range(len(gas)):
        tank += gas[i] - cost[i]
        if tank < 0:  # no start in [start, i] works: try i + 1
            start, tank = i + 1, 0
    return start


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ([1, 2, 3, 4, 5], [3, 4, 5, 1, 2]),
        ([2, 3, 4], [3, 4, 3]),
        ([5], [4]),
        ([3, 1, 1], [1, 2, 2]),
        ([5, 1, 2, 3, 4], [4, 4, 1, 5, 1]),
    ]
    for gas, cost in tests:
        print("brute:", can_complete_circuit_brute(gas, cost))
        print("pass :", can_complete_circuit(gas, cost))
        print("---")

"""
Syntax notes (Python):
- for ... else: the else runs only if the loop finished without break.
- (s + k) % n wraps the index around the circle.
- start, tank = i + 1, 0 resets both in one statement.
"""
