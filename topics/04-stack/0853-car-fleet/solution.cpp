/*
 * 0853. Car Fleet  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/car-fleet/
 *
 * Problem: Cars drive to target on one lane and can't pass; a car that
 *          catches up joins that fleet. Count fleets arriving at target.
 *
 * Examples:
 *   target 12,  pos [10,8,0,5,3], speed [2,4,1,1,3]  -> 3
 *   target 10,  pos [3],          speed [3]          -> 1
 *   target 100, pos [0,2,4],      speed [4,2,1]      -> 1
 *   target 10,  pos [0,4,8],      speed [1,1,1]      -> 3
 *
 * Approaches:
 *   1. Sort + stack of fleet times     O(n log n) time, O(n) space
 *   2. Sort + slowest fleet time  ⭐    O(n log n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> sortedCars(const vector<int>& position, const vector<int>& speed) {
    vector<pair<int, int>> cars;
    for (size_t i = 0; i < position.size(); i++) cars.push_back({position[i], speed[i]});
    sort(cars.rbegin(), cars.rend());      // closest to target first
    return cars;
}

// ---------- Approach 1: Sort + Stack of Fleet Times ----------
int carFleetStack(int target, const vector<int>& position, const vector<int>& speed) {
    vector<double> st;                     // arrival time of each fleet ahead
    for (auto [p, s] : sortedCars(position, speed)) {
        double t = double(target - p) / s; // double: integer division would truncate
        st.push_back(t);
        if (st.size() >= 2 && st.back() <= st[st.size() - 2]) st.pop_back();   // caught up: merged
    }
    return st.size();
}

// ---------- Approach 2: Sort + Slowest Fleet Time ⭐ ----------
int carFleet(int target, const vector<int>& position, const vector<int>& speed) {
    int fleets = 0;
    double last = 0;                       // arrival time of the fleet directly ahead
    for (auto [p, s] : sortedCars(position, speed)) {
        double t = double(target - p) / s;
        if (t > last) {                    // can't catch it: new, slower fleet
            fleets++;
            last = t;
        }
    }
    return fleets;
}

// ---------- Driver ----------
int main() {
    vector<tuple<int, vector<int>, vector<int>>> tests = {
        {12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}},
        {10, {3}, {3}},
        {100, {0, 2, 4}, {4, 2, 1}},
        {10, {0, 4, 8}, {1, 1, 1}},
    };
    for (auto& [target, pos, sp] : tests) {
        cout << "stack  : " << carFleetStack(target, pos, sp) << "\n";
        cout << "slowest: " << carFleet(target, pos, sp) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - sort(v.rbegin(), v.rend()) sorts descending via reverse iterators.
 * - `for (auto [p, s] : cars)` unpacks pairs by value (C++17).
 * - double(a) / b forces floating division; a / b on ints truncates.
 * - tuple<int, vector<int>, vector<int>> + structured bindings for test tables.
 */
