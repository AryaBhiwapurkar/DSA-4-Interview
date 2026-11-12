/*
 * 0901. Online Stock Span  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/online-stock-span/
 *
 * Problem: next(price) returns how many consecutive days, ending today, had price <= today's.
 *
 * Examples:
 *   next: 100,80,60,70,60,75,85  -> 1,1,1,2,1,4,6
 *   next: 10,20,30               -> 1,2,3
 *   next: 5,5,5                  -> 1,2,3
 *
 * Approaches:
 *   1. Scan back each day                 O(n) per call
 *   2. Stack of (price, span)  ⭐         O(1) amortised per call   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Scan Back ----------
class StockSpannerBrute {
    vector<int> prices;

public:
    int next(int price) {
        prices.push_back(price);
        int span = 0;
        for (int i = prices.size() - 1; i >= 0 && prices[i] <= price; i--) span++;
        return span;
    }
};

// ---------- Approach 2: Monotonic Stack ⭐ ----------
class StockSpanner {
    vector<pair<int, int>> st;                     // (price, span), prices strictly decreasing

public:
    int next(int price) {
        int span = 1;
        while (!st.empty() && st.back().first <= price) {
            span += st.back().second;              // absorb the days that entry covered
            st.pop_back();
        }
        st.push_back({price, span});
        return span;
    }
};

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{100, 80, 60, 70, 60, 75, 85}, {10, 20, 30}, {5, 5, 5}};
    for (auto& t : tests) {
        StockSpannerBrute b;
        StockSpanner s;
        cout << "brute:";
        for (int p : t) cout << " " << b.next(p);
        cout << "\nstack:";
        for (int p : t) cout << " " << s.next(p);
        cout << "\n---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<pair<int,int>> as a stack of tuples; .first / .second read fields.
 * - Brute loop condition combines a bound check and the comparison (short-circuit).
 * - A fresh object per test keeps state from leaking between runs.
 */
