/*
 * 0239. Sliding Window Maximum  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/sliding-window-maximum/
 *
 * Problem: Return the maximum of every window of size k as it slides
 *          from left to right.
 *
 * Examples:
 *   [1,3,-1,-3,5,3,6,7], k=3   -> [3,3,5,5,6,7]
 *   [1], k=1                   -> [1]
 *   [9,8,7,6], k=2             -> [9,8,7]
 *   [4,4,4], k=2               -> [4,4]
 *
 * Approaches:
 *   1. Brute force                   O(n*k) time, O(1) space
 *   2. Max-heap with lazy deletion   O(n log n) time, O(n) space
 *   3. Monotonic deque  ⭐            O(n) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
vector<int> maxSlidingWindowBrute(const vector<int>& nums, int k) {
    vector<int> res;
    for (int i = 0; i + k <= (int)nums.size(); i++)
        res.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
    return res;
}

// ---------- Approach 2: Max-Heap With Lazy Deletion ----------
vector<int> maxSlidingWindowHeap(const vector<int>& nums, int k) {
    priority_queue<pair<int, int>> pq;                       // (value, index), max-heap
    vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        pq.push({nums[i], i});
        if (i >= k - 1) {
            while (pq.top().second <= i - k) pq.pop();       // discard maxes that left the window
            res.push_back(pq.top().first);
        }
    }
    return res;
}

// ---------- Approach 3: Monotonic Deque ⭐ ----------
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    deque<int> dq;                                           // indices; values strictly decreasing
    vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();          // front left the window
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back(); // dominated: never a max again
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 3, -1, -3, 5, 3, 6, 7}, 3}, {{1}, 1}, {{9, 8, 7, 6}, 2}, {{4, 4, 4}, 2}
    };
    for (auto& [nums, k] : tests) {
        print("brute", maxSlidingWindowBrute(nums, k));
        print("heap ", maxSlidingWindowHeap(nums, k));
        print("deque", maxSlidingWindow(nums, k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::deque: push_back/pop_back/push_front/pop_front, front()/back(), all O(1).
 * - priority_queue<pair<int,int>> is a max-heap ordered by .first, then .second.
 * - *max_element(first, last) returns the max in a sub-range.
 */
