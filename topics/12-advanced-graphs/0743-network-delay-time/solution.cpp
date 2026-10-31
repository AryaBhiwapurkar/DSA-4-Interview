/*
 * 0743. Network Delay Time  |  Medium  |  Advanced Graphs
 * Link: https://leetcode.com/problems/network-delay-time/
 *
 * Problem: Directed weighted edges (u, v, w), nodes 1..n. A signal starts at k.
 *          Return the time until every node has it, or -1 if some never does.
 *
 * Examples:
 *   [[2,1,1],[2,3,1],[3,4,1]], n=4, k=2          -> 2
 *   [[1,2,1]], n=2, k=1                          -> 1
 *   [[1,2,1]], n=2, k=2                          -> -1
 *   [[1,2,4],[1,3,1],[3,2,1],[2,4,1]], n=4, k=1  -> 3 (detour beats direct edge)
 *
 * Approaches:
 *   1. Bellman-Ford        O(V*E) time, O(V) space
 *   2. Dijkstra (heap)  ⭐  O(E log V) time, O(V + E) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Bellman-Ford ----------
int networkDelayTimeBF(const vector<vector<int>>& times, int n, int k) {
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    for (int round = 1; round < n; round++) {   // a shortest path has at most n-1 edges
        bool changed = false;
        for (auto& e : times) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) { dist[v] = dist[u] + w; changed = true; }
        }
        if (!changed) break;
    }
    int ans = *max_element(dist.begin() + 1, dist.end());
    return ans == INT_MAX ? -1 : ans;
}

// ---------- Approach 2: Dijkstra ⭐ ----------
int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& e : times) adj[e[0]].push_back({e[1], e[2]});
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;   // (dist, node), min first
    dist[k] = 0;
    pq.push({0, k});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;                // stale entry: u was already settled cheaper
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
    }
    int ans = *max_element(dist.begin() + 1, dist.end());   // node 0 unused
    return ans == INT_MAX ? -1 : ans;
}

// ---------- Driver ----------
int main() {
    struct Test { vector<vector<int>> times; int n, k; };
    vector<Test> tests = {
        {{{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2},
        {{{1, 2, 1}}, 2, 1},
        {{{1, 2, 1}}, 2, 2},
        {{{1, 2, 4}, {1, 3, 1}, {3, 2, 1}, {2, 4, 1}}, 4, 1},
    };
    for (auto& t : tests) {
        cout << "bellman : " << networkDelayTimeBF(t.times, t.n, t.k) << "\n";
        cout << "dijkstra: " << networkDelayTime(t.times, t.n, t.k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `priority_queue<T, vector<T>, greater<>>` is a min-heap; pairs compare by .first first.
 * - `auto [d, u] = pq.top();` copies before pop(), so the binding stays valid.
 * - `*max_element(v.begin() + 1, v.end())` skips the unused index 0.
 * - Guard `dist[u] != INT_MAX` before adding, or INT_MAX + w overflows.
 */
