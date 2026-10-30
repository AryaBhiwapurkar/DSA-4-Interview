/*
 * 0981. Time Based Key-Value Store  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/time-based-key-value-store/
 *
 * Problem: set(key, value, t) stores a version; get(key, t) returns the
 *          value with the largest timestamp <= t, or "". Set timestamps
 *          are strictly increasing.
 *
 * Examples:
 *   set foo bar 1, get foo 1, get foo 3, set foo bar2 4, get foo 4, get foo 5
 *     -> [null,null,"bar","bar",null,"bar2","bar2"]
 *   set a x 5, get a 4, get b 1, get a 5
 *     -> [null,null,"","","x"]
 *
 * Approaches:
 *   1. Hashmap + linear scan        O(1) set, O(n) get, O(n) space
 *   2. Hashmap + binary search  ⭐   O(1) set, O(log n) get, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hashmap + Linear Scan ----------
class TimeMapLinear {
    unordered_map<string, vector<pair<int, string>>> m;
public:
    void set(const string& key, const string& value, int t) { m[key].push_back({t, value}); }
    string get(const string& key, int t) {
        auto it = m.find(key);
        if (it == m.end()) return "";
        auto& v = it->second;
        for (int i = v.size() - 1; i >= 0; i--)    // newest first
            if (v[i].first <= t) return v[i].second;
        return "";
    }
};

// ---------- Approach 2: Hashmap + Binary Search ⭐ ----------
class TimeMap {
    unordered_map<string, vector<pair<int, string>>> m;   // per key: sorted by time for free
public:
    void set(const string& key, const string& value, int t) { m[key].push_back({t, value}); }
    string get(const string& key, int t) {
        auto it = m.find(key);             // find, not m[key]: don't insert on lookup
        if (it == m.end()) return "";
        auto& v = it->second;
        int lo = 0, hi = v.size();         // upper bound: first timestamp > t
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (v[mid].first <= t) lo = mid + 1;
            else hi = mid;
        }
        return lo == 0 ? "" : v[lo - 1].second;
    }
};

// ---------- Driver ----------
template <class M>
void run(const string& label, const vector<string>& ops, const vector<vector<string>>& args) {
    M tm;
    cout << label << ": [null";            // ops[0] is the constructor
    for (size_t i = 1; i < ops.size(); i++) {
        if (ops[i] == "set") {
            tm.set(args[i][0], args[i][1], stoi(args[i][2]));
            cout << ",null";
        } else {
            cout << ",\"" << tm.get(args[i][0], stoi(args[i][1])) << "\"";
        }
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, vector<vector<string>>>> tests = {
        {{"TimeMap", "set", "get", "get", "set", "get", "get"},
         {{}, {"foo", "bar", "1"}, {"foo", "1"}, {"foo", "3"}, {"foo", "bar2", "4"}, {"foo", "4"}, {"foo", "5"}}},
        {{"TimeMap", "set", "get", "get", "get"},
         {{}, {"a", "x", "5"}, {"a", "4"}, {"b", "1"}, {"a", "5"}}},
    };
    for (auto& [ops, args] : tests) {
        run<TimeMapLinear>("linear", ops, args);
        run<TimeMap>("binary", ops, args);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - m[key].push_back(...) creates the vector on first use (intended in set).
 * - m.find(key) for read-only lookups avoids inserting empty entries.
 * - Alternative per key: map<int, string>; prev(upper_bound(t)) is the answer
 *   if upper_bound(t) != begin().
 */
