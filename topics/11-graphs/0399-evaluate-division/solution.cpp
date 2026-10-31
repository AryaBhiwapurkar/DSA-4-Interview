/*
 * 0399. Evaluate Division  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/evaluate-division/
 *
 * Problem: Given equations a / b = k, answer queries x / y, or -1.0 if
 *          they can't be determined.
 *
 * Examples:
 *   [a/b=2, b/c=3]; a/c, b/a, a/e, a/a, x/x        -> [6.00000,0.50000,-1.00000,1.00000,-1.00000]
 *   [a/b=1.5, b/c=2.5, bc/cd=5]; a/c, c/b, bc/cd, cd/bc -> [3.75000,0.40000,5.00000,0.20000]
 *   [a/b=0.5]; a/b, b/a, a/c, x/y                  -> [0.50000,2.00000,-1.00000,-1.00000]
 *
 * Approaches:
 *   1. DFS per query  ⭐         O(Q * (V + E)) time, O(V + E) space   <- go-to
 *   2. Weighted Union-Find       O((E + Q) * alpha) time, O(V) space
 */

#include <bits/stdc++.h>
using namespace std;

using Eqs = vector<vector<string>>;

// ---------- Approach 1: DFS per Query ⭐ ----------
double dfs(const string& u, const string& target, unordered_map<string, vector<pair<string, double>>>& adj,
           unordered_set<string>& seen) {
    if (u == target) return 1.0;
    seen.insert(u);
    for (auto& [v, w] : adj[u]) {
        if (seen.count(v)) continue;
        double r = dfs(v, target, adj, seen);
        if (r >= 0) return w * r;          // u/target = u/v * v/target
    }
    return -1.0;
}

vector<double> calcEquation(const Eqs& eq, const vector<double>& vals, const Eqs& queries) {
    unordered_map<string, vector<pair<string, double>>> adj;
    for (size_t i = 0; i < eq.size(); i++) {
        adj[eq[i][0]].push_back({eq[i][1], vals[i]});
        adj[eq[i][1]].push_back({eq[i][0], 1.0 / vals[i]});   // reverse edge
    }
    vector<double> res;
    for (auto& q : queries) {
        if (!adj.count(q[0]) || !adj.count(q[1])) { res.push_back(-1.0); continue; }   // unknown, even x/x
        unordered_set<string> seen;
        res.push_back(dfs(q[0], q[1], adj, seen));
    }
    return res;
}

// ---------- Approach 2: Weighted Union-Find ----------
struct WDSU {
    unordered_map<string, string> parent;
    unordered_map<string, double> weight;  // weight[x] = x / parent[x]
    void add(const string& x) { if (!parent.count(x)) { parent[x] = x; weight[x] = 1.0; } }
    string find(const string& x) {         // afterwards weight[x] = x / root
        if (parent[x] == x) return x;
        string p = parent[x];
        string root = find(p);
        weight[x] *= weight[p];
        parent[x] = root;
        return root;
    }
    void unite(const string& a, const string& b, double k) {   // a / b = k
        string ra = find(a), rb = find(b);
        if (ra == rb) return;
        parent[ra] = rb;
        weight[ra] = k * weight[b] / weight[a];   // ra/rb = (a/wa) / (b/wb) with a/b = k
    }
};

vector<double> calcEquationUF(const Eqs& eq, const vector<double>& vals, const Eqs& queries) {
    WDSU d;
    for (size_t i = 0; i < eq.size(); i++) {
        d.add(eq[i][0]); d.add(eq[i][1]);
        d.unite(eq[i][0], eq[i][1], vals[i]);
    }
    vector<double> res;
    for (auto& q : queries) {
        if (!d.parent.count(q[0]) || !d.parent.count(q[1]) || d.find(q[0]) != d.find(q[1])) res.push_back(-1.0);
        else res.push_back(d.weight[q[0]] / d.weight[q[1]]);   // (x/root) / (y/root)
    }
    return res;
}

// ---------- Driver ----------
void print(const string& label, const vector<double>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) printf("%s%.5f", i ? "," : "", v[i]);
    cout << "]\n";
}

int main() {
    struct T { Eqs eq; vector<double> vals; Eqs q; };
    vector<T> tests = {
        {{{"a", "b"}, {"b", "c"}}, {2.0, 3.0}, {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}}},
        {{{"a", "b"}, {"b", "c"}, {"bc", "cd"}}, {1.5, 2.5, 5.0}, {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}}},
        {{{"a", "b"}}, {0.5}, {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}}},
    };
    for (auto& t : tests) {
        print("dfs", calcEquation(t.eq, t.vals, t.q));
        cout.flush();
        print("uf ", calcEquationUF(t.eq, t.vals, t.q));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Mixing printf and cout works because they share stdio sync by default.
 * - `using Eqs = vector<vector<string>>;` is a type alias.
 * - unordered_map::count avoids the inserting operator[] for existence checks.
 */
