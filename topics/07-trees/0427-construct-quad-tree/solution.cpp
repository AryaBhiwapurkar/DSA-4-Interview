/*
 * 0427. Construct Quad Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/construct-quad-tree/
 *
 * Problem: Build the quad tree of an n x n 0/1 grid (n a power of 2).
 *          Output: level order of [isLeaf, val] with null for missing children.
 *
 * Examples:
 *   [[0,1],[1,0]]       -> [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *   8x8 (see README)    -> [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 *   [[1]]               -> [[1,1]]
 *   [[0,0],[0,0]]       -> [[1,0]]
 *
 * Approaches:
 *   1. Check then split  ⭐          O(n^2 log n) time, O(log n) stack   <- go-to
 *   2. Split then merge (bottom-up)  O(n^2) time, O(log n) stack
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool val, isLeaf;
    Node *topLeft = nullptr, *topRight = nullptr, *bottomLeft = nullptr, *bottomRight = nullptr;
    Node(bool v, bool leaf) : val(v), isLeaf(leaf) {}
    Node(bool v, bool leaf, Node* tl, Node* tr, Node* bl, Node* br)
        : val(v), isLeaf(leaf), topLeft(tl), topRight(tr), bottomLeft(bl), bottomRight(br) {}
};

// ---------- Approach 1: Check Then Split ⭐ ----------
Node* go(const vector<vector<int>>& g, int r, int c, int size) {
    bool uniform = true;
    for (int i = r; i < r + size && uniform; i++)
        for (int j = c; j < c + size; j++)
            if (g[i][j] != g[r][c]) { uniform = false; break; }
    if (uniform) return new Node(g[r][c], true);
    int h = size / 2;                      // TL, TR, BL, BR: rows first, then columns
    return new Node(true, false, go(g, r, c, h), go(g, r, c + h, h), go(g, r + h, c, h), go(g, r + h, c + h, h));
}

Node* construct(const vector<vector<int>>& grid) { return go(grid, 0, 0, grid.size()); }

// ---------- Approach 2: Split Then Merge ----------
Node* merge(const vector<vector<int>>& g, int r, int c, int size) {
    if (size == 1) return new Node(g[r][c], true);
    int h = size / 2;
    Node *tl = merge(g, r, c, h), *tr = merge(g, r, c + h, h);
    Node *bl = merge(g, r + h, c, h), *br = merge(g, r + h, c + h, h);
    bool allLeaves = tl->isLeaf && tr->isLeaf && bl->isLeaf && br->isLeaf;
    if (allLeaves && tl->val == tr->val && tr->val == bl->val && bl->val == br->val)
        return new Node(tl->val, true);    // four equal leaves collapse into one
    return new Node(true, false, tl, tr, bl, br);
}

Node* constructMerge(const vector<vector<int>>& grid) { return merge(grid, 0, 0, grid.size()); }

// ---------- Driver ----------
string serialize(Node* root) {             // LeetCode format: level order of [isLeaf,val]
    vector<string> out;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* n = q.front();
        q.pop();
        if (!n) { out.push_back("null"); continue; }
        out.push_back("[" + to_string(n->isLeaf) + "," + to_string(n->val) + "]");
        for (Node* ch : {n->topLeft, n->topRight, n->bottomLeft, n->bottomRight}) q.push(ch);
    }
    while (!out.empty() && out.back() == "null") out.pop_back();
    string s = "[";
    for (size_t i = 0; i < out.size(); i++) s += (i ? "," : "") + out[i];
    return s + "]";
}

int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 1}, {1, 0}},
        {{1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1},
         {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}},
        {{1}},
        {{0, 0}, {0, 0}},
    };
    for (auto& g : tests) {
        cout << "split: " << serialize(construct(g)) << "\n";
        cout << "merge: " << serialize(constructMerge(g)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - to_string(bool) prints 1/0 (bool promotes to int).
 * - Constructing a Node from an int grid cell converts 0/1 to false/true.
 * - Iterating a braced list of four pointers queues children in order.
 */
