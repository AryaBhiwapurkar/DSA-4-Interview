/*
 * 0739. Daily Temperatures  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/daily-temperatures/
 *
 * Problem: For each day, how many days until a strictly warmer one?
 *          0 if none.
 *
 * Examples:
 *   [73,74,75,71,69,72,76,73]  -> [1,1,4,2,1,1,0,0]
 *   [30,40,50,60]              -> [1,1,1,0]
 *   [30,60,90]                 -> [1,1,0]
 *   [70,70]                    -> [0,0]
 *   [5,4,3]                    -> [0,0,0]
 *
 * Approaches:
 *   1. Brute force         O(n^2) time, O(1) extra space
 *   2. Monotonic stack  ⭐  O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
vector<int> dailyTemperaturesBrute(const vector<int>& t) {
    int n = t.size();
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (t[j] > t[i]) { ans[i] = j - i; break; }
    return ans;
}

// ---------- Approach 2: Monotonic Stack ⭐ ----------
vector<int> dailyTemperatures(const vector<int>& t) {
    int n = t.size();
    vector<int> ans(n, 0);                 // unresolved days stay 0
    vector<int> st;                        // indices; temps decreasing bottom -> top
    for (int i = 0; i < n; i++) {
        while (!st.empty() && t[i] > t[st.back()]) {   // strictly warmer resolves
            ans[st.back()] = i - st.back();
            st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {
        {73, 74, 75, 71, 69, 72, 76, 73}, {30, 40, 50, 60}, {30, 60, 90}, {70, 70}, {5, 4, 3}
    };
    for (auto& t : tests) {
        print("brute", dailyTemperaturesBrute(t));
        print("stack", dailyTemperatures(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<int> ans(n, 0) preallocates and zero-fills.
 * - Short-circuit `!st.empty() && t[i] > t[st.back()]` keeps back() safe.
 * - Store indices on the stack; read values through t[st.back()].
 */
