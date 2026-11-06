/*
 * 2013. Detect Squares  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/detect-squares/
 *
 * Problem: add(point) stores a point (duplicates allowed). count(point) returns how
 *          many ways to pick 3 stored points that form a positive-area, axis-aligned
 *          square with the query point.
 *
 * Examples:
 *   add(3,10) add(11,2) add(3,2)
 *   count(11,10) -> 1
 *   count(14,8)  -> 0
 *   add(11,2)
 *   count(11,10) -> 2      (two copies of (11,2))
 *   --- extra: squares on both sides of the query ---
 *   add(0,0) add(0,1) add(1,0) add(2,0) add(2,1)
 *   count(1,1)   -> 2      (left square uses x=0, right square uses x=2)
 *   count(5,5)   -> 0
 *
 * Approaches:
 *   1. Scan diagonal candidates  ⭐   add O(1), count O(distinct points)   <- go-to
 *   2. Scan the query's column        add O(1), count O(points with x = qx)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Diagonal Candidates ⭐ ----------
class DetectSquares {
    map<pair<int, int>, int> cnt;

    int get(int x, int y) const {                  // lookup without inserting
        auto it = cnt.find({x, y});
        return it == cnt.end() ? 0 : it->second;
    }

public:
    void add(vector<int> p) { cnt[{p[0], p[1]}]++; }

    int count(vector<int> q) {
        int qx = q[0], qy = q[1], total = 0;
        for (auto& [pt, c] : cnt) {
            auto [x, y] = pt;
            if (x == qx || abs(x - qx) != abs(y - qy)) continue;   // must be a true diagonal
            total += c * get(qx, y) * get(x, qy);
        }
        return total;
    }
};

// ---------- Approach 2: Query's Column ----------
class DetectSquaresColumn {
    unordered_map<int, unordered_map<int, int>> byX;   // x -> (y -> count)

    int get(int x, int y) const {
        auto ix = byX.find(x);
        if (ix == byX.end()) return 0;
        auto iy = ix->second.find(y);
        return iy == ix->second.end() ? 0 : iy->second;
    }

public:
    void add(vector<int> p) { byX[p[0]][p[1]]++; }

    int count(vector<int> q) {
        int qx = q[0], qy = q[1], total = 0;
        auto col = byX.find(qx);
        if (col == byX.end()) return 0;
        for (auto& [y, c] : col->second) {
            int d = abs(y - qy);
            if (d == 0) continue;
            for (int x : {qx - d, qx + d})         // square to the left and to the right
                total += c * get(x, qy) * get(x, y);
        }
        return total;
    }
};

// ---------- Driver ----------
template <class DS>
void run(const string& name) {
    cout << name << "\n";
    DS ds;
    ds.add({3, 10}); ds.add({11, 2}); ds.add({3, 2});
    cout << ds.count({11, 10}) << "\n";            // 1
    cout << ds.count({14, 8}) << "\n";             // 0
    ds.add({11, 2});
    cout << ds.count({11, 10}) << "\n";            // 2

    DS e;
    for (auto p : vector<vector<int>>{{0, 0}, {0, 1}, {1, 0}, {2, 0}, {2, 1}}) e.add(p);
    cout << e.count({1, 1}) << "\n";               // 2
    cout << e.count({5, 5}) << "\n";               // 0
    cout << "---\n";
}

int main() {
    run<DetectSquares>("diagonal:");
    run<DetectSquaresColumn>("column:");
}

/*
 * Syntax notes (C++):
 * - map<pair<int,int>, int> works out of the box; unordered_map needs a custom hash for pairs.
 * - find() instead of operator[] for lookups: [] would insert zero entries mid-iteration.
 * - auto [x, y] = pt destructures a pair (C++17).
 * - A template driver runs the same script against both classes.
 */
