/*
 * 0787. Cheapest Flights Within K Stops  |  Medium  |  Advanced Graphs
 * Link: https://leetcode.com/problems/cheapest-flights-within-k-stops/
 *
 * Problem: Directed flights (from, to, price) between n cities. Cheapest price
 *          from src to dst using at most k stops (k+1 flights), or -1.
 *
 * Examples:
 *   n=4, [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], 0->3, k=1  -> 700
 *   n=3, [[0,1,100],[1,2,100],[0,2,500]], 0->2, k=1                      -> 200
 *   n=3, [[0,1,100],[1,2,100],[0,2,500]], 0->2, k=0                      -> 500
 *   n=2, [[0,1,100]], 1->0, k=1                                          -> -1
 *
 * Approaches:
 *   1. Dijkstra on (node, flights used)   O(E*k log(E*k)) time, O(n*k + E) space
 *   2. Bellman-Ford, k+1 rounds  ⭐         O(k*E) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Dijkstra with stop count in the state ----------
int findCheapestPriceDijkstra(int n, const vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& f : flights) adj[f[0]].push_back({f[1], f[2]});
    vector<int> bestEdges(n, INT_MAX);            // fewest flights seen when popping each city
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;   // (cost, city, flights)
    pq.push({0, src, 0});
    while (!pq.empty()) {
        auto [cost, u, e] = pq.top(); pq.pop();
        if (u == dst) return cost;                // first pop of dst is the cheapest valid one
        if (e == k + 1 || e >= bestEdges[u]) continue;   // out of flights, or dominated (cheaper AND fewer flights seen)
        bestEdges[u] = e;
        for (auto [v, w] : adj[u]) pq.push({cost + w, v, e + 1});
    }
    return -1;
}

// ---------- Approach 2: Bellman-Ford, k+1 rounds ⭐ ----------
int findCheapestPrice(int n, const vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> price(n, INT_MAX);
    price[src] = 0;
    for (int round = 0; round <= k; round++) {   // round i allows i+1 flights
        vector<int> next = price;                 // read old prices only: one more flight per round
        for (auto& f : flights) {
            int u = f[0], v = f[1], w = f[2];
            if (price[u] != INT_MAX && price[u] + w < next[v]) next[v] = price[u] + w;
        }
        price = next;
    }
    return price[dst] == INT_MAX ? -1 : price[dst];
}

// ---------- Driver ----------
int main() {
    struct Test { int n; vector<vector<int>> flights; int src, dst, k; };
    vector<vector<int>> tri = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    vector<Test> tests = {
        {4, {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}}, 0, 3, 1},
        {3, tri, 0, 2, 1},
        {3, tri, 0, 2, 0},
        {2, {{0, 1, 100}}, 1, 0, 1},
    };
    for (auto& t : tests) {
        cout << "dijkstra: " << findCheapestPriceDijkstra(t.n, t.flights, t.src, t.dst, t.k) << "\n";
        cout << "bellman : " << findCheapestPrice(t.n, t.flights, t.src, t.dst, t.k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `array<int, 3>` compares lexicographically, so it works in a priority_queue like a tuple.
 * - `auto [cost, u, e] = pq.top();` unpacks a std::array with structured bindings.
 * - `vector<int> next = price;` is a full copy: the key to "one flight per round".
 */
