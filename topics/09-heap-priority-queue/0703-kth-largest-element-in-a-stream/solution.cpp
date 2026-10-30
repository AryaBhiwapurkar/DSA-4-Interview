/*
 * 0703. Kth Largest Element in a Stream  |  Easy  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/kth-largest-element-in-a-stream/
 *
 * Problem: KthLargest(k, nums); add(val) returns the k-th largest so far.
 *
 * Examples:
 *   k 3, [4,5,8,2]; add 3, 5, 10, 9, 4      -> [null,4,5,5,8,8]
 *   k 4, [7,7,7,7,8,3]; add 2, 10, 9, 9     -> [null,7,7,7,8]
 *   k 1, []; add -3, -2, -4                 -> [null,-3,-2,-2]
 *
 * Approaches:
 *   1. Sorted list with insertion   O(n) per add, O(n) space
 *   2. Min-heap of size k  ⭐        O(log k) per add, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sorted List With Insertion ----------
class KthLargestSorted {
    int k;
    vector<int> a;                         // ascending
public:
    KthLargestSorted(int k, const vector<int>& nums) : k(k), a(nums) { sort(a.begin(), a.end()); }
    int add(int val) {
        a.insert(upper_bound(a.begin(), a.end(), val), val);   // O(n) shift
        return a[a.size() - k];
    }
};

// ---------- Approach 2: Min-Heap of Size k ⭐ ----------
class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;   // min-heap of the k largest
public:
    KthLargest(int k, const vector<int>& nums) : k(k) {
        for (int x : nums) add(x);
    }
    int add(int val) {
        pq.push(val);
        if ((int)pq.size() > k) pq.pop();  // drop the smallest: it's not in the top k
        return pq.top();                   // smallest of the top k = k-th largest
    }
};

// ---------- Driver ----------
template <class K>
void run(const string& label, int k, const vector<int>& nums, const vector<int>& adds) {
    K obj(k, nums);
    cout << label << ": [null";
    for (int v : adds) cout << "," << obj.add(v);
    cout << "]\n";
}

int main() {
    vector<tuple<int, vector<int>, vector<int>>> tests = {
        {3, {4, 5, 8, 2}, {3, 5, 10, 9, 4}}, {4, {7, 7, 7, 7, 8, 3}, {2, 10, 9, 9}}, {1, {}, {-3, -2, -4}}
    };
    for (auto& [k, nums, adds] : tests) {
        run<KthLargestSorted>("sorted", k, nums, adds);
        run<KthLargest>("heap  ", k, nums, adds);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - priority_queue<int, vector<int>, greater<int>> is a min-heap.
 * - a.insert(upper_bound(...), v) keeps a vector sorted (O(n) shifting).
 * - Member initializer `k(k)` disambiguates the parameter from the member.
 */
