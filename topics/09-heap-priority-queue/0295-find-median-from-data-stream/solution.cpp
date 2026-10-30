/*
 * 0295. Find Median from Data Stream  |  Hard  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/find-median-from-data-stream/
 *
 * Problem: addNum(num) and findMedian() over a stream of integers.
 *
 * Examples:
 *   add 1, add 2, median, add 3, median
 *     -> [null,null,null,1.50000,null,2.00000]
 *   add -1, median, add -2, median, add -3, median, add -4, median, add -5, median
 *     -> [null,null,-1.00000,null,-1.50000,null,-2.00000,null,-2.50000,null,-3.00000]
 *
 * Approaches:
 *   1. Sorted list with insertion   O(n) add, O(1) median, O(n) space
 *   2. Two heaps  ⭐                 O(log n) add, O(1) median, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sorted List With Insertion ----------
class MedianFinderSorted {
    vector<int> a;
public:
    void addNum(int x) { a.insert(upper_bound(a.begin(), a.end(), x), x); }
    double findMedian() {
        int n = a.size();
        return n % 2 ? a[n / 2] : (a[n / 2 - 1] + (double)a[n / 2]) / 2.0;
    }
};

// ---------- Approach 2: Two Heaps ⭐ ----------
class MedianFinder {
    priority_queue<int> low;                              // max-heap: smaller half
    priority_queue<int, vector<int>, greater<int>> high;  // min-heap: larger half
public:
    void addNum(int x) {
        low.push(x);                       // 1) into the lower half
        high.push(low.top());              // 2) its max moves up: halves stay ordered
        low.pop();
        if (high.size() > low.size()) {    // 3) rebalance: low keeps the extra one
            low.push(high.top());
            high.pop();
        }
    }
    double findMedian() {
        if (low.size() > high.size()) return low.top();
        return (low.top() + (double)high.top()) / 2.0;
    }
};

// ---------- Driver ----------
template <class M>
void run(const string& label, const vector<string>& ops, const vector<int>& args) {
    M m;
    printf("%s: [null", label.c_str());
    for (size_t i = 1; i < ops.size(); i++) {
        if (ops[i] == "addNum") { m.addNum(args[i]); printf(",null"); }
        else printf(",%.5f", m.findMedian());
    }
    printf("]\n");
}

int main() {
    vector<pair<vector<string>, vector<int>>> tests = {
        {{"MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"}, {0, 1, 2, 0, 3, 0}},
        {{"MedianFinder", "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian",
          "addNum", "findMedian"},
         {0, -1, 0, -2, 0, -3, 0, -4, 0, -5, 0}},
    };
    for (auto& [ops, args] : tests) {
        run<MedianFinderSorted>("sorted", ops, args);
        run<MedianFinder>("heaps ", ops, args);
        printf("---\n");
    }
}

/*
 * Syntax notes (C++):
 * - Two heap types side by side: priority_queue<int> (max) and the
 *   greater<int> version (min).
 * - (a + (double)b) / 2.0 avoids integer division and int overflow.
 */
