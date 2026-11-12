/*
 * 0220. Contains Duplicate III  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/contains-duplicate-iii/
 *
 * Problem: Is there i != j with |i - j| <= indexDiff and |nums[i] - nums[j]| <= valueDiff?
 *
 * Examples:
 *   [1,2,3,1],     indexDiff = 3, valueDiff = 0  -> true
 *   [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3  -> false
 *   [-3,3],        indexDiff = 1, valueDiff = 2  -> false   (truncating buckets would say true)
 *   [2147483647,-2147483648], indexDiff = 1, valueDiff = 1 -> false   (overflow trap)
 *   [1,5,9,1],     indexDiff = 3, valueDiff = 3  -> true
 *
 * Approaches:
 *   1. Check each pair in range      O(n * indexDiff) time, O(1) space
 *   2. Ordered set window            O(n log k) time, O(k) space
 *   3. Buckets  ⭐                   O(n) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Pairs in Range ----------
bool containsNearbyAlmostDuplicateBrute(const vector<int>& nums, int indexDiff, int valueDiff) {
    int n = nums.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= i + indexDiff && j < n; j++)
            if (llabs((long long)nums[i] - nums[j]) <= valueDiff) return true;
    return false;
}

// ---------- Approach 2: Ordered Set ----------
bool containsNearbyAlmostDuplicateSet(const vector<int>& nums, int indexDiff, int valueDiff) {
    set<long long> win;
    for (int i = 0; i < (int)nums.size(); i++) {
        auto it = win.lower_bound((long long)nums[i] - valueDiff);   // smallest >= x - valueDiff
        if (it != win.end() && *it <= (long long)nums[i] + valueDiff) return true;
        win.insert(nums[i]);
        if (i >= indexDiff) win.erase(nums[i - indexDiff]);
    }
    return false;
}

// ---------- Approach 3: Buckets ⭐ ----------
bool containsNearbyAlmostDuplicate(const vector<int>& nums, int indexDiff, int valueDiff) {
    long long w = (long long)valueDiff + 1;
    auto id = [w](long long x) { return x >= 0 ? x / w : (x + 1) / w - 1; };   // floor division
    unordered_map<long long, long long> bucket;   // bucket id -> the one value in it
    for (int i = 0; i < (int)nums.size(); i++) {
        long long x = nums[i], b = id(x);
        if (bucket.count(b)) return true;          // same bucket: within valueDiff
        for (long long nb : {b - 1, b + 1}) {
            auto it = bucket.find(nb);
            if (it != bucket.end() && llabs(it->second - x) <= valueDiff) return true;
        }
        bucket[b] = x;
        if (i >= indexDiff) bucket.erase(id(nums[i - indexDiff]));   // keep the last indexDiff values
    }
    return false;
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    struct T { vector<int> nums; int idx, val; };
    vector<T> tests = {{{1, 2, 3, 1}, 3, 0}, {{1, 5, 9, 1, 5, 9}, 2, 3}, {{-3, 3}, 1, 2},
                       {{2147483647, -2147483647 - 1}, 1, 1}, {{1, 5, 9, 1}, 3, 3}};
    for (auto& t : tests) {
        cout << "pairs  : " << containsNearbyAlmostDuplicateBrute(t.nums, t.idx, t.val) << "\n";
        cout << "set    : " << containsNearbyAlmostDuplicateSet(t.nums, t.idx, t.val) << "\n";
        cout << "buckets: " << containsNearbyAlmostDuplicate(t.nums, t.idx, t.val) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - C++ / truncates toward zero; floor for negatives is (x + 1) / w - 1.
 * - set::lower_bound(v) finds the first element >= v in O(log n).
 * - Write INT_MIN as -2147483647 - 1: the literal 2147483648 doesn't fit in int.
 */
