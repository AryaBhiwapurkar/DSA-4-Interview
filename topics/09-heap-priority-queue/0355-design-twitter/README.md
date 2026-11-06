---
number: 355
title: Design Twitter
difficulty: Medium
topic: Heap / Priority Queue
pattern: Heap merge of k feeds
link: https://leetcode.com/problems/design-twitter/
lists: [NeetCode 150]
followup_of: []
related: ["0023 Merge k Sorted Lists", "0146 LRU Cache", "0373 Find K Pairs with Smallest Sums"]
---

# 0355. Design Twitter

## ⚡ 30-Second Summary
**Pattern:** Merge k sorted lists with a heap, stopping after 10
**Key insight:** Each user's tweets are already in time order (append with a global counter). A news feed is "the 10 most recent across self + followees": a k-way merge of those lists from the end. A max-heap of each list's newest unseen tweet yields them in order, and you stop after 10.
**Go-to:** Per-user tweet lists + max-heap merge, O(F + 10 log F) per feed (F = followees)

## Problem
Design `postTweet(userId, tweetId)`, `getNewsFeed(userId)` (10 most recent tweet ids from the user and the people they follow, newest first), `follow(followerId, followeeId)` and `unfollow(followerId, followeeId)`. [LeetCode](https://leetcode.com/problems/design-twitter/)

**Examples:**
```
Input:  ["Twitter","postTweet","getNewsFeed","follow","postTweet","getNewsFeed","unfollow","getNewsFeed"]
        [[],[1,5],[1],[1,2],[2,6],[1],[1,2],[1]]
Output: [null,null,[5],null,null,[6,5],null,[5]]
Why:    After following user 2, user 1 sees 2's newer tweet 6 first; after unfollowing,
        only their own tweet 5 remains.
```

**Constraints:**
- User ids and tweet ids up to 500 / 10⁴; up to 3·10⁴ calls; tweet ids are unique.
- A user never follows themselves through `follow`, but their own tweets are in their feed.

## Hints
<details><summary>Hint 1</summary>
Which data structures do you need per user?
</details>
<details><summary>Hint 2</summary>
A feed merges several time-sorted lists. Have you seen "merge k sorted lists" before?
</details>
<details><summary>Hint 3</summary>
Global timestamp per tweet. getNewsFeed: push each relevant user's latest tweet into a max-heap by time; pop, record, push that user's previous tweet; stop at 10.
</details>

## Clarifying Questions
- Is the user's own timeline in their feed? (Yes.)
- Unfollowing someone not followed? (No-op.)
- Fewer than 10 tweets available? (Return what exists.)

## Example Walkthrough
post(1,5) at t=0. feed(1) → [5]. follow(1,2). post(2,6) at t=1. feed(1): heap has (0,5) from 1 and (1,6) from 2 → pop 6, then 5 → [6,5]. unfollow(1,2) → feed(1) = [5].

## Approaches

### 1. Global Tweet List, Scan From Newest: O(total tweets) per feed
Keep one list of (user, tweet) in time order; walk backwards and take tweets whose author is the user or a followee, until 10.

### 2. Per-User Lists + Heap Merge ⭐ Go-to: O(F log F + 10 log F) per feed
**Why it's the go-to:** feed cost depends on how many people you follow, not on all tweets ever posted; it's the 0023 pattern applied to a design.

## Dry Run (Approach 2)
Second feed(1): tweets[1] = [(0,5)], tweets[2] = [(1,6)]

| step | heap (time, id) | pop | push next from same user | feed |
|------|-----------------|-----|--------------------------|------|
| seed | (1,6), (0,5) | | | |
| 1 | | (1,6) | none (user 2 has no older) | [6] |
| 2 | | (0,5) | none | [6,5] |

## Edge Case Check
- User with no tweets and no follows: []. ✅
- More than 10 tweets: exactly the 10 newest. ✅
- Following the same person twice: a set ignores the duplicate. ✅

## ⚠️ Pitfalls
- **Forgetting the user's own tweets** in the feed.
- **Using tweet ids as timestamps**: ids aren't increasing; keep a counter.
- **Unfollow when not following / follow self**: guard both.
- **Python heapq**: max-heap via negated times.

## 🎯 What the Interviewer Wants
- Clean data model: tweets per user, follow sets, global clock.
- Recognize the k-way merge and stop early at 10.

## Follow-ups
- **Merging sorted lists in general:** [LC 0023 Merge k Sorted Lists](../../06-linked-list/0023-merge-k-sorted-lists/)
- **Scale:** precompute feeds on write (fan-out on write) vs. merge on read; celebrities break fan-out.
- **Cap stored tweets per user at 10:** older tweets can never appear in a feed.
