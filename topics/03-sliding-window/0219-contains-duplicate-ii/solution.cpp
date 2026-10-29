/*
 * 0219. Contains Duplicate II  |  Easy  |  Sliding Window
 * Link: https://leetcode.com/problems/contains-duplicate-ii/
 *
 * Problem: Return true if two equal values sit at most k indices apart.
 *
 * Examples:
 *   [1,2,3,1], k=3        -> true
 *   [1,0,1,1], k=1        -> true
 *   [1,2,3,1,2,3], k=2    -> false
 *   [1,1], k=0            -> false
 *
 * Approaches:
 *   1. Brute force          O(n*k) time, O(1) space
 *   2. Last-seen hashmap    O(n) time, O(n) space
 *   3. Window set  ⭐        O(n) time, O(min(n,k)) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
bool containsNearbyDuplicateBrute(const vector<int>& nums, int k) {
    int n = nums.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n && j - i <= k; j++)
            if (nums[i] == nums[j]) return true;
    return false;
}

// ---------- Approach 2: Last-Seen Hashmap ----------
bool containsNearbyDuplicateMap(const vector<int>& nums, int k) {
    unordered_map<int, int> last;                       // value -> most recent index
    for (int i = 0; i < (int)nums.size(); i++) {
        auto it = last.find(nums[i]);
        if (it != last.end() && i - it->second <= k) return true;
        last[nums[i]] = i;
    }
    return false;
}

// ---------- Approach 3: Window Set ⭐ ----------
bool containsNearbyDuplicate(const vector<int>& nums, int k) {
    unordered_set<int> window;                          // values at indices [i-k, i-1]
    for (int i = 0; i < (int)nums.size(); i++) {
        if (window.count(nums[i])) return true;
        window.insert(nums[i]);
        if ((int)window.size() > k) window.erase(nums[i - k]);   // drop the value that leaves the window
    }
    return false;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 3, 1}, 3}, {{1, 0, 1, 1}, 1}, {{1, 2, 3, 1, 2, 3}, 2}, {{1, 1}, 0}
    };
    cout << boolalpha;
    for (auto& [nums, k] : tests) {
        cout << "brute : " << containsNearbyDuplicateBrute(nums, k) << "\n";
        cout << "map   : " << containsNearbyDuplicateMap(nums, k) << "\n";
        cout << "window: " << containsNearbyDuplicate(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_set::erase(value) removes by value.
 * - Cast size() to int before comparing with a signed k.
 * - The set never holds duplicates: a repeat would have returned true first.
 */
