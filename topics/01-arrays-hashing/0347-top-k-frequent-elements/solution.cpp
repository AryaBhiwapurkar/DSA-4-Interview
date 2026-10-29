/*
 * 0347. Top K Frequent Elements  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Problem: Return the k most frequent values (any order; answer is unique).
 *
 * Examples (printed sorted for stable output):
 *   [1,1,1,2,2,3], k=2             -> [1,2]
 *   [1], k=1                       -> [1]
 *   [1,2,1,2,1,2,3,1,3,2], k=2     -> [1,2]
 *   [4,4,-1,-1,-1,7], k=1          -> [-1]
 *
 * Approaches:
 *   1. Sort by frequency     O(n log n) time, O(n) space
 *   2. Min-heap of size k    O(n log k) time, O(n) space
 *   3. Bucket sort  ⭐        O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort by Frequency ----------
vector<int> topKFrequentSorted(const vector<int>& nums, int k) {
    unordered_map<int, int> cnt;
    for (int x : nums) cnt[x]++;
    vector<pair<int, int>> byFreq(cnt.begin(), cnt.end());          // (value, count)
    sort(byFreq.begin(), byFreq.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    vector<int> res;
    for (int i = 0; i < k; i++) res.push_back(byFreq[i].first);
    return res;
}

// ---------- Approach 2: Min-Heap of Size k ----------
vector<int> topKFrequentHeap(const vector<int>& nums, int k) {
    unordered_map<int, int> cnt;
    for (int x : nums) cnt[x]++;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;   // min-heap on (count, value)
    for (auto& [val, c] : cnt) {
        pq.push({c, val});
        if ((int)pq.size() > k) pq.pop();                           // evict the least frequent
    }
    vector<int> res;
    while (!pq.empty()) {
        res.push_back(pq.top().second);
        pq.pop();
    }
    return res;
}

// ---------- Approach 3: Bucket Sort ⭐ ----------
vector<int> topKFrequent(const vector<int>& nums, int k) {
    unordered_map<int, int> cnt;
    for (int x : nums) cnt[x]++;
    vector<vector<int>> buckets(nums.size() + 1);                   // index = frequency, max n
    for (auto& [val, c] : cnt) buckets[c].push_back(val);
    vector<int> res;
    for (int f = nums.size(); f >= 1 && (int)res.size() < k; f--)
        for (int val : buckets[f]) {
            res.push_back(val);
            if ((int)res.size() == k) break;
        }
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<int> v) {
    sort(v.begin(), v.end());                                        // normalize: order is unspecified
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 1, 1, 2, 2, 3}, 2}, {{1}, 1}, {{1, 2, 1, 2, 1, 2, 3, 1, 3, 2}, 2}, {{4, 4, -1, -1, -1, 7}, 1}
    };
    for (auto& [nums, k] : tests) {
        print("sorted", topKFrequentSorted(nums, k));
        print("heap  ", topKFrequentHeap(nums, k));
        print("bucket", topKFrequent(nums, k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - priority_queue<T, vector<T>, greater<>> is a min-heap; pairs compare by .first then .second.
 * - vector<pair<int,int>> v(m.begin(), m.end()) copies a map into a vector.
 * - Lambda comparator: [](const auto& a, const auto& b) { return a.second > b.second; }.
 * - vector<vector<int>> buckets(n + 1) creates n+1 empty inner vectors.
 */
