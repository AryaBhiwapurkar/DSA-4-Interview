/*
 * 0088. Merge Sorted Array  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/merge-sorted-array/
 *
 * Problem: nums1 holds m sorted values plus n free slots; nums2 holds n
 *          sorted values. Merge nums2 into nums1 in place, sorted.
 *
 * Examples:
 *   [1,2,3,0,0,0], m=3, [2,5,6], n=3   -> [1,2,2,3,5,6]
 *   [1], m=1, [], n=0                  -> [1]
 *   [0], m=0, [1], n=1                 -> [1]
 *   [4,5,0,0], m=2, [1,2], n=2         -> [1,2,4,5]
 *
 * Approaches:
 *   1. Copy + sort              O((m+n) log(m+n)) time, O(1) extra
 *   2. Forward merge with copy  O(m+n) time, O(m) space
 *   3. Backward merge  ⭐        O(m+n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Copy + Sort ----------
void mergeSort(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
    copy(nums2.begin(), nums2.end(), nums1.begin() + m);
    sort(nums1.begin(), nums1.end());
}

// ---------- Approach 2: Forward Merge With a Copy ----------
void mergeForward(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
    vector<int> a(nums1.begin(), nums1.begin() + m);    // save nums1's values before overwriting
    int i = 0, j = 0, w = 0;
    while (i < m || j < n)
        nums1[w++] = (j == n || (i < m && a[i] <= nums2[j])) ? a[i++] : nums2[j++];
}

// ---------- Approach 3: Backward Merge ⭐ ----------
void merge(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, w = m + n - 1;
    while (j >= 0) {                                    // once nums2 is used up, nums1's rest is in place
        if (i >= 0 && nums1[i] > nums2[j]) nums1[w--] = nums1[i--];
        else nums1[w--] = nums2[j--];
    }
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    struct Test { vector<int> nums1; int m; vector<int> nums2; int n; };
    vector<Test> tests = {
        {{1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}, 3}, {{1}, 1, {}, 0}, {{0}, 0, {1}, 1}, {{4, 5, 0, 0}, 2, {1, 2}, 2}
    };
    for (auto& t : tests) {
        auto a = t.nums1, b = t.nums1, c = t.nums1;
        mergeSort(a, t.m, t.nums2, t.n);
        mergeForward(b, t.m, t.nums2, t.n);
        merge(c, t.m, t.nums2, t.n);
        print("sort    ", a);
        print("forward ", b);
        print("backward", c);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - nums1[w--] = nums1[i--] uses both values before decrementing.
 * - vector<int> a(first, last) copies a sub-range.
 * - A local struct makes a readable test table.
 */
