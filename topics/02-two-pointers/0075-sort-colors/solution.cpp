/*
 * 0075. Sort Colors  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/sort-colors/
 *
 * Problem: Sort an array of 0s, 1s and 2s in place, without a library sort.
 *
 * Examples:
 *   [2,0,2,1,1,0]  -> [0,0,1,1,2,2]
 *   [2,0,1]        -> [0,1,2]
 *   [1]            -> [1]
 *   [2,2,0,0]      -> [0,0,2,2]
 *
 * Approaches:
 *   1. Counting sort                  O(n) time, O(1) space, two passes
 *   2. Dutch national flag  ⭐        O(n) time, O(1) space, one pass   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Counting Sort ----------
void sortColorsCount(vector<int>& nums) {
    int cnt[3] = {0, 0, 0};
    for (int x : nums) cnt[x]++;
    int k = 0;
    for (int c = 0; c < 3; c++)
        while (cnt[c]--) nums[k++] = c;
}

// ---------- Approach 2: Dutch National Flag ⭐ ----------
void sortColors(vector<int>& nums) {
    int lo = 0, mid = 0, hi = nums.size() - 1;     // [0,lo)=0, [lo,mid)=1, (hi,end]=2
    while (mid <= hi) {
        if (nums[mid] == 0) swap(nums[lo++], nums[mid++]);
        else if (nums[mid] == 1) mid++;
        else swap(nums[mid], nums[hi--]);          // mid stays: swapped-in value unseen
    }
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{2, 0, 2, 1, 1, 0}, {2, 0, 1}, {1}, {2, 2, 0, 0}};
    for (auto& t : tests) {
        auto a = t, b = t;
        sortColorsCount(a);
        sortColors(b);
        cout << "count: "; print(a);
        cout << "flag : "; print(b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - swap(nums[lo++], nums[mid++]) binds both references first, then increments.
 * - int cnt[3] = {0, 0, 0}; is a small fixed C array; std::array<int,3>{} also works.
 * - while (cnt[c]--) runs cnt[c] times (post-decrement tests the old value).
 */
