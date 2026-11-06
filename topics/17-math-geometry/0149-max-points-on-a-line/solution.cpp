/*
 * 0149. Max Points on a Line  |  Hard  |  Math & Geometry
 * Link: https://leetcode.com/problems/max-points-on-a-line/
 *
 * Problem: Given distinct integer points, return the most that lie on one straight line.
 *
 * Examples:
 *   [[1,1],[2,2],[3,3]]                          -> 3
 *   [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]        -> 4   (x + y = 5)
 *   [[0,0]]                                      -> 1
 *   [[1,1],[1,5],[1,-3],[2,2]]                   -> 3   (vertical x = 1)
 *   [[0,0],[94911151,94911150],[94911152,94911151]] -> 2   (outside LC range; float slopes would say 3)
 *
 * Approaches:
 *   1. Every pair + cross-product check     O(n^3) time, O(1) space
 *   2. Anchor + gcd-normalised slope map ⭐  O(n^2 log C) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Pair + Collinearity ----------
int maxPointsCubic(const vector<vector<int>>& p) {
    int n = p.size();
    if (n <= 2) return n;
    int best = 2;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            long long dx = p[j][0] - p[i][0], dy = p[j][1] - p[i][1];
            int cnt = 2;
            for (int k = j + 1; k < n; k++)        // cross product 0 <=> collinear
                if (dx * (p[k][1] - p[i][1]) == dy * (p[k][0] - p[i][0])) cnt++;
            best = max(best, cnt);
        }
    return best;
}

// ---------- Approach 2: Anchor + Slope Map ⭐ ----------
int maxPoints(const vector<vector<int>>& p) {
    int n = p.size(), best = 1;
    for (int i = 0; i < n; i++) {
        map<pair<int, int>, int> slopes;           // fresh map per anchor
        for (int j = i + 1; j < n; j++) {
            int dx = p[j][0] - p[i][0], dy = p[j][1] - p[i][1];
            int g = gcd(abs(dx), abs(dy));         // > 0: points are distinct
            dx /= g, dy /= g;
            if (dx < 0 || (dx == 0 && dy < 0)) dx = -dx, dy = -dy;   // one key per direction
            best = max(best, 1 + ++slopes[{dx, dy}]);
        }
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 1}, {2, 2}, {3, 3}},
        {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}},
        {{0, 0}},
        {{1, 1}, {1, 5}, {1, -3}, {2, 2}},
        {{0, 0}, {94911151, 94911150}, {94911152, 94911151}}};
    for (auto& t : tests) {
        cout << "cubic: " << maxPointsCubic(t) << "\n";
        cout << "slope: " << maxPoints(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::gcd (in <numeric>, C++17) returns a non-negative gcd; gcd(0, k) = k.
 * - map<pair<int,int>, int> keys on exact integer pairs (no custom hash needed).
 * - 1 + ++m[key] increments first, then uses the new count.
 * - Cross products use long long: differences up to 2e4 are fine, but big inputs would overflow int.
 */
