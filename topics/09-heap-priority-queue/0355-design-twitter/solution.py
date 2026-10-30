"""
0355. Design Twitter  |  Medium  |  Heap / Priority Queue
Link: https://leetcode.com/problems/design-twitter/

Problem: postTweet, getNewsFeed (10 most recent from self + followees),
         follow, unfollow.

Examples:
  post(1,5), feed(1), follow(1,2), post(2,6), feed(1), unfollow(1,2), feed(1)
    -> [null,null,[5],null,null,[6,5],null,[5]]
  post(1,1)..post(1,11), feed(1), unfollow(1,3)   (more than 10; unfollow a stranger)
    -> [null x11, [11,10,9,8,7,6,5,4,3,2], null]

Approaches:
  1. Global tweet list, scan newest first     O(total tweets) per feed
  2. Per-user lists + heap merge  ⭐           O(F log F + 10 log F) per feed   <- go-to
"""

import heapq
from collections import defaultdict


# ---------- Approach 1: Global Tweet List ----------
class TwitterScan:
    def __init__(self) -> None:
        self.tweets: list[tuple[int, int]] = []  # (user, tweetId) in time order
        self.follows: defaultdict[int, set[int]] = defaultdict(set)

    def postTweet(self, u: int, t: int) -> None:
        self.tweets.append((u, t))

    def getNewsFeed(self, u: int) -> list[int]:
        res = []
        for author, tid in reversed(self.tweets):
            if author == u or author in self.follows[u]:
                res.append(tid)
                if len(res) == 10:
                    break
        return res

    def follow(self, a: int, b: int) -> None:
        if a != b:
            self.follows[a].add(b)

    def unfollow(self, a: int, b: int) -> None:
        self.follows[a].discard(b)


# ---------- Approach 2: Per-User Lists + Heap Merge ⭐ ----------
class Twitter:
    def __init__(self) -> None:
        self.clock = 0  # global time: tweet ids aren't ordered
        self.tweets: defaultdict[int, list[tuple[int, int]]] = defaultdict(list)  # user -> (time, id)
        self.follows: defaultdict[int, set[int]] = defaultdict(set)

    def postTweet(self, u: int, t: int) -> None:
        self.tweets[u].append((self.clock, t))
        self.clock += 1

    def getNewsFeed(self, u: int) -> list[int]:
        h = []  # (-time, user, index): newest on top
        for v in self.follows[u] | {u}:  # own tweets count too
            if self.tweets.get(v):
                i = len(self.tweets[v]) - 1
                h.append((-self.tweets[v][i][0], v, i))
        heapq.heapify(h)
        res = []
        while h and len(res) < 10:
            _, v, i = heapq.heappop(h)
            res.append(self.tweets[v][i][1])
            if i > 0:  # that user's next newest
                heapq.heappush(h, (-self.tweets[v][i - 1][0], v, i - 1))
        return res

    def follow(self, a: int, b: int) -> None:
        if a != b:
            self.follows[a].add(b)

    def unfollow(self, a: int, b: int) -> None:
        self.follows[a].discard(b)


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[list[int]]) -> str:
    tw = cls()
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        r = getattr(tw, op)(*a)
        out.append("null" if r is None else "[" + ",".join(map(str, r)) + "]")
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    ops2 = ["Twitter"] + ["postTweet"] * 11 + ["getNewsFeed", "unfollow"]
    args2 = [[]] + [[1, t] for t in range(1, 12)] + [[1], [1, 3]]
    tests = [
        (["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"],
         [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]),
        (ops2, args2),
    ]
    for ops, args in tests:
        print("scan:", run(TwitterScan, ops, args))
        print("heap:", run(Twitter, ops, args))
        print("---")

"""
Syntax notes (Python):
- set.discard(x) removes if present (no KeyError, unlike remove).
- `self.follows[u] | {u}` is a set union without mutating follows.
- getattr(obj, name)(*args) dispatches a method call by name.
"""
