# 09. Heap / Priority Queue

## Core Idea
A heap gives O(1) access to the min (or max) and O(log n) push/pop. Use it whenever you repeatedly need "the best remaining item" while items keep arriving or changing. Two inversions are worth memorizing: to keep the **k largest**, use a **min**-heap of size k (its top is the k-th largest); to keep the **k smallest**, use a **max**-heap of size k. Heaps also merge k sorted sources (push each source's head, pop the best, push that source's next).

## When to Use
- Top-k / k-th largest or smallest, static or streaming (0703, 0215, 0973).
- Repeatedly take the largest/smallest and put something back: simulations (1046, 0621).
- Median or other order statistics of a stream: two heaps (0295).
- Merge k sorted lists or rows; k smallest pairs/sums; news feeds (0355, 0373).
- Greedy "best available option" where availability grows over time: sort by requirement + heap (0502).

## Templates

### Min-heap of size k (k-th largest)
```cpp
priority_queue<int, vector<int>, greater<int>> pq;   // min-heap
for (int x : nums) {
    pq.push(x);
    if ((int)pq.size() > k) pq.pop();
}
return pq.top();
```
```python
h = []
for x in nums:
    heapq.heappush(h, x)
    if len(h) > k:
        heapq.heappop(h)
return h[0]
```
```go
h := &IntHeap{}                       // IntHeap: Less is h[i] < h[j]
for _, x := range nums {
	heap.Push(h, x)
	if h.Len() > k {
		heap.Pop(h)
	}
}
return (*h)[0]
```

### K-way merge
```cpp
using T = tuple<int, int, int>;                 // (value, source, index)
priority_queue<T, vector<T>, greater<T>> pq;
for (int s = 0; s < k; s++) if (!src[s].empty()) pq.push({src[s][0], s, 0});
while (!pq.empty()) {
    auto [v, s, i] = pq.top(); pq.pop();
    out.push_back(v);
    if (i + 1 < (int)src[s].size()) pq.push({src[s][i + 1], s, i + 1});
}
```
```python
h = [(src[s][0], s, 0) for s in range(k) if src[s]]
heapq.heapify(h)
while h:
    v, s, i = heapq.heappop(h)
    out.append(v)
    if i + 1 < len(src[s]):
        heapq.heappush(h, (src[s][i + 1], s, i + 1))
```

### Two heaps (running median)
```python
low, high = [], []          # low: max-heap via negatives
def add(x):
    heapq.heappush(low, -x)
    heapq.heappush(high, -heapq.heappop(low))
    if len(high) > len(low):
        heapq.heappush(low, -heapq.heappop(high))
def median():
    return -low[0] if len(low) > len(high) else (-low[0] + high[0]) / 2
```

## Common Variations
- **Max-heap in Python:** push negatives (or (-key, tiebreak, item)).
- **Custom order:** C++ comparator returns `a > b` for a min-heap; Go implements `Less`; Python uses tuples.
- **Tie-breakers:** add an index so incomparable payloads (nodes, lists) are never compared.
- **Cooldown / delayed re-insertion:** a queue of (item, readyTime) beside the heap (0621).
- **Sort + pointer + heap:** unlock items in requirement order, pick the best unlocked one (0502).
- **Quickselect** beats a heap for one-off k-th element on an array (O(n) average) (0215).

## ⚠️ Pitfalls
- **Wrong heap direction:** k largest needs a min-heap; k smallest needs a max-heap.
- **C++ `priority_queue` is a max-heap by default**, and `pop()` returns void.
- **Go `container/heap`:** call `heap.Push/Pop`, not the methods directly; `heap.Init` after filling the slice.
- **Python heap of tuples with unorderable items:** add a unique tiebreaker.
- **Ties in output order:** "any order" answers may differ between languages; sort before comparing.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0703 | [Kth Largest Element in a Stream](0703-kth-largest-element-in-a-stream/) | Easy | Min-heap of size k | ✅ |
| 1046 | [Last Stone Weight](1046-last-stone-weight/) | Easy | Max-heap simulation | ✅ |
| 0215 | [Kth Largest Element in an Array](0215-kth-largest-element-in-an-array/) | Medium | Min-heap of size k / quickselect | ✅ |
| 0355 | [Design Twitter](0355-design-twitter/) | Medium | Heap merge of k feeds | ✅ |
| 0373 | [Find K Pairs with Smallest Sums](0373-find-k-pairs-with-smallest-sums/) | Medium | Min-heap frontier | ✅ |
| 0621 | [Task Scheduler](0621-task-scheduler/) | Medium | Greedy counting / max-heap | ✅ |
| 0973 | [K Closest Points to Origin](0973-k-closest-points-to-origin/) | Medium | Max-heap of size k | ✅ |
| 0295 | [Find Median from Data Stream](0295-find-median-from-data-stream/) | Hard | Two heaps | ✅ |
| 0502 | [IPO](0502-ipo/) | Hard | Sort by capital + max-heap | ✅ |
