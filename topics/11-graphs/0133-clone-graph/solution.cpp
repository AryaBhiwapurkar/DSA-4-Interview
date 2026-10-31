/*
 * 0133. Clone Graph  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/clone-graph/
 *
 * Problem: Deep-copy a connected undirected graph given one of its nodes.
 *          Test input/output is an adjacency list (node i+1's neighbours).
 *
 * Examples:
 *   [[2,4],[1,3],[2,4],[1,3]]  -> [[2,4],[1,3],[2,4],[1,3]]
 *   [[]]                       -> [[]]
 *   []                         -> []
 *   [[2],[1,3],[2]]            -> [[2],[1,3],[2]]   (path 1-2-3)
 *
 * Approaches:
 *   1. DFS + map  ⭐   O(V + E) time, O(V) space   <- go-to
 *   2. BFS + map       O(V + E) time, O(V) space
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    vector<Node*> neighbors;
    Node(int v) : val(v) {}
};

// ---------- Approach 1: DFS + Map ⭐ ----------
Node* dfs(Node* node, unordered_map<Node*, Node*>& copy) {
    auto it = copy.find(node);
    if (it != copy.end()) return it->second;
    Node* c = new Node(node->val);
    copy[node] = c;                        // before recursing: cycles find it
    for (Node* nb : node->neighbors) c->neighbors.push_back(dfs(nb, copy));
    return c;
}

Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> copy;
    return dfs(node, copy);
}

// ---------- Approach 2: BFS + Map ----------
Node* cloneGraphBFS(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> copy{{node, new Node(node->val)}};
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        for (Node* nb : cur->neighbors) {
            if (!copy.count(nb)) {
                copy[nb] = new Node(nb->val);
                q.push(nb);
            }
            copy[cur]->neighbors.push_back(copy[nb]);
        }
    }
    return copy[node];
}

// ---------- Driver ----------
vector<Node*> build(const vector<vector<int>>& adj) {
    vector<Node*> nodes;
    for (size_t i = 0; i < adj.size(); i++) nodes.push_back(new Node(i + 1));
    for (size_t i = 0; i < adj.size(); i++)
        for (int v : adj[i]) nodes[i]->neighbors.push_back(nodes[v - 1]);
    return nodes;
}

vector<Node*> collect(Node* start) {       // every reachable node, indexed by val - 1
    vector<Node*> out;
    if (!start) return out;
    unordered_set<Node*> seen{start};
    vector<Node*> st{start};
    while (!st.empty()) {
        Node* cur = st.back(); st.pop_back();
        if ((int)out.size() < cur->val) out.resize(cur->val);
        out[cur->val - 1] = cur;
        for (Node* nb : cur->neighbors) if (seen.insert(nb).second) st.push_back(nb);
    }
    return out;
}

void print(const string& label, Node* clone, const vector<Node*>& orig) {
    auto nodes = collect(clone);
    bool deep = true;
    cout << label << ": [";
    for (size_t i = 0; i < nodes.size(); i++) {
        if (find(orig.begin(), orig.end(), nodes[i]) != orig.end()) deep = false;
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < nodes[i]->neighbors.size(); j++) cout << (j ? "," : "") << nodes[i]->neighbors[j]->val;
        cout << "]";
    }
    cout << "] deep copy: " << (deep ? "true" : "false") << "\n";
}

int main() {
    vector<vector<vector<int>>> tests = {{{2, 4}, {1, 3}, {2, 4}, {1, 3}}, {{}}, {}, {{2}, {1, 3}, {2}}};
    for (auto& adj : tests) {
        auto orig = build(adj);
        Node* start = orig.empty() ? nullptr : orig[0];
        print("dfs", cloneGraph(start), orig);
        print("bfs", cloneGraphBFS(start), orig);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_map<Node*, Node*> keys on pointer identity.
 * - seen.insert(x).second is true only if x was new.
 * - Driver leaks the test nodes on purpose (short-lived program).
 */
