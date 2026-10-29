/*
 * 0015. 3Sum  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/3sum/
 *
 * Problem: Return all unique value-triplets [a,b,c] from different indices
 *          with a + b + c == 0. Any order.
 *
 * Examples (printed sorted for stable output):
 *   [-1,0,1,2,-1,-4]  -> [[-1,-1,2],[-1,0,1]]
 *   [0,1,1]           -> []
 *   [0,0,0]           -> [[0,0,0]]
 *   [0,0,0,0]         -> [[0,0,0]]
 *
 * Approaches:
 *   1. Brute force + set        O(n^3) time, O(k) space
 *   2. Hash set per fixed i     O(n^2) time, O(n) space
 *   3. Sort + two pointers  ⭐   O(n^2) time, O(1) extra space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force + Set ----------
vector<vector<int>> threeSumBrute(const vector<int>& nums) {
    set<vector<int>> found;
    int n = nums.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> t = {nums[i], nums[j], nums[k]};
                    sort(t.begin(), t.end());              // canonical order for dedup
                    found.insert(t);
                }
    return {found.begin(), found.end()};
}

// ---------- Approach 2: Hash Set per Fixed Element ----------
vector<vector<int>> threeSumHash(const vector<int>& nums) {
    set<vector<int>> found;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        unordered_set<int> seen;
        for (int j = i + 1; j < n; j++) {
            int need = -nums[i] - nums[j];
            if (seen.count(need)) {
                vector<int> t = {nums[i], nums[j], need};
                sort(t.begin(), t.end());
                found.insert(t);
            }
            seen.insert(nums[j]);
        }
    }
    return {found.begin(), found.end()};
}

// ---------- Approach 3: Sort + Two Pointers ⭐ ----------
vector<vector<int>> threeSum(vector<int> nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    int n = nums.size();
    for (int i = 0; i < n - 2; i++) {
        if (nums[i] > 0) break;                            // smallest is positive: no more zeros possible
        if (i > 0 && nums[i] == nums[i - 1]) continue;     // same first value already handled
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum < 0) l++;
            else if (sum > 0) r--;
            else {
                res.push_back({nums[i], nums[l], nums[r]});
                l++, r--;
                while (l < r && nums[l] == nums[l - 1]) l++;   // skip duplicate seconds
                while (l < r && nums[r] == nums[r + 1]) r--;   // skip duplicate thirds
            }
        }
    }
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<int>> v) {
    sort(v.begin(), v.end());                              // normalize: order is unspecified
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++)
        cout << (i ? "," : "") << "[" << v[i][0] << "," << v[i][1] << "," << v[i][2] << "]";
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{-1, 0, 1, 2, -1, -4}, {0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0}};
    for (auto& nums : tests) {
        print("brute   ", threeSumBrute(nums));
        print("hash    ", threeSumHash(nums));
        print("pointers", threeSum(nums));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - set<vector<int>> dedupes vectors (ordered lexicographically).
 * - return {s.begin(), s.end()}; constructs the return vector from a range.
 * - Loop bound i < n - 2 is safe because n is an int (n >= 3 here).
 */
