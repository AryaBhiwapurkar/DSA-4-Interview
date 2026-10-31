"""
0332. Reconstruct Itinerary  |  Hard  |  Advanced Graphs
Link: https://leetcode.com/problems/reconstruct-itinerary/

Problem: Use every ticket [from, to] exactly once, starting at "JFK".
         If several itineraries work, return the lexicographically smallest.

Examples:
  [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
      -> ["JFK","MUC","LHR","SFO","SJC"]
  [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
      -> ["JFK","ATL","JFK","SFO","ATL","SFO"]
  [["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]
      -> ["JFK","NRT","JFK","KUL"]   (smallest first move KUL is a dead end)

Approaches:
  1. Backtracking, smallest destination first   O(E^d) worst case, O(E) space
  2. Hierholzer (post-order Eulerian path)  ⭐   O(E log E) time, O(E) space   <- go-to
"""

from collections import defaultdict


# ---------- Approach 1: Backtracking ----------
def find_itinerary_backtrack(tickets: list[list[str]]) -> list[str]:
    adj: dict[str, list[str]] = defaultdict(list)
    for a, b in sorted(tickets):  # sorted: first full path found = smallest
        adj[a].append(b)
    path = ["JFK"]

    def bt() -> bool:
        if len(path) == len(tickets) + 1:
            return True
        dests = adj[path[-1]]
        for i in range(len(dests)):
            v = dests.pop(i)  # use the ticket
            path.append(v)
            if bt():
                return True
            path.pop()
            dests.insert(i, v)  # give it back
        return False

    bt()
    return path


# ---------- Approach 2: Hierholzer ⭐ ----------
def find_itinerary(tickets: list[list[str]]) -> list[str]:
    adj: dict[str, list[str]] = defaultdict(list)
    for a, b in sorted(tickets, reverse=True):  # descending: pop() yields the smallest
        adj[a].append(b)
    route: list[str] = []

    def visit(u: str) -> None:
        while adj[u]:
            visit(adj[u].pop())
        route.append(u)  # post-order: dead ends land first

    visit("JFK")
    return route[::-1]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]],
        [["JFK", "SFO"], ["JFK", "ATL"], ["SFO", "ATL"], ["ATL", "JFK"], ["ATL", "SFO"]],
        [["JFK", "KUL"], ["JFK", "NRT"], ["NRT", "JFK"]],
    ]
    for t in tests:
        print("backtrack :", find_itinerary_backtrack(t))
        print("hierholzer:", find_itinerary(t))
        print("---")

"""
Syntax notes (Python):
- sorted(tickets, reverse=True) sorts list pairs by (from, to) descending.
- list.pop() is O(1) from the end; list.pop(i) / insert(i, v) are O(n) but undo cleanly.
- route[::-1] returns a reversed copy.
- Recursion depth ≤ number of tickets (≤ 300), well under Python's default limit of 1000.
"""
