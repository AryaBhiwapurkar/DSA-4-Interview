/*
 * 0332. Reconstruct Itinerary  |  Hard  |  Advanced Graphs
 * Link: https://leetcode.com/problems/reconstruct-itinerary/
 *
 * Problem: Use every ticket [from, to] exactly once, starting at "JFK".
 *          If several itineraries work, return the lexicographically smallest.
 *
 * Examples:
 *   [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
 *       -> ["JFK","MUC","LHR","SFO","SJC"]
 *   [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
 *       -> ["JFK","ATL","JFK","SFO","ATL","SFO"]
 *   [["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]
 *       -> ["JFK","NRT","JFK","KUL"]   (smallest first move KUL is a dead end)
 *
 * Approaches:
 *   1. Backtracking, smallest destination first   O(E^d) worst case, O(E) space
 *   2. Hierholzer (post-order Eulerian path)  ⭐   O(E log E) time, O(E) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Backtracking ----------
bool backtrack(map<string, vector<string>>& adj, vector<string>& path, size_t total) {
    if (path.size() == total) return true;
    auto& dests = adj[path.back()];
    for (size_t i = 0; i < dests.size(); i++) {
        string v = dests[i];
        dests.erase(dests.begin() + i);           // use the ticket
        path.push_back(v);
        if (backtrack(adj, path, total)) return true;
        path.pop_back();
        dests.insert(dests.begin() + i, v);       // give it back
    }
    return false;
}

vector<string> findItineraryBacktrack(const vector<vector<string>>& tickets) {
    map<string, vector<string>> adj;
    for (auto& t : tickets) adj[t[0]].push_back(t[1]);
    for (auto& [_, d] : adj) sort(d.begin(), d.end());   // first full path found = smallest
    vector<string> path = {"JFK"};
    backtrack(adj, path, tickets.size() + 1);
    return path;
}

// ---------- Approach 2: Hierholzer ⭐ ----------
void visit(const string& u, unordered_map<string, vector<string>>& adj, vector<string>& route) {
    auto& dests = adj[u];
    while (!dests.empty()) {
        string v = dests.back();                  // sorted descending: back() is the smallest
        dests.pop_back();
        visit(v, adj, route);
    }
    route.push_back(u);                           // post-order: dead ends land first
}

vector<string> findItinerary(const vector<vector<string>>& tickets) {
    unordered_map<string, vector<string>> adj;
    for (auto& t : tickets) adj[t[0]].push_back(t[1]);
    for (auto& [_, d] : adj) sort(d.rbegin(), d.rend());
    vector<string> route;
    visit("JFK", adj, route);
    reverse(route.begin(), route.end());
    return route;
}

// ---------- Driver ----------
void print(const string& label, const vector<string>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << '"' << v[i] << '"';
    cout << "]\n";
}

int main() {
    vector<vector<vector<string>>> tests = {
        {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}},
        {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}},
        {{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}},
    };
    for (auto& t : tests) {
        print("backtrack ", findItineraryBacktrack(t));
        print("hierholzer", findItinerary(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `sort(d.rbegin(), d.rend())` sorts descending, so pop_back() yields the smallest in O(1).
 * - Copy `dests.back()` into a string before pop_back(); a reference would dangle.
 * - `auto& dests = adj[u];` binds to the map's vector so pops modify it in place.
 * - vector::erase/insert at an index make the backtracking undo simple (O(deg) each).
 */
