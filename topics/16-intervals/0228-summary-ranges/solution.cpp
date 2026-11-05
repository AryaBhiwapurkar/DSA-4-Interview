/*
 * 0228. Summary Ranges  |  Easy  |  Intervals
 * Link: https://leetcode.com/problems/summary-ranges/
 *
 * Problem: Given a sorted array of distinct ints, describe it as the fewest
 *          ranges of consecutive numbers ("a->b", or "a" for a single number).
 *
 * Examples:
 *   [0,1,2,4,5,7]       -> ["0->2","4->5","7"]
 *   [0,2,3,4,6,8,9]     -> ["0","2->4","6","8->9"]
 *   []                  -> []
 *   [-1]                -> ["-1"]
 *   [-2147483648,2147483647] -> ["-2147483648","2147483647"]
 *
 * Approaches:
 *   1. Group by (value - index)          O(n) time, O(n) space
 *   2. One scan with a run start  ⭐      O(n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

string fmt(long long a, long long b) { return a == b ? to_string(a) : to_string(a) + "->" + to_string(b); }

// ---------- Approach 1: Group by value - index ----------
vector<string> summaryRangesGroup(const vector<int>& nums) {
    vector<string> res;
    size_t i = 0;
    while (i < nums.size()) {
        long long key = (long long)nums[i] - (long long)i;   // constant within a run
        size_t j = i;
        while (j + 1 < nums.size() && (long long)nums[j + 1] - (long long)(j + 1) == key) j++;
        res.push_back(fmt(nums[i], nums[j]));
        i = j + 1;
    }
    return res;
}

// ---------- Approach 2: One Scan ⭐ ----------
vector<string> summaryRanges(const vector<int>& nums) {
    vector<string> res;
    for (size_t i = 0; i < nums.size(); i++) {
        int start = nums[i];
        while (i + 1 < nums.size() && (long long)nums[i] + 1 == nums[i + 1]) i++;   // nums[i] + 1 overflows at INT_MAX
        res.push_back(fmt(start, nums[i]));
    }
    return res;
}

void print(const vector<string>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << "'" << v[i] << "'";
    cout << "]\n";
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{0, 1, 2, 4, 5, 7}, {0, 2, 3, 4, 6, 8, 9}, {}, {-1}, {INT_MIN, INT_MAX}};
    for (auto& t : tests) {
        cout << "group: "; print(summaryRangesGroup(t));
        cout << "scan : "; print(summaryRanges(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (long long)nums[i] + 1 widens before adding, so INT_MAX + 1 doesn't overflow.
 * - to_string(x) converts numbers to std::string; + concatenates.
 * - The inner while advances i, and the for loop's i++ then moves past the run.
 */
